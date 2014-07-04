/**
 * templated kd-tree
 *
 * References:
 *	[1] On building fast kd-Trees for Ray Tracing, and on doing that in O(N log N). Ingo Wald & Vlastimil Havran
 *  [2] http://www.lsi.upc.edu/~conrado/research/talks/sem-albcom07.pdf
 */

#ifndef __SHZ_MATH_KD_TREE__
#define __SHZ_MATH_KD_TREE__

#include <array>
#include <stdexcept> 
#include <limits>
#include <tuple>
#include <stack>
#include <shz/math/math.hpp>
#include <shz/spatial/kd_tree_discriminators.hpp>
#include <shz/spatial/kd_tree_exceptions.hpp>

namespace shz{ namespace spatial{

    template <typename KeyType, typename ValueType, size_t K, typename Discriminator> struct default_kd_tree_traits {
		typedef KeyType key_type;
		typedef ValueType value_type;
		typedef size_t size_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;  
		typedef Discriminator discriminator_type;
		typedef std::pair<key_type, value_type> pair_type;

		static const size_type POINTER_BITS  = 0x7FFFFFFF;
		static const size_type LEAF_FLAG_BIT = 0xA0000000;
		static const size_type SIZE_BITS     = 0xFFFFFFFF;
		static const size_type MAX_ITEMS_PER_NODE = SIZE_BITS;
		static const size_type MAX_TREE_NODES = POINTER_BITS >> 12;
		static const size_type lower_bound = 0;
		static const size_type upper_bound = 1;
		static const size_type max_dimensions = K;
        /*
#if defined(_MSC_VER) // You can do better MSVC++, this is a constexpr...
		#include <climits>
		static const size_t max_size = LONG_MAX ;
#else
		static const size_t max_size = std::numeric_limits<size_type>::max();
#endif*/

		static size_type next_dimension(size_t dimension){
			return (dimension+1)%max_dimensions;
		}

		// Generic iterator functor to sort by dimension and a given upper/lower bound
		struct less_than_key
		{
			size_type dimension, sorted_bound;

			less_than_key(size_type discriminated_dimension, size_type bound){ 
				dimension = discriminated_dimension; 
				sorted_bound = bound;
			}
			inline bool operator() (const pair_type& key1, const pair_type& key2)
			{
				return (key1.first[sorted_bound][dimension] < key2.first[sorted_bound][dimension]);
			}
		}; 
    };

	template<typename KDTreeTraits> struct kd_tree_node {
		typedef typename KDTreeTraits::size_type size_type;
		typedef typename KDTreeTraits::discriminator_type discriminator_type;

		kd_tree_node() : left_child(-1), right_child(-1), leaf_flag(false), first_item(0), num_items(0) {}

		inline bool is_leaf(){ return leaf_flag; }
		inline bool is_empty(){ return num_items == 0; }
		inline void mark_as_leaf(){ leaf_flag = true; }
		inline size_type get_num_items(){ return num_items; }
		inline void set_num_items(size_type nitems){ num_items = nitems; }
		inline void set_first_item(size_type index){ first_item = index; }
		inline void set_left_child(size_type child){ left_child = child; }
		inline void set_right_child(size_type child){ right_child = child; }
		inline size_type get_left_child(){ return left_child; }
		inline size_type get_right_child(){ return right_child; }
		inline bool has_right_child(){ return right_child != size_type(-1); }
		inline bool has_left_child(){ return left_child != size_type(-1); }
		inline void set_discriminator(discriminator_type disc){ discriminator = disc; }
		inline discriminator_type get_discrminator(){ return discriminator; }
		inline void set_dimension(size_type dimension){ dimension = dimension; }
		inline size_type get_dimension(){ return dimension; }

	private:
		size_type left_child, right_child; /* Index of the child nodes */
		bool leaf_flag; /** Only leafs contain items */
		size_type first_item; /** Index into the first contained item in this leaf */
		size_type num_items; /** Number of contained items if this a leaf */
		size_type dimension; /** Dimension where the splitting plane is placed i.e {x, y, z}*/
		discriminator_type discriminator; /** splitting plane position along the discriminating dimension (i.e. x's value where the plane is placed)*/
	};

	template<typename KDTreeTraits> struct compact_kd_tree_node {

		compact_kd_tree_node() : left_child(0) {}

		typedef typename KDTreeTraits::size_type size_type;

		static const size_type LEAF_FLAG = KDTreeTraits::LEAF_FLAG_BIT;
		static const size_type CHILD_POINTER_BITS =  KDTreeTraits::POINTER_BITS;
		static const size_type SIZE_FLAG = KDTreeTraits::SIZE_BITS;

		typename KDTreeTraits::discriminator_type axis;

		inline bool is_leaf(){ return left_child & LEAF_FLAG; };
		size_type left_child;

		bool is_empty(){ return this->left_child&SIZE_FLAG == 0; }
		void mark_as_leaf(){ this->left_child |= LEAF_FLAG; }
		size_type get_num_nodes(){ return this->left_child&SIZE_FLAG; }
		void set_num_items(size_type num_nodes){ this->left_child |= num_nodes&CHILD_POINTER_BITS; }
		size_type get_first_items(){ return this->left_child&CHILD_POINTER_BITS; }
		void set_first_node(size_type node_position){ this->left_child |= node_position&CHILD_POINTER_BITS; }

	private:
        
	};

	

    template <
		typename Key, 
		typename Value, 
		size_t K=3, 
		typename Discrminator=shz::math::f32,
		typename DiscriminatorCategory=plane_roundrobin_discriminator_tag,
		typename TreeTraits=default_kd_tree_traits<Key, Value, K, Discrminator> >
    struct kd_tree {

        typedef TreeTraits traits;
        typedef typename traits::key_type key_type; 
		typedef typename traits::value_type value_type;
		typedef typename traits::size_type size_type;
		typedef typename traits::pointer pointer;
		typedef typename traits::reference reference;
		typedef typename traits::const_pointer const_pointer;
		typedef typename traits::const_reference const_reference;
		typedef typename traits::discriminator_type discriminator_type;
		typedef kd_tree_node<traits> node_type;
		typedef typename traits::pair_type pair_type;
		typedef plane_discriminator_category<traits, DiscriminatorCategory> discriminator_category_type;

        
    protected:
        std::vector<node_type> nodes; /** All nodes in the tree, orderes from to top to lowest-left node */
		std::vector<pair_type> items; /** All items in the tree orderes in the same fasion as the nodes */
		Key key_bounds; /** Stores the size of the entire key space (ie, upper and lower limits of the enclosing boundingbox of the entire tree) */
		
    public:
		/** 
		 * Given a set of pair_type objects, iteratively build the tree by paritioning the set 
		 * 	
		 * The tree is stored in a compact from, where the top node is the first item in the node's list, its childs
		 * are stored secuentally and so on, very similir to a binary tree.
         * 
		 * The discriminator algorithm is selected in compile time depending on the DiscriminatorCategory 
		 * (defaults to plane_roundrobin_discriminator_tag). 
		  * 
		 * @param start The start iterator to the input set
		 * #param end The end position iterator for the input set
		 * 
		 */

		template<class InputIterator> inline void build_from_set(InputIterator start, InputIterator end) {
			std::vector<pair_type> vec(start, end);
			std::stack<std::vector<pair_type> > sets_stack;
			std::stack<node_type> nodes_stack;
            

			if(vec.size() > traits::MAX_TREE_NODES)
				throw kdtree_max_nodes_overflow_exception("input number of nodes exceeds tree capacity");

			items.clear();
			nodes.clear();

			size_t dimension = 0;

			key_bounds = compute_set_limits(vec); // Get upper and lower limits of the whole input set of keys

			nodes_stack.push(node_type());
			sets_stack.push(vec);  // The working set is  the whole input set at this point		

			while(!sets_stack.empty()){ // while we have more sets to work on, continue
				auto current_set = sets_stack.top();
				sets_stack.pop();
				node_type current_node = nodes_stack.top();
				nodes_stack.pop();
                
				if(current_set.empty()){
					// The current set is empty so the current sub-tree is done
					current_node.mark_as_leaf();
					current_node.set_num_items(0);
					nodes.push_back(current_node);

					continue;
				}
                
				// Discriminating algorithm
                discriminator_category_type plane_discriminator(dimension);

				std::vector<pair_type> left_set, right_set;
				// get the dimension along we are partitioning the space, and the value along that axis where our splitting 
				// plane is placed.This informantion is stored in a tuple -> 'disciminator_params'
				auto discriminator_params = plane_discriminator.choose_plane(current_set.begin(), current_set.end());
				if(!plane_discriminator.partition_set(discriminator_params, current_set, left_set, right_set)){
					// The cost of partition is equal or higher than no partition at all
					current_node.mark_as_leaf();
					current_node.set_first_item(items.size());
					current_node.set_num_items(current_set.size());
					nodes.push_back(current_node);
					
					std::move(std::begin(current_set), std::end(current_set), std::back_inserter(items));
				} else{
					// Generate two subtrees, one for each sub partition of the current set
					node_type left_node, right_node;

					current_node.set_left_child(nodes.size()+1);
					current_node.set_right_child(nodes.size()+2);
					current_node.set_dimension(std::get<0>(discriminator_params));
					current_node.set_discriminator(std::get<1>(discriminator_params));
					
					nodes.push_back(current_node);
					nodes_stack.push(left_node);
					nodes_stack.push(right_node);
					
					sets_stack.push(left_set);
					sets_stack.push(right_set);
				}
                
                
			}

		}
              
        kd_tree() { }
		/** We consider here that a key-value pair is passed to this constructor */
        /*template<class InputIterator> kd_tree(InputIterator first, InputIterator last) {
			build_from_set(first, last);
		}*/
        inline kd_tree& operator = (const kd_tree<Key, Value>& other) { }
        
		inline size_type size() const { return items.size(); }
        inline size_type max_size() const { return size_type(-1); }
        inline bool empty() const { return size() == size_type(); }

	private:

		/** 
		 * Computes the upper and lower limits of the given set. For a Key of type shz::math::bbox, 
		 * that bould be a bbox enclosing the entire given set of keys. We do this by sorting
		 * the set for each dimension (i.e x, y, z) and storing the upper and lower limits.
		 *
		 * This is done by sorting in each dimension for the upper and lower bounds. Could be done
		 * better but this is done once per tree build.
		 */
		Key compute_set_limits(std::vector<typename traits::pair_type> &input_set){
			Key bounds;

			for(size_t current_dimension = 0; current_dimension < Key::num_dimensions; current_dimension++){
				std::sort(
                      std::begin(input_set),
                      std::end(input_set),
                      typename traits::less_than_key(current_dimension, traits::lower_bound));

				bounds[current_dimension][traits::lower_bound] = input_set[0].first[current_dimension][traits::lower_bound];

				std::sort(
                      std::begin(input_set),
                      std::end(input_set),
                      typename traits::less_than_key(current_dimension, traits::upper_bound));
				
				bounds[current_dimension][traits::upper_bound] = input_set[0].first[current_dimension][traits::upper_bound];

			}

			return bounds;
		}
		
    };
} }

#endif // __SHZ_MATH_KD_TREE__