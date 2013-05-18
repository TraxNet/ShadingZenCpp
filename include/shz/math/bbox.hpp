#ifndef __SHZ_MATH_BBOX__
#define __SHZ_MATH_BBOX__

#include <array>
#include <stdexcept> 
#include <shz/math/math.hpp>

namespace shz{ namespace math{

	template<typename T> struct bbox{

		bbox(){}
		bbox(vector<T, 3> mins, vector<T, 3> maxs){ this->mins = mins; this->maxs = maxs; }
		bbox(T minx, T miny, T minz, T maxx, T maxy, T maxz){
			mins.data[0] = minx;
			mins.data[1] = miny;
			mins.data[2] = minz;
			maxs.data[0] = maxx;
			maxs.data[1] = maxy;
			maxs.data[2] = maxz;
		}
		bbox(vector<T, 3> center, T radius){
			mins = center - radius;
			maxs = center + radius;
		}

		vector<T, 3> mins, maxs;
	};
} }

#endif // __SHZ_MATH_BBOX__