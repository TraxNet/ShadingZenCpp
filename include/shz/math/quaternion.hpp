#ifndef __SHZ_MATH_QUATERNION__
#define __SHZ_MATH_QUATERNION__

#include <array>
#include <shz/math/math.hpp>
#include <shz/math/matrix.hpp>

namespace shz{ namespace math{

	template <typename T> struct quaternion
	{
		typedef T underlaying_type;
		typedef T* underlaying_type_pointer;
		typedef const T* underlaying_type_const_pointer;
		typedef T& underlaying_type_reference;
		typedef const T& underlaying_type_const_reference;

		quaternion(){}
		quaternion(shz::math::vector<T, 3> v, T angle){
			set_rotation(v.data[0], v.data[1], v.data[2], angle);
		}
		quaternion(T x, T y, T z, T angle){
			set_rotation(x, y, z, angle);
		}

		underlaying_type_reference operator [] (size_t pos){ return data[pos]; }
		underlaying_type_const_reference operator [] (size_t pos) const { return data[pos]; }

		void set_rotation(T x, T y, T z, T angle){
			T half = angle*0.5;
			T s = ::sin(half);
			data[0] = x*s;
			data[1] = y*s;
			data[2] = z*s;
			data[3] = ::cos(half);
		}
		void to_matrix(shz::math::matrix<T, 4, 4>& matrix){
			T x2, y2, z2, xx, xy, xz, yy, yz, zz, wx, wy, wz;

			// calculate coefficients
			x2 = x + x;
			y2 = y + y;
			z2 = z + z;

			xx = x * x2;   xy = x * y2;   xz = x * z2;
			yy = y * y2;   yz = y * z2;   zz = z * z2;
			wx = w * x2;   wy = w * y2;   wz = w * z2;

			matrix.data[0] = 1.0f - (yy + zz);
			matrix.data[1] = xy - wz;
			matrix.data[2] = xz + wy;
			matrix.data[3] = 0.0f;

			matrix.data[4] = xy + wz;
			matrix.data[5] = 1.0f - (xx + zz);
			matrix.data[6] = yz - wx;
			matrix.data[7] = 0.0f;

			matrix.data[8] = xz - wy;
			matrix.data[9] = yz + wx;
			matrix.data[10] = 1.0f - (xx + yy);
			matrix.data[11] = 0.0f;

			matrix.data[12] = 0.0f;
			matrix.data[13] = 0.0f;
			matrix.data[14] = 0.0f;
			matrix.data[15] = 1.0f;
		}

		static inline void mul(T* left, T* right, T* target){
			target[0] = +left[0] *right[3] + left[1] *right[2] - left[2] *right[1] + left[3] *right[0];
			target[1] = -left[0] *right[2] + left[1] *right[3] + left[2] *right[0] + left[3] *right[1];
			target[2] = +left[0] *right[1] - left[1] *right[0] + left[2] *right[3] + left[3] *right[2];
			target[3] = -left[0] *right[0] - left[1] *right[1] - left[2] *right[2] + left[3] *right[3];
		}
		static inline void mul(T* left, T value, T* target){

		}
		static inline T dot(T* left, T* right){
			return left[0]*right[0] + left[1]*right[1] + left[2]*right[2] + left[3]*right[3]; 
		}
		static inline void slerp(T* start, T* end, T alpha){
			// TODO
		}

		union{
			struct{ T x, y, z, w; };
			std::array<T, 4> data;
		};
		
	};

} }


#endif // __SHZ_MATH_QUATERNION__