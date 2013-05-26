#ifndef __SHZ_MATH_KD_TREE__
#define __SHZ_MATH_KD_TREE__

#include <array>
#include <stdexcept> 
#include <limits>
#include <tuple>
#include <stack>
#include <shz/math/math.hpp>
#include <shz/spatial/kd_tree_discriminators.hpp>

namespace shz{ namespace spatial{

    template <typename KeyType, typename ValueType, size_t K, typename Discriminator> struct kd_tree_trais {
		typedef KeyType key_type;
		typedef ValueType value_type;
		typedef size_t size_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;  
		typedef Discriminator discriminator_type;
		typedef std::pair<key_type, value_type> pair_type;

		static const size_t lower_bound = 0;
		static const size_t upper_bound = 1;
		static const size_t max_dimensions = K;
        /*
#if defined(_MSC_VER) // You can do better MSVC++, this is a constexpr...
		#include <climits>
		static const size_t max_size = LONG_MAX ;
#else
		static const size_t max_size = std::numeric_limits<size_type>::max();
#endif*/

		static size_t next_dimension(size_t dimension){
			return (dimension+1)%max_dimensions;
		}

		// Generic iterator functor to sort by dimension and a given upper/lower bound
		struct less_than_key
		{
			size_t dimension, sorted_bound;

			less_than_key(size_t discriminated_dimension, size_t bound){ 
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
		typename KDTreeTraits::discriminator_type axis;
		inline bool is_leaf(){ };
		size_t left_child;
        
	};

	

    template <
		typename Key, 
		typename Value, 
		size_t K=3, 
		typename Discrminator=shz::math::f32,
		typename DiscriminatorCategory=plane_roundrobin_discriminator_tag>
    struct kd_tree {

        typedef kd_tree_trais<Key, Value, K, Discrminator> traits;
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
        size_type numNodes;

		template<class InputIterator> inline void build_from_set(InputIterator start, InputIterator end) {
			std::vector<pair_type> vec(start, end);
			std::stack<std::vector<pair_type>> sets_stack;
            std::vector<node_type> nodes;
            

			size_t dimension = 0;

			sets_stack.push(vec);

			while(!sets_stack.empty()){
				auto current_set = sets_stack.top();
				sets_stack.pop();
                
                
				if(current_set.empty()){
					// TODO: Make an empty leaf
					continue;
				}
                
                node_type current_node;
                
                discriminator_category_type plane_discriminator(dimension);


				std::vector<pair_type> left_set, right_set;
				auto discriminator_params = plane_discriminator.choose_plane(current_set.begin(), current_set.end());
				if(!plane_discriminator.partition_set(discriminator_params, current_set, left_set, right_set)){
					// The cost of partition is equal or higher than no partition at all
					// TODO: Make this a leaf node

				} else{
					// TODO: Create child nodes

					sets_stack.push(left_set);
					sets_stack.push(right_set);
				}
                
                
			}
		}
        
    public:
              
        kd_tree() : numNodes(size_type()) { }
		/** We consider here that a key-value pair is passed to this constructor */
        template<class InputIterator> kd_tree(InputIterator first, InputIterator last) {
			build_from_set(first, last);
		}
        inline kd_tree& operator = (const kd_tree<Key, Value>& other) { }
        
        inline size_type size() const { return numNodes; }
        inline size_type max_size() const { return size_type(-1); }
        inline bool empty() const { return size() == size_type(); }
    };
} }

#endif // __SHZ_MATH_KD_TREE__