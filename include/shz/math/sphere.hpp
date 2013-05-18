#ifndef __SHZ_MATH_SPHERE__
#define __SHZ_MATH_SPHERE__

#include <array>
#include <stdexcept> 
#include <shz/math/math.hpp>

namespace shz{ namespace math{

	template<typename T> struct sphere{

		sphere(){}
		sphere(vector<T, 3> center, T radius){ this->center = center; }
		sphere(T x, T y, T z, T radius){ center = vector<T, 3>(x, y, z); this->radius = radius; }

		vector<T, 3> center;
		T radius;
	};
} }

#endif // __SHZ_MATH_SPHERE__