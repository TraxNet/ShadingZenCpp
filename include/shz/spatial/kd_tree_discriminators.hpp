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


	template<typename KDTreeTraits> struct plane_discriminator_category<KDTreeTraits, plane_roundrobin_discriminator_tag> {
		plane_discriminator_category(size_t dimension) 
			: current_dimension(dimension) { }

		/**
		 * Chooses a discriminator plane which partitions the given set in two. For this
		 * round-robin implementation, the discriminator (axis) is chosen alternatively on
		 * each depth of the tree.
		 *
		 * @return A tuple with information about the discriminating dimension and the exact
		 * value where the plane has been placed.	
		 */
		template<class InputIterator> std::tuple<size_t, typename KDTreeTraits::discriminator_type> 
		choose_plane(
			InputIterator start, 
			InputIterator end){
				std::tuple<size_t, typename KDTreeTraits::discriminator_type> ret;
				std::get<0>(ret) = current_dimension;
				
				auto median = (end - start)/2;
				std::get<1>(ret) = start[median].first[KDTreeTraits::lower_bound][current_dimension];

				return ret;
		}


		bool partition_set(
			const std::tuple<size_t, typename KDTreeTraits::discriminator_type>& params, 
			std::vector<typename KDTreeTraits::pair_type>& input_set,
			std::vector<typename KDTreeTraits::pair_type>& left_set,
			std::vector<typename KDTreeTraits::pair_type>& right_set) {
				size_t dimension; 
				typename KDTreeTraits::discriminator_type discriminator;
				std::vector<typename KDTreeTraits::pair_type>::size_type items_in_both = 0;

				std::tie(dimension, discriminator) = params;

				for(auto& pair : input_set){
					if(pair.first[dimension][KDTreeTraits::upper_bound] < discriminator){
						left_set.push_back(pair);
					} else if(pair.first[dimension][KDTreeTraits::lower_bound] < discriminator && pair.first[dimension][KDTreeTraits::upper_bound] > discriminator) {
						left_set.push_back(pair);
						right_set.push_back(pair);
						items_in_both++;
					} else{

					}
				}

				if(items_in_both == input_set.size())
					return false;
				return true;
		}

	protected:
		size_t current_dimension;
	};
} };

#endif // __SHZ_MATH_KD_TREE_DISCRIMINATORS__