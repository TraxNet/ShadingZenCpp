#ifndef __SHZ_MATH_RAY__
#define __SHZ_MATH_RAY__

#include <array>
#include <stdexcept> 
#include <limits>
#include <shz/math/math.hpp>
#include <shz/math/vector.hpp>

namespace shz{ namespace math{

	template<typename T> struct ray{

		ray(){}
		ray(vector<T, 3> origin, vector<T, 3> direction, T length = std::numeric_limits<T>::max(), T radius = T()){ 
			this->origin = origin; 
			this->direction = direction; 
			this->length = length; 
			this->radius = radius;
		}
		ray(T originx, T originy, T originz, T dirx, T diry, T dirz, T length = std::numeric_limits<T>::max(), T radius = T()){
			origin.x = originx;
			origin.y = originy;
			origin.z = originz;
			direction.x = dirx;
			direction.y = diry;
			direction.z = dirz;
			this->length = length;
			this->radius = radius;
		}

		vector<T, 3> origin, direction;
		T length;
		T radius;
	};
} }

#endif // __SHZ_MATH_RAY__