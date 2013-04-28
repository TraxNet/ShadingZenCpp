#ifndef __SHZ_MATH_MATRIX__
#define __SHZ_MATH_MATRIX__

#include <array>
#include <boost/integer/static_min_max.hpp>
#include <shz/math/math.hpp>
#include <shz/math/vector.hpp>

namespace shz{ namespace math{
		
	template <typename T, int C, int R> struct _declspec(align(16)) matrix
	{
		static const size_t size = C*R;
		static const size_t mindimension = ::boost::static_unsigned_min<C, R>::value;
		static const size_t columns = C;
		static const size_t rows = R;

		matrix(){}
		matrix(const T* data){ std::copy(data, data+size, this->data.begin()); }		

		matrix<T, C, R> operator + (const matrix<T, C, R>& other){ matrix<T, C, R> t; matrix<T, C, R>::add(&this->data[0], &other.data[0], &t.data[0]); return t; }
		matrix<T, C, R> operator + (const T value){ matrix<T, C, R> t; matrix<T, C, R>::add(&t.data[0], value, &t.data[0]); return t; }
		matrix<T, C, R>& operator += (const matrix<T, C, R>& other){ matrix<T, C, R>::add(&this->data[0], &other.data[0], &this->data[0]); return *this; }
		matrix<T, C, R>& operator += (const T value){ matrix<T, C, R>::add(&this->data[0], value, &this->data[0]); return *this; }

		matrix<T, C, R> operator - (const matrix<T, C, R>& other){ matrix<T, C, R> t; matrix<T, C, R>::sub(&this->data[0], &other.data[0], &t.data[0]); return t; }
		matrix<T, C, R> operator - (const T value){ matrix<T, C, R> t; matrix<T, C, R>::sub(&this->data[0], value, &t.data[0]); return t; }
		matrix<T, C, R>& operator -= (const matrix<T, C, R>& other){ matrix<T, C, R>::sub(&this->data[0], &other.data[0], &this->data[0]); return *this; }
		matrix<T, C, R>& operator -= (const T value){ matrix<T, C, R>::sub(&this->data[0], value, &this->data[0]); return *this; }

		matrix<T, mindimension, mindimension> operator * (const matrix<T, R, C>& other){ matrix<T, mindimension, mindimension> ret; mul(&this->data[0], &other.data[0], &ret.data[0]); return ret; }
		matrix<T, mindimension, mindimension> operator * (const T value){ matrix<T, R, C> t; matrix<T, C, R>::mul(&this->data[0], value, &t.data[0]); return t; }
		matrix<T, C, R>& operator *= (const matrix<T, C, R>& other){ matrix<T, R, C> left(*this); matrix<T, C, R>::mul(&left.data[0], other.data[0], &this->data[0]); return *this; }
		matrix<T, C, R>& operator *= (const T value){ matrix<T, R, C> left(*this); matrix<T, C, R>::mul(&left.data[0], value, &this->data[0]); return *this; }
		vector<T, C> operator * (const vector<T, C>& other){ vector<T, C> ret;  matrix<T, C, R>::mul_vec(&this->data[0], &other.data[0], &ret.data[0]); return ret; }


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
			for(size_t i=0; i<size; i++){
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

	template <> struct _declspec(align(16)) matrix<typename shz::math::f32, 4, 4>
	{
		static const size_t size = 4*4;
		static const size_t mindimension = ::boost::static_unsigned_min<4, 4>::value;
		static const size_t columns = 4;
		static const size_t rows = 4;

		matrix(){}
		matrix(const shz::math::f32* data){ std::copy(data, data+size, this->data.begin()); }		

		matrix<shz::math::f32, 4, 4> operator + (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::add(&this->data[0], &other.data[0], &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4> operator + (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::add(&t.data[0], value, &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4>& operator += (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, 4, 4>::add(&this->data[0], &other.data[0], &this->data[0]); return *this; }
		matrix<shz::math::f32, 4, 4>& operator += (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4>::add(&this->data[0], value, &this->data[0]); return *this; }

		matrix<shz::math::f32, 4, 4> operator - (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::sub(&this->data[0], &other.data[0], &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4> operator - (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::sub(&this->data[0], value, &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4>& operator -= (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, 4, 4>::sub(&this->data[0], &other.data[0], &this->data[0]); return *this; }
		matrix<shz::math::f32, 4, 4>& operator -= (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4>::sub(&this->data[0], value, &this->data[0]); return *this; }

		matrix<shz::math::f32, mindimension, mindimension> operator * (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, mindimension, mindimension> ret; mul(&this->data[0], &other.data[0], &ret.data[0]); return ret; }
		matrix<shz::math::f32, mindimension, mindimension> operator * (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4> t; matrix<shz::math::f32, 4, 4>::mul(&this->data[0], value, &t.data[0]); return t; }
		matrix<shz::math::f32, 4, 4>& operator *= (const matrix<shz::math::f32, 4, 4>& other){ matrix<shz::math::f32, 4, 4> left(*this); matrix<shz::math::f32, 4, 4>::mul(&left.data[0], other.data[0], &this->data[0]); return *this; }
		matrix<shz::math::f32, 4, 4>& operator *= (const shz::math::f32 value){ matrix<shz::math::f32, 4, 4> left(*this); matrix<shz::math::f32, 4, 4>::mul(&left.data[0], value, &this->data[0]); return *this; }
		vector<shz::math::f32, 4> operator * (const vector<shz::math::f32, 4>& other){ vector<shz::math::f32, 4> ret;  matrix<shz::math::f32, 4, 4>::mul_vec(&this->data[0], &other.data[0], &ret.data[0]); return ret; }


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

		union{
			struct{ __m128 column1, column2, column3, column4; };
			std::array<shz::math::f32, size> data;
		};
	};

	typedef shz::math::matrix<shz::math::f32, 4, 4> matrix4f;
	typedef shz::math::matrix<shz::math::f64, 4, 4> matrix4d;
} }

#endif // __SHZ_MATH_MATRIX__
