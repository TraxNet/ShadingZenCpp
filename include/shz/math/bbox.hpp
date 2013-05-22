#ifndef __SHZ_MATH_BBOX__
#define __SHZ_MATH_BBOX__

#include <array>
#include <stdexcept> 
//#include <initializer_list>
#include <shz/math/math.hpp>

namespace shz{ namespace math{

	template<typename T, int D=3> struct bbox{
		typedef size_t dimension_type;
		static const dimension_type num_dimensions = D;
		typedef vector<T, num_dimensions> bounds_type;

		bbox(){}
		bbox(bounds_type mins, bounds_type maxs){ lower_bound = mins; upper_bound = maxs; }
		bbox(bounds_type center, T radius){
			mins = center - radius;
			maxs = center + radius;
		}

		union 
		{
			struct{ bounds_type mins, maxs; };
			struct{ bounds_type lower_bound, upper_bound; };
		};
		
	};

	template<> struct _ALIGNED(16) bbox<shz::math::f32, 3>{
		typedef size_t dimension_type;
		static const dimension_type num_dimensions = 3;
		typedef vector<shz::math::f32, 3> _ALIGNED(16) bounds_type;

		bbox(){}
		bbox(bounds_type& mins, bounds_type& maxs){ lower_bound = mins; upper_bound = maxs; }
		bbox(shz::math::f32 minx, shz::math::f32 miny, shz::math::f32 minz, shz::math::f32 maxx, shz::math::f32 maxy, shz::math::f32 maxz){
			mins.data[0] = minx;
			mins.data[1] = miny;
			mins.data[2] = minz;
			maxs.data[0] = maxx;
			maxs.data[1] = maxy;
			maxs.data[2] = maxz;
		}
		bbox(bounds_type& center, shz::math::f32 radius){
			mins = center - radius;
			maxs = center + radius;
		}

		union 
		{
			struct{ bounds_type mins, maxs; };
			struct{ bounds_type lower_bound, upper_bound; };
		};

	};
} }

#endif // __SHZ_MATH_BBOX__