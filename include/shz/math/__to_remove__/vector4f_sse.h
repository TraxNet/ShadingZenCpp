#ifndef __SHZ_MATH_VECTOR4F__
#define __SHZ_MATH_VECTOR4F__

#include <array>
#include <shz/math/math.hpp>


namespace shz{ namespace math{
		template <> struct vector<float, 4>
		{
			static const size_t size = C;

			vector(){}
			/*Vector(std::initializer_list<T> list){ 
				std::copy(list.begin(), list.end(), data);
			}*/
			explicit vector(const T value){ 
				for(size_t i=0; i<size; i++)
					data[i] = value;
			}

			vector<T,C> operator + (const vector<T,C>& other) const {  vector<T,C> t; vector<T,C>::add(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<T,C> operator + (const T value) const {  vector<T,C> t; vector<T,C>::add(&data[0], value, &t.data[0]); return t; }
			vector<T,C>& operator += (const vector<T,C>& other) { vector<T,C>::add(&data[0], &other.data[0], &data[0]); return *this; }
			vector<T,C>& operator += (const T value) { vector<T,C>::add(&data[0], value, &data[0]); return *this; }

			vector<T,C> operator - (const vector<T,C>& other) const {  vector<T,C> t; vector<T,C>::sub(data, &other.data[0], &t.data[0]); return t; }
			vector<T,C> operator - (const T value) const {  vector<T,C> t; vector<T,C>::sub(data, value, &t.data[0]); return t; }
			vector<T,C>& operator -= (const vector<T,C>& other) { vector<T,C>::sub(&data[0], &other.data[0], &data[0]); return *this; }
			vector<T,C>& operator -= (const T value) { vector<T,C>::sub(&data[0], value, &data[0]); return *this; }

			vector<T,C> operator * (const vector<T,C>& other) const {  vector<T,C> t; vector<T,C>::mul(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<T,C> operator * (const T value) const {  vector<T,C> t; vector<T,C>::mul(&data[0], value, &t.data[0]); return t; }
			vector<T,C>& operator *= (const vector<T,C>& other) { vector<T,C>::mul(&data[0], &other.data[0], &data[0]); return *this; }
			vector<T,C>& operator *= (const T value) { vector<T,C>::mul(&data[0], value, &data[0]); return *this; }

			vector<T,C> operator / (const vector<T,C>& other) const {  vector<T,C> t; vector<T,C>::div(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<T,C> operator / (const T value) const {  vector<T,C> t; vector<T,C>::div(&data[0], value, &t.data[0]); return t; }
			vector<T,C>& operator /= (const vector<T,C>& other) { vector<T,C>::div(&data[0], &other.data[0], &data[0]); return *this; }
			vector<T,C>& operator /= (const T value) { vector<T,C>::div(&data[0], value, &data[0]); return *this; }

			inline void copy(const vector<T,C>& other){
				std::copy(other.data.cbegin(), other.data.cend(), data.begin());
			}
			inline T dot(const vector<T,C>& other) const { 
				return vector<T,C>::dot(&data[0], &other.data[0]);
			}
			inline T length() const { 
				return dot(*this);
			}
			inline T sqrtlength() const {
				return vector<T,C>::sqrtlength(&data[0]);
			}
			vector<T,C> normalize() const {
				vector<T,C> t;
				vector<T,C>::normalize(&data[0], &t.data[0]);
				return t;
			}
			void normalize_inplace(){
				vector<T,C>::normalize(&data[0], &data[0]);
			}

			static inline void add(const T* left, const T* right, T* target){
				for(size_t i=0; i<size; ++i){
					target[i] = left[i] + right[i];
				}
			}
			static inline void add(const T* left, const T value, T* target){
				for(size_t i=0; i<size; ++i){
					target[i] = left[i] + value;
				}
			}
			static inline void sub(const T* left, const T* right, T* target){
				for(size_t i=0; i<size; ++i){
					target[i] = left[i] - right[i];
				}
			}
			static inline void sub(const T* left, const T value, T* target){
				for(size_t i=0; i<size; ++i){
					target[i] = left[i] - value;
				}
			}
			static inline void mul(const T* left, const T* right, T* target){
				for(size_t i=0; i<size; ++i){
					target[i] = left[i] * right[i];
				}
			}
			static inline void mul(const T* left, const T value, T* target){
				for(size_t i=0; i<size; ++i){
					target[i] = left[i] * value;
				}
			}
			static inline void div(const T* left, const T* right, T* target){
				for(size_t i=0; i<size; ++i){
					target[i] = left[i] / right[i];
				}
			}
			static inline void div(const T* left, const T value, T* target){
				for(size_t i=0; i<size; ++i){
					target[i] = left[i] / value;
				}
			}
			static inline T dot(const T* left, const T* right){
				T value = T();
				for(size_t i=0; i<size; ++i)
					value += left[i]*right[i];

				return value;

			}
			static inline T sqrtlength(const T* source){
				return ::sqrt(vector<T,C>::dot(source, source));
			}
			static inline void normalize(const T* source, T* target){
				T len = vector<T,C>::sqrtlength(source);
				if(shz::math::equals(len, 0))
					return;

				vector<T,C>::div(source, len, target);
			}
			

			std::array<T, size> data;			
		};
} }

#endif // __SHZ_MATH_VECTOR4F__
