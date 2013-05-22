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
		ray(vector<T, 3>& origin, vector<T, 3>& direction, T length = std::numeric_limits<T>::max(), T radius = T()){ 
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

	template<> struct _ALIGNED(16) ray<shz::math::f32>{

		ray(){}
		ray(vector<shz::math::f32, 3>& origin, vector<shz::math::f32, 3>& direction, shz::math::f32 length = std::numeric_limits<shz::math::f32>::max(), shz::math::f32 radius = 0.f){ 
			this->origin = origin; 
			this->direction = direction; 
			this->length = length; 
			this->radius = radius;
		}
		ray(shz::math::f32 originx, shz::math::f32 originy, shz::math::f32 originz, shz::math::f32 dirx, shz::math::f32 diry, shz::math::f32 dirz, shz::math::f32 length = std::numeric_limits<shz::math::f32>::max(), shz::math::f32 radius = 0.f){
			origin.x = originx;
			origin.y = originy;
			origin.z = originz;
			direction.x = dirx;
			direction.y = diry;
			direction.z = dirz;
			this->length = length;
			this->radius = radius;
		}

		vector<shz::math::f32, 3> origin, direction;
		shz::math::f32 length;
		shz::math::f32 radius;
	};
} }

#endif // __SHZ_MATH_RAY__