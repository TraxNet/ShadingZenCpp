#ifndef __SHZ_MATH_VECTOR__
#define __SHZ_MATH_VECTOR__

//#include <initializer_list>
#include <array>
#include <memory>
#include <shz/math/math.hpp>


namespace shz{ namespace math{
		template <typename T, int C> struct vector
		{
			static const size_t size = C;

			typedef T underlaying_type;

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

			vector<T,C> operator - (const vector<T,C>& other) const {  vector<T,C> t; vector<T,C>::sub(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<T,C> operator - (const T value) const {  vector<T,C> t; vector<T,C>::sub(&data[0], value, &t.data[0]); return t; }
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

		template <>  struct _ALIGNED(16) vector<float, 3>
		{
			static const size_t size = 3;

			vector(){}
			explicit vector(const float value){ 
				for(size_t i=0; i<size; i++)
					data[i] = value;
			}

			vector<float,3> operator + (const vector<float,3>& other) const {  vector<float,3> t; vector<float,3>::add(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<float,3> operator + (const float value) const {  vector<float,3> t; vector<float,3>::add(&data[0], value, &t.data[0]); return t; }
			vector<float,3>& operator += (const vector<float,3>& other) { vector<float,3>::add(&data[0], &other.data[0], &data[0]); return *this; }
			vector<float,3>& operator += (const float value) { vector<float,3>::add(&data[0], value, &data[0]); return *this; }

			vector<float,3> operator - (const vector<float,3>& other) const {  vector<float,3> t; vector<float,3>::sub(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<float,3> operator - (const float value) const {  vector<float,3> t; vector<float,3>::sub(&data[0], value, &t.data[0]); return t; }
			vector<float,3>& operator -= (const vector<float,3>& other) { vector<float,3>::sub(&data[0], &other.data[0], &data[0]); return *this; }
			vector<float,3>& operator -= (const float value) { vector<float,3>::sub(&data[0], value, &data[0]); return *this; }

			vector<float,3> operator * (const vector<float,3>& other) const {  vector<float,3> t; vector<float,3>::mul(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<float,3> operator * (const float value) const {  vector<float,3> t; vector<float,3>::mul(&data[0], value, &t.data[0]); return t; }
			vector<float,3>& operator *= (const vector<float,3>& other) { vector<float,3>::mul(&data[0], &other.data[0], &data[0]); return *this; }
			vector<float,3>& operator *= (const float value) { vector<float,3>::mul(&data[0], value, &data[0]); return *this; }

			vector<float,3> operator / (const vector<float,3>& other) const {  vector<float,3> t; vector<float,3>::div(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<float,3> operator / (const float value) const {  vector<float,3> t; vector<float,3>::div(&data[0], value, &t.data[0]); return t; }
			vector<float,3>& operator /= (const vector<float,3>& other) { vector<float,3>::div(&data[0], &other.data[0], &data[0]); return *this; }
			vector<float,3>& operator /= (const float value) { vector<float,3>::div(&data[0], value, &data[0]); return *this; }

			inline void* operator new[](size_t x) { return _ALIGNED_ALLOC(x, 16); }
			inline void operator delete[](void* x) { if (x) _ALIGNED_DEALLOC(x); }

			inline void copy(const vector<float,3>& other){
				std::copy(other.data.cbegin(), other.data.cend(), data.begin());
			}
			inline float dot(const vector<float,3>& other) const { 
				return vector<float,3>::dot(&data[0], &other.data[0]);
			}
			inline float length() const { 
				return dot(*this);
			}
			inline float sqrtlength() const {
				return vector<float,3>::sqrtlength(&data[0]);
			}
			vector<float,3> normalize() const {
				vector<float,3> t;
				vector<float,3>::normalize(&data[0], &t.data[0]);
				return t;
			}
			void normalize_inplace(){
				vector<float,3>::normalize(&data[0], &data[0]);
			}

			static void add(const float* left, const float* right, float* target);
			static void add(const float* left, const float value, float* target);
			static void sub(const float* left, const float* right, float* target);
			static void sub(const float* left, const float value, float* target);
			static void mul(const float* left, const float* right, float* target);
			static void mul(const float* left, const float value, float* target);
			static void div(const float* left, const float* right, float* target);
			static void div(const float* left, const float value, float* target);
			static float dot(const float* left, const float* right);
			static float sqrtlength(const float* source);
			static void normalize(const float* source, float* target);

			

			union{
				struct{ float x, y, z; };
				std::array<float, 4> data;	
			};
		};

		template <>  struct _ALIGNED(16) vector<float, 4>
		{
			static const size_t size = 4;

			vector(){}
			explicit vector(const float value){ 
				for(size_t i=0; i<size; i++)
					data[i] = value;
			}

			vector<float,4> operator + (const vector<float,4>& other) const {  vector<float,4> t; vector<float,4>::add(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<float,4> operator + (const float value) const {  vector<float,4> t; vector<float,4>::add(&data[0], value, &t.data[0]); return t; }
			vector<float,4>& operator += (const vector<float,4>& other) { vector<float,4>::add(&data[0], &other.data[0], &data[0]); return *this; }
			vector<float,4>& operator += (const float value) { vector<float,4>::add(&data[0], value, &data[0]); return *this; }

			vector<float,4> operator - (const vector<float,4>& other) const {  vector<float,4> t; vector<float,4>::sub(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<float,4> operator - (const float value) const {  vector<float,4> t; vector<float,4>::sub(&data[0], value, &t.data[0]); return t; }
			vector<float,4>& operator -= (const vector<float,4>& other) { vector<float,4>::sub(&data[0], &other.data[0], &data[0]); return *this; }
			vector<float,4>& operator -= (const float value) { vector<float,4>::sub(&data[0], value, &data[0]); return *this; }

			vector<float,4> operator * (const vector<float,4>& other) const {  vector<float,4> t; vector<float,4>::mul(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<float,4> operator * (const float value) const {  vector<float,4> t; vector<float,4>::mul(&data[0], value, &t.data[0]); return t; }
			vector<float,4>& operator *= (const vector<float,4>& other) { vector<float,4>::mul(&data[0], &other.data[0], &data[0]); return *this; }
			vector<float,4>& operator *= (const float value) { vector<float,4>::mul(&data[0], value, &data[0]); return *this; }

			vector<float,4> operator / (const vector<float,4>& other) const {  vector<float,4> t; vector<float,4>::div(&data[0], &other.data[0], &t.data[0]); return t; }
			vector<float,4> operator / (const float value) const {  vector<float,4> t; vector<float,4>::div(&data[0], value, &t.data[0]); return t; }
			vector<float,4>& operator /= (const vector<float,4>& other) { vector<float,4>::div(&data[0], &other.data[0], &data[0]); return *this; }
			vector<float,4>& operator /= (const float value) { vector<float,4>::div(&data[0], value, &data[0]); return *this; }

			inline void* operator new[](size_t x) { return _ALIGNED_ALLOC(x, 16); }
			inline void operator delete[](void* x) { if (x) _ALIGNED_DEALLOC(x); }

			inline void copy(const vector<float,4>& other){
				std::copy(other.data.cbegin(), other.data.cend(), data.begin());
			}
			inline float dot(const vector<float,4>& other) const { 
				return vector<float,4>::dot(&data[0], &other.data[0]);
			}
			inline float length() const { 
				return dot(*this);
			}
			inline float sqrtlength() const {
				return vector<float,4>::sqrtlength(&data[0]);
			}
			vector<float,4> normalize() const {
				vector<float,4> t;
				vector<float,4>::normalize(&data[0], &t.data[0]);
				return t;
			}
			void normalize_inplace(){
				vector<float,4>::normalize(&data[0], &data[0]);
			}

			static void add(const float* left, const float* right, float* target);
			static void add(const float* left, const float value, float* target);
			static void sub(const float* left, const float* right, float* target);
			static void sub(const float* left, const float value, float* target);
			static void mul(const float* left, const float* right, float* target);
			static void mul(const float* left, const float value, float* target);
			static void div(const float* left, const float* right, float* target);
			static void div(const float* left, const float value, float* target);
			static float dot(const float* left, const float* right);
			static float sqrtlength(const float* source);
			static void normalize(const float* source, float* target);
			
			union{
				struct{ float x, y, z, w; };
				std::array<float, 4> data;	
			};
		};

		typedef shz::math::vector<shz::math::f32, 3> vector3f;
		typedef shz::math::vector<shz::math::f32, 4> vector4f;
} }

#endif // __SHZ_MATH_VECTOR__
