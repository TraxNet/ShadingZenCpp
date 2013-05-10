#ifndef __SHZ_MATH_PLANE__
#define __SHZ_MATH_PLANE__

#include <array>
#include <shz/math/math.hpp>
#include <shz/math/vector.hpp>

namespace shz{ namespace math{

	template <typename T> struct plane {
		typedef T underlaying_type;
		typedef T* underlaying_type_pointer;
		typedef const T* underlaying_type_const_pointer;
		typedef T& underlaying_type_reference;
		typedef const T& underlaying_type_const_reference;

		plane(){}
		plane(T a, T b, T c, T d){ eq[0] = a; eq[1] = b; eq[2] = c; eq[3] = d; }
		plane(vector<T, 3> n, T d){ eq[0] = n.data[0]; eq[1] = n.data[1]; eq[2] = n.data[2]; eq[3] = d; }

		underlaying_type_reference operator [] (size_t pos){ return eq[pos]; }
		underlaying_type_const_reference operator [] (size_t pos) const { return eq[pos]; }

		T length(){
			return shz::math::vector<T, 3>::dot(eq.data(), eq.data());
		}
		inline T sqrtlength() const {
			return vector<T,3>::sqrtlength(eq.data());
		}

		bool is_point_behind(T x, T y, T z) {
			return eq[0]*x + eq[1]*y + eq[2]*z + eq[3] <= 0.f;
		}
		bool is_point_behind(vector<T, 3>& p) {
			return eq[0]*p.x + eq[1]*p.y + eq[2]*p.z + eq[3] <= 0.f;
		}
		bool is_point_behind(vector<T, 4>& p) {
			return eq[0]*p.x + eq[1]*p.y + eq[2]*p.z + eq[3] <= 0.f;
		}

		bool is_sphere_behind(T x, T y, T z, T radius) {
			return eq[0]*x + eq[1]*y + eq[2]*z + eq[3] <= -radius;
		}

		union {
			struct { T a, b, c, d; };
			std::array<T, 4> eq;
		};
		
	};

} }

#endif // __SHZ_MATH_PLANE__