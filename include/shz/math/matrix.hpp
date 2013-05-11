#ifndef __SHZ_MATH_MATRIX__
#define __SHZ_MATH_MATRIX__

#include <array>
#include <stdexcept> 
#include <shz/math/math.hpp>
#include <shz/math/vector.hpp>

namespace shz{ namespace math{
		
	template <typename T, int C, int R> struct matrix
	{
		typedef T underlaying_type;
		typedef T* underlaying_type_pointer;
		typedef const T* underlaying_type_const_pointer;
		typedef T& underlaying_type_reference;
		typedef const T& underlaying_type_const_reference;

		static const size_t size = C*R;
		static const size_t mindimension = shz::math::static_unsigned_min<C, R>::value;
		static const size_t columns = C;
		static const size_t rows = R;

		matrix(){}
		matrix(const T* data){ std::copy(data, data+size, this->data.begin()); }		

		matrix<T, C, R> operator + (const matrix<T, C, R>& other) const { matrix<T, C, R> t; matrix<T, C, R>::add(&this->data[0], &other.data[0], &t.data[0]); return t; }
		matrix<T, C, R> operator + (const T value){ matrix<T, C, R> t; matrix<T, C, R>::add(&t.data[0], value, &t.data[0]); return t; }
		matrix<T, C, R>& operator += (const matrix<T, C, R>& other){ matrix<T, C, R>::add(&this->data[0], &other.data[0], &this->data[0]); return *this; }
		matrix<T, C, R>& operator += (const T value){ matrix<T, C, R>::add(&this->data[0], value, &this->data[0]); return *this; }

		matrix<T, C, R> operator - (const matrix<T, C, R>& other){ matrix<T, C, R> t; matrix<T, C, R>::sub(&this->data[0], &other.data[0], &t.data[0]); return t; }
		matrix<T, C, R> operator - (const T value){ matrix<T, C, R> t; matrix<T, C, R>::sub(&this->data[0], value, &t.data[0]); return t; }
		matrix<T, C, R>& operator -= (const matrix<T, C, R>& other){ matrix<T, C, R>::sub(&this->data[0], &other.data[0], &this->data[0]); return *this; }
		matrix<T, C, R>& operator -= (const T value){ matrix<T, C, R>::sub(&this->data[0], value, &this->data[0]); return *this; }

		matrix<T, mindimension, mindimension> operator * (const matrix<T, R, C>& other) const { matrix<T, mindimension, mindimension> ret; mul(&this->data[0], &other.data[0], &ret.data[0]); return ret; }
		matrix<T, mindimension, mindimension> operator * (const T value) const { matrix<T, R, C> t; matrix<T, C, R>::mul(&this->data[0], value, &t.data[0]); return t; }
		matrix<T, C, R>& operator *= (const matrix<T, C, R>& other){ matrix<T, R, C> left(*this); matrix<T, C, R>::mul(&left.data[0], other.data[0], &this->data[0]); return *this; }
		matrix<T, C, R>& operator *= (const T value){ matrix<T, R, C> left(*this); matrix<T, C, R>::mul(&left.data[0], value, &this->data[0]); return *this; }
		vector<T, C> operator * (const vector<T, C>& other) const { vector<T, C> ret;  matrix<T, C, R>::mul_vec(&this->data[0], &other.data[0], &ret.data[0]); return ret; }

		underlaying_type_reference operator [] (size_t pos){ return data[pos]; }
		underlaying_type_const_reference operator [] (size_t pos) const { return data[pos]; }

		static inline void add(const T* left, const T* right, T* target){
			for(size_t i=0; i < C*R; ++i){
				*target = *left + *right;
				left++; right++; target++;
			}
		}
		static inline void add(const T* left, const T value, T* target){
			for(size_t i=0; i < C*R; ++i)
				target[i] = left[i] + value;
		}
		static inline void sub(const T* left, const T* right, T* target){
			for(size_t i=0; i < C*R; ++i){
				*target = *left - *right;
				left++; right++; target++;
			}
		}
		static inline void sub(const T* left, const T value, T* target){
			for(size_t i=0; i < C*R; ++i)
				target[i] = left[i] - value;
		}
		static inline void  mul(const T* left, const T*right, T* target) {
			T left_transposed[size];
			matrix<T, C, R>::transpose(left, left_transposed);
					
			for(size_t m=0; m<mindimension; ++m){
				T* transposed = left_transposed;

				for(size_t n=0; n<mindimension; ++n){
					*target = T();

					for(size_t i=0; i<R; ++i){
						T a = *(transposed + i);
						T b = *(right + i);
						*target += a*b;
					}

					target++;
					transposed += C;
				}

				right += C;
			}
		}
		static inline void mul(const T* left, const T value, T *target){
			for(size_t i=0; i < C*R; ++i)
				target[i] = left[i]*value;
		}
		static inline void mul_vec(const T* left, const T* right, T* target) {
			for(size_t m=0; m<R; ++m){
				*target = T();
				for(size_t n=0; n<C; ++n){
					*target += left[m*R + n]*right[n];
				}
				target++;
			}
		}
		static inline void transpose(const T* left, T* target){
			for(size_t n=0; n<C; ++n){
				for(size_t m=0; m<R; ++m){
					target[n*R + m] = left[m*C + n];
				}
			}
		}
		inline matrix<T, R, C> transpose() const {
			matrix<T, R, C> result;
			matrix<T, C, R>::transpose(&data[0], &result.data[0]);

			return result;
		}
		static inline bool is_identity(const matrix<T, C, R>& matrix) {
			size_t next_one_position = 0;
			for(size_t i=0; i < matrix.size; i++){
				if(i == next_one_position){
					if(1.0 != (double)matrix.data[i])
						return false;
					next_one_position += R + 1;
				} else{
					if(T() != matrix.data[i])
						return false;
				}
			}

			return true;
		}
		inline bool is_identity() const {
			return matrix<T, C, R>::is_identity(*this);
		}

		static inline matrix<T, C, R> identity(){
			matrix<T, C, R> ret;

			size_t next_one_position = 0;
			for(size_t i=0; i<size; ++i){
				if(i == next_one_position){
					ret.data[i] = 1;
					next_one_position += R+1;
				} else{
					ret.data[i] = 0;
				}
			}

			return ret;
		}		
			
		std::array<T, size> data;
	};

	template <> struct _ALIGNED(16) matrix<typename shz::math::f32, 4, 4>
	{

		static const size_t size = 4*4;
		static const size_t mindimension = shz::math::static_unsigned_min<4, 4>::value;
		static const size_t columns = 4;
		static const size_t rows = 4;

		matrix(){}
		matrix(const shz::math::f32* data){ std::copy(data, data+size, this->data.begin()); }		

		matrix<shz::math::f32, 4, 4> operator + (const matrix<shz::math::f32, 4, 4>& other) const { matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::add(&this->data[0], &other.data[0], &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4> operator + (const shz::math::f32 value) const { matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::add(&t.data[0], value, &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4>& operator += (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, 4, 4>::add(&this->data[0], &other.data[0], &this->data[0]); return *this; }
		matrix<shz::math::f32, 4, 4>& operator += (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4>::add(&this->data[0], value, &this->data[0]); return *this; }

		matrix<shz::math::f32, 4, 4> operator - (const matrix<shz::math::f32, 4, 4>& other) const { matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::sub(&this->data[0], &other.data[0], &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4> operator - (const shz::math::f32 value) const { matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::sub(&this->data[0], value, &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4>& operator -= (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, 4, 4>::sub(&this->data[0], &other.data[0], &this->data[0]); return *this; }
		matrix<shz::math::f32, 4, 4>& operator -= (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4>::sub(&this->data[0], value, &this->data[0]); return *this; }

		matrix<shz::math::f32, mindimension, mindimension> operator * (const matrix<shz::math::f32, 4, 4>& other) const { matrix<shz::math::f32, mindimension, mindimension> ret; mul(&this->data[0], &other.data[0], &ret.data[0]); return ret; }
		matrix<shz::math::f32, mindimension, mindimension> operator * (const shz::math::f32 value) const { matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::mul(&this->data[0], value, &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4>& operator *= (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, 4, 4> left(*this); matrix<shz::math::f32, 4, 4>::mul(&left.data[0], other.data[0], &this->data[0]); return *this; }
		matrix<shz::math::f32, 4, 4>& operator *= (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4> left(*this); matrix<shz::math::f32, 4, 4>::mul(&left.data[0], value, &this->data[0]); return *this; }
		vector<shz::math::f32, 4> operator * (const vector<shz::math::f32, 4>& other) const { vector<shz::math::f32, 4> ret;  matrix<shz::math::f32, 4, 4>::mul_vec(&this->data[0], &other.data[0], &ret.data[0]); return ret; }

		f32& operator [] (size_t pos){ return data[pos]; }
		const f32& operator [] (size_t pos) const { return data[pos]; }

		static void add(const shz::math::f32* left, const shz::math::f32* right, shz::math::f32* target);
		static void add(const shz::math::f32* left, const shz::math::f32 value, shz::math::f32* target);
		static void sub(const shz::math::f32* left, const shz::math::f32* right, shz::math::f32* target);
		static void sub(const shz::math::f32* left, const shz::math::f32 value, shz::math::f32* target);
		static void mul(const shz::math::f32* left, const shz::math::f32*right, shz::math::f32* target);
		static void mul(const shz::math::f32* left, const shz::math::f32 value, shz::math::f32 *target);
		static void mul_vec(const shz::math::f32* left, const shz::math::f32* right, shz::math::f32* target);
		static void transpose(const shz::math::f32* left, shz::math::f32* target);

		inline matrix<shz::math::f32, 4, 4> transpose() const {
			matrix<shz::math::f32, 4, 4> result;
			matrix<shz::math::f32, 4, 4>::transpose(&data[0], &result.data[0]);

			return result;
		}
		static inline bool is_identity(const matrix<shz::math::f32, 4, 4>& matrix) {
			size_t next_one_position = 0;
			for(size_t i=0; i<size; i++){
				if(i == next_one_position){
					if(1.0 != (double)matrix.data[i])
						return false;
					next_one_position += 4 + 1;
				} else{
					if(shz::math::f32() != matrix.data[i])
						return false;
				}
			}

			return true;
		}
		inline bool is_identity() const {
			return matrix<shz::math::f32, 4, 4>::is_identity(*this);
		}

		static inline matrix<shz::math::f32, 4, 4> identity(){
			matrix<shz::math::f32, 4, 4> ret;

			size_t next_one_position = 0;
			for(size_t i=0; i<size; ++i){
				if(i == next_one_position){
					ret.data[i] = 1;
					next_one_position += 4+1;
				} else{
					ret.data[i] = 0;
				}
			}

			return ret;
		}

		static inline void set_rotation(const f32* axis, f32 radians, f32* target) {
			target[3] = 0;
			target[7] = 0;
			target[11]= 0;
			target[12]= 0;
			target[13]= 0;
			target[14]= 0;
			target[15]= 1;
			f32 s = ::sin(radians);
			f32 c = ::cos(radians);
			if (1.0f == axis[0] && 0.0f == axis[1] && 0.0f == axis[2]) {
				target[5] = c;   target[10]= c;
				target[6] = s;   target[9] = -s;
				target[1] = 0;   target[2] = 0;
				target[4] = 0;   target[8] = 0;
				target[0] = 1;
			} else if (0.0f == axis[0] && 1.0f == axis[1] && 0.0f == axis[2]) {
				target[0] = c;   target[10]= c;
				target[8] = s;   target[2] = -s;
				target[1] = 0;   target[4] = 0;
				target[6] = 0;   target[9] = 0;
				target[5] = 1;
			} else if (0.0f == axis[0] && 0.0f == axis[1] && 1.0f == axis[2]) {
				target[0] = c;   target[5] = c;
				target[1] = s;   target[4] = -s;
				target[2] = 0;   target[6] = 0;
				target[8] = 0;   target[9] = 0;
				target[10]= 1;
			} else {
				f32 axis_n[3];
				vector3f::normalize(axis, axis_n);

				f32 nc = 1.0f - c;
				f32 xy = axis_n[0] * axis_n[1];
				f32 yz = axis_n[1] * axis_n[2];
				f32 zx = axis_n[2] * axis_n[0];
				f32 xs = axis_n[0] * s;
				f32 ys = axis_n[1] * s;
				f32 zs = axis_n[2] * s;
				target[ 0] = axis_n[0]*axis_n[0]*nc +  c;
				target[ 4] =  xy*nc - zs;
				target[ 8] =  zx*nc + ys;
				target[ 1] =  xy*nc + zs;
				target[ 5] = axis_n[1]*axis_n[1]*nc +  c;
				target[ 9] =  yz*nc - xs;
				target[ 2] =  zx*nc - ys;
				target[ 6] =  yz*nc + xs;
				target[10] = axis_n[2]*axis_n[2]*nc +  c;
			}
		}

		static inline matrix<f32, 4, 4> from_rotation(const vector<f32, 3>& axis, f32 radians){
			matrix<f32, 4, 4> ret;
			matrix<f32, 4, 4>::set_rotation(&axis.data[0], radians, ret.data.data());
			return ret;
		}

		static inline matrix<f32, 4, 4> from_rotation(f32 x, f32 y, f32 z, f32 radians){
			matrix<f32, 4, 4> ret;
			f32 input[3] = { x, y, z };

			matrix<f32, 4, 4>::set_rotation(input, radians, ret.data.data());
			return ret;
		}

		/**
		* Define a projection matrix in terms of six clip planes
		* @param left
		* @param right
		* @param bottom
		* @param top
		* @param near
		* @param far
		*/
		static inline matrix<f32, 4, 4> frustum(f32 left, f32 right, f32 bottom, float top, float near, float far) {
				if (left == right) {
					throw std::invalid_argument("left == right");
				}
				if (top == bottom) {
					throw std::invalid_argument("top == bottom");
				}
				if (near == far) {
					throw std::invalid_argument("near == far");
				}
				if (near <= 0.0f) {
					throw std::invalid_argument("near <= 0.0f");
				}
				if (far <= 0.0f) {
					throw std::invalid_argument("far <= 0.0f");
				}

				matrix<f32, 4, 4> m;
				const f32 r_width  = 1.0f / (right - left);
				const f32 r_height = 1.0f / (top - bottom);
				const f32 r_depth  = 1.0f / (near - far);
				const f32 x = 2.0f * (near * r_width);
				const f32 y = 2.0f * (near * r_height);
				const f32 A = 2.0f * ((right + left) * r_width);
				const f32 B = (top + bottom) * r_height;
				const f32 C = (far + near) * r_depth;
				const f32 D = 2.0f * (far * near * r_depth);
				m[0] = x;
				m[5] = y;
				m[8] = A;
				m[ 9] = B;
				m[10] = C;
				m[14] = D;
				m[11] = -1.0f;
				m[ 1] = 0.0f;
				m[ 2] = 0.0f;
				m[ 3] = 0.0f;
				m[ 4] = 0.0f;
				m[ 6] = 0.0f;
				m[ 7] = 0.0f;
				m[12] = 0.0f;
				m[13] = 0.0f;
				m[15] = 0.0f;
		}

		 /**
		 * Computes an orthographic projection matrix.
		 *
		 * @param left
		 * @param right
		 * @param bottom
		 * @param top
		 * @param near
		 * @param far
		 */
		static inline matrix<f32, 4, 4> ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
			if (left == right) {
				throw std::invalid_argument("left == right");
			}
			if (top == bottom) {
				throw std::invalid_argument("top == bottom");
			}
			if (near == far) {
				throw std::invalid_argument("near == far");
			}

			matrix<f32, 4, 4> m;

			const f32 r_width  = 1.0f / (right - left);
			const f32 r_height = 1.0f / (top - bottom);
			const f32 r_depth  = 1.0f / (far - near);
			const f32 x =  2.0f * (r_width);
			const f32 y =  2.0f * (r_height);
			const f32 z = -2.0f * (r_depth);
			const f32 tx = -(right + left) * r_width;
			const f32 ty = -(top + bottom) * r_height;
			const f32 tz = -(far + near) * r_depth;
			m[ 0] = x;
			m[ 5] = y;
			m[10] = z;
			m[12] = tx;
			m[13] = ty;
			m[14] = tz;
			m[15] = 1.0f;
			m[ 1] = 0.0f;
			m[ 2] = 0.0f;
			m[ 3] = 0.0f;
			m[ 4] = 0.0f;
			m[ 6] = 0.0f;
			m[ 7] = 0.0f;
			m[ 8] = 0.0f;
			m[ 9] = 0.0f;
			m[ 11] = 0.0f;
		}

		union{
			std::array<shz::math::f32, size> data;
		};
	};

	typedef shz::math::matrix<shz::math::f32, 4, 4> matrix4f;
	typedef shz::math::matrix<shz::math::f64, 4, 4> matrix4d;
} }

#endif // __SHZ_MATH_MATRIX__
