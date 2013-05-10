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
			set_rotation(v, angle);
		}
		quaternion(T x, T y, T z, T angle){
			set_rotation(x, y, z, angle);
		}

		quaternion<T> operator * (const quaternion<T> & other){ quaternion<T> ret; quaternion<T>::mul(this->data.data(), other.data.data(), ret.data.data()); return ret; }
		//quaternion<T>  operator * (const T value){ quaternion<T>  t; quaternion<T>::mul(this->data.data(), value, t.data.data()); return t; }
		quaternion<T> & operator *= (const quaternion<T> & other){ quaternion<T> left(*this); quaternion<T>::mul(left.data.data(), other.data.data(), this->data.data()); return *this; }
		//quaternion<T> & operator *= (const T value){ quaternion<T> left(*this); quaternion<T>::mul(left.data.data(), value, this->data.data()); return *this; }

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
		void set_rotation(vector<T, 3> axis, T angle){
			T half = angle*0.5;
			T s = ::sin(half);
			data[0] = axis.data[0]*s;
			data[1] = axis.data[1]*s;
			data[2] = axis.data[2]*s;
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
			matrix.data[4] = xy - wz;
			matrix.data[8] = xz + wy;
			matrix.data[12] = 0.0f;

			matrix.data[1] = xy + wz;
			matrix.data[5] = 1.0f - (xx + zz);
			matrix.data[9] = yz - wx;
			matrix.data[13] = 0.0f;

			matrix.data[2] = xz - wy;
			matrix.data[6] = yz + wx;
			matrix.data[10] = 1.0f - (xx + yy);
			matrix.data[14] = 0.0f;

			matrix.data[3] = 0.0f;
			matrix.data[7] = 0.0f;
			matrix.data[11] = 0.0f;
			matrix.data[15] = 1.0f;
		}

		static inline void mul(const T* left, const T* right, T* target){
			target[0] = +left[0] *right[3] + left[1] *right[2] - left[2] *right[1] + left[3] *right[0];
			target[1] = -left[0] *right[2] + left[1] *right[3] + left[2] *right[0] + left[3] *right[1];
			target[2] = +left[0] *right[1] - left[1] *right[0] + left[2] *right[3] + left[3] *right[2];
			target[3] = -left[0] *right[0] - left[1] *right[1] - left[2] *right[2] + left[3] *right[3];
		}
		/*
		static inline void mul(const T* left, T value, T* target){

		}*/
		static inline T dot(const T* left, const T* right){
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