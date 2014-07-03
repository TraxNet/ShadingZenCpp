#ifndef __SHZ_MATH_KD_TREE_DISCRIMINATORS__
#define __SHZ_MATH_KD_TREE_DISCRIMINATORS__

namespace shz{ namespace spatial{ 

	struct plane_discriminator_tag { };
	struct sah_boxplanes_plane_discriminator_tag : public plane_discriminator_tag { };
	struct plane_roundrobin_discriminator_tag : public plane_discriminator_tag { };

	template<typename KDTreeTraits, typename Tag> struct plane_discriminator_category { };

	template<typename KDTreeTraits> struct plane_discriminator_category<KDTreeTraits, sah_boxplanes_plane_discriminator_tag> {
		plane_discriminator_category(size_t dimension){ }

		/*
		template<class InputIterator> std::tuple<size_t, typename KDTreeTraits::discriminator_type> 
		choose_plane(
			InputIterator& first, 
			InputIterator& last){
				std::tuple<size_t, typename KDTreeTraits::discriminator_type> ret;

				return ret;
		}


		bool partition_set(
			const std::tuple<size_t, typename KDTreeTraits::discriminator_type>& params, 
			std::vector<typename KDTreeTraits::pair_type>& left_set,
			std::vector<typename KDTreeTraits::pair_type>& right_set) {

				return false;
		}*/
	};

	/** 
	 * Round robin discrimintaor partial specialization. The discrinator plane to parition the current set is choosen in 
	 * a round robin secuence. This is the least efficient algorithm to generate a kd-tree.
	 */
	template<typename KDTreeTraits> struct plane_discriminator_category<KDTreeTraits, plane_roundrobin_discriminator_tag> {
		/**
         * Constructor
         *
         * @param depth The current depth of the tree being discriminated
         * @return A tuple with information regarding the choosen discrimination
         * parameters (dimensio, discriminator value)
         */
        plane_discriminator_category(size_t depth)
			: current_depth(depth) { }

		/**
		 * Chooses a discriminator plane which partitions the given set in two. For this
		 * round-robin implementation, the discriminator (axis) is chosen alternatively on
		 * each depth of the tree.
		 *
		 * @return A tuple with information about the discriminating dimension and the exact
		 * value where the plane has been placed.	
		 */
		template<class InputIterator> inline std::tuple<size_t, typename KDTreeTraits::discriminator_type> 
		choose_plane(
			InputIterator start, 
			InputIterator end)
        {
            size_t current_dimension = current_depth%KDTreeTraits::max_dimensions;
            std::tuple<size_t, typename KDTreeTraits::discriminator_type> ret;
            
            std::vector<typename KDTreeTraits::pair_type> elements(start, end);
            std::sort(
                      elements.begin(),
                      elements.end(),
                      typename KDTreeTraits::less_than_key(current_dimension, KDTreeTraits::lower_bound));
            
            std::get<0>(ret) = current_dimension;
				
            auto median = (end - start)/2;
			std::get<1>(ret) = start[median].first[KDTreeTraits::lower_bound][current_dimension];

			return ret;
		}

		/**
		 * Given an input and information about the discriminator plane, parititions the input set into
		 * two sub-sets using their median values (for the plane position). If all the items in the input 
		 * set are in both sub-sets, or one of the sub-sets is empty, returns false to point the caller to
		 * avoid creating two sub-sets

		 * @return If all items are in both partitions or there is an empty partition  we can return false 
		 * so that this is actually not partitioned and a leaf node should be created. Otherwise return true.
		 */
		inline bool partition_set(
			const std::tuple<size_t, typename KDTreeTraits::discriminator_type>& params, 
			std::vector<typename KDTreeTraits::pair_type>& input_set,
			std::vector<typename KDTreeTraits::pair_type>& left_set,
			std::vector<typename KDTreeTraits::pair_type>& right_set)
        {
            typename KDTreeTraits::discriminator_type discriminator;
            typename std::vector<typename KDTreeTraits::pair_type>::size_type items_in_both = 0;
            size_t dimension = current_depth%KDTreeTraits::max_dimensions;
            
			// sort all items acordding to the current dimension and choose the median. That poin is the
			// place where the parition plane is placed.
            std::sort(
                      input_set.begin(),
                      input_set.end(),
                      typename KDTreeTraits::less_than_key(dimension, KDTreeTraits::lower_bound));
            auto median = (input_set.end() - input_set.begin())/2;
            discriminator =
                input_set[median].first[KDTreeTraits::lower_bound][dimension];

            for(auto& pair : input_set){
                if(pair.first[dimension][KDTreeTraits::upper_bound] < discriminator){
                    left_set.push_back(pair);
                } else if(pair.first[dimension][KDTreeTraits::lower_bound] < discriminator
                          && pair.first[dimension][KDTreeTraits::upper_bound] > discriminator) {
                    left_set.push_back(pair);
                    right_set.push_back(pair);
                    items_in_both++;
                } else{
                    right_set.push_back(pair);
                }
            }

            // If all items are in both partitions or there is an empty partition
            // we can return false so that this is actually not partitioned and
            // a leaf node is created.
            if(items_in_both == input_set.size() || right_set.empty() || left_set.empty())
                return false;
            return true;
		}

	protected:
		size_t current_depth;
	};
} };

#endif // __SHZ_MATH_KD_TREE_DISCRIMINATORS__