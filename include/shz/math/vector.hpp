#ifndef __SHZ_MATH_VECTOR__
#define __SHZ_MATH_VECTOR__

//#include <initializer_list>
#include <array>
#include <memory>
#include <iostream>
#include <shz/math/math.hpp>
#include <cstdarg>


namespace shz{ namespace math{
		template <typename T, int C> struct vector
		{
			typedef T underlaying_type;
			typedef T* underlaying_type_pointer;
			typedef const T* underlaying_type_const_pointer;
			typedef T& underlaying_type_reference;
			typedef const T& underlaying_type_const_reference;
			
			static const size_t size = C;

			vector(){}
			/*Vector(std::initializer_list<T> list){ 
				std::copy(list.begin(), list.end(), data);
			}*/
			explicit vector(const T value){ 
				for(size_t i=0; i<size; i++)
					data[i] = value;
			}
			vector(f32 x, f32 y, f32 z, f32 w){ data[0] = x; data[1] = y; data[2] = z; data[3] = w; }

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

			underlaying_type_reference operator [] (size_t pos){ return data[pos]; }
			underlaying_type_const_reference operator [] (size_t pos) const { return data[pos]; }
            
            friend std::ostream& operator << (std::ostream& os, const vector<T,C>& vec){
                os << "[";
                for(size_t i=0; i < size; ++i){
                    os << vec.data[i];
                    if(i==size-1)
                        os << "]";
                    else
                        os << ",";
                }
                
                return os;
            }

			inline void set(int num, ...){
				va_list arguments;    
				va_start (arguments, num);  

				for (int x = 0; x < num && x < size; ++x)
					data[x] = va_arg(arguments, T);

				va_end(arguments);
			}
			inline void copy(const vector<T,C>& other){
				std::copy(other.data.cbegin(), other.data.cend(), data.begin());
			}
			inline T dot(const vector<T,C>& other) const { 
				return vector<T,C>::dot(&data[0], &other.data[0]);
			}
			inline T length() const { 
				return vector<T,C>::length(&data[0]);
			}
			inline T inv_length() const { 
				return 1.0/length();
			}
			inline T sqrlength() const {
				return dot(*this);
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
			static inline T length(const T* source){
				return ::sqrt(vector<T,C>::dot(source, source));
			}
			static inline T inv_length(const T* source){
				return 1.0/length(source);
			}
			static inline void normalize(const T* source, T* target){
				T len = vector<T,C>::length(source);
				if(shz::math::equals(len, 0))
					return;

				vector<T,C>::div(source, len, target);
			}
			

			std::array<T, size> data;			
		};

		template <>  struct _ALIGNED(16) vector<float, 3>
		{
			typedef float underlaying_type;
			typedef float* underlaying_type_pointer;
			typedef const float* underlaying_type_const_pointer;
			typedef float& underlaying_type_reference;
			typedef const float& underlaying_type_const_reference;
			static const size_t size = 3;

			vector(){}
			explicit vector(const float value){ 
				for(size_t i=0; i<size; i++)
					data[i] = value;
			}
			vector(f32 x, f32 y, f32 z){ data[0] = x; data[1] = y; data[2] = z; }

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

			underlaying_type_reference operator [] (size_t pos){ return data[pos]; }
			underlaying_type_const_reference operator [] (size_t pos) const { return data[pos]; }
            
            friend std::ostream& operator << (std::ostream& os, const vector<float,3>& vec){
                os << "[";
                for(size_t i=0; i < size; ++i){
                    os << vec.data[i];
                    if(i==size-1)
                        os << "]";
                    else
                        os << ",";
                }
                
                return os;
            }

			inline void* operator new[](size_t x) { return _ALIGNED_ALLOC(x, 16); }
			inline void operator delete[](void* x) { if (x) _ALIGNED_DEALLOC(x); }

			inline void copy(const vector<float,3>& other){
				std::copy(other.data.cbegin(), other.data.cend(), data.begin());
			}
			inline float dot(const vector<float,3>& other) const { 
				return vector<float,3>::dot(&data[0], &other.data[0]);
			}
			inline float length() const { 
				return vector<float,3>::length(data.data());
			}
			inline float inv_length() const { 
				return vector<float,3>::inv_length(data.data());
			}
			inline float sqrlength() const {
				return dot(*this);
				
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
			static float length(const float* source);
			static float inv_length(const float* source);
			static void normalize(const float* source, float* target);	

			union{
				struct{ float x, y, z; };
				std::array<float, 4> data;	
			};
		};

		template <>  struct _ALIGNED(16) vector<float, 4>
		{
			typedef float underlaying_type;
			typedef float* underlaying_type_pointer;
			typedef const float* underlaying_type_const_pointer;
			typedef float& underlaying_type_reference;
			typedef const float& underlaying_type_const_reference;
			static const size_t size = 4;

			vector(){}
			explicit vector(const float value){ 
				for(size_t i=0; i<size; i++)
					data[i] = value;
			}
            vector(f32 x, f32 y, f32 z, f32 w){ data[0] = x; data[1] = y; data[2] = z; data[3] = w; }

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

			underlaying_type_reference operator [] (size_t pos){ return data[pos]; }
			underlaying_type_const_reference operator [] (size_t pos) const { return data[pos]; }
            
            friend std::ostream& operator << (std::ostream& os, const vector<float,4>& vec){
                os << "[";
                for(size_t i=0; i < size; ++i){
                    os << vec.data[i];
                    if(i==size-1)
                        os << "]";
                    else
                        os << ",";
                }
                
                return os;
            }

			inline void* operator new[](size_t x) { return _ALIGNED_ALLOC(x, 16); }
			inline void operator delete[](void* x) { if (x) _ALIGNED_DEALLOC(x); }

			inline void copy(const vector<float,4>& other){
				std::copy(other.data.cbegin(), other.data.cend(), data.begin());
			}
			inline float dot(const vector<float,4>& other) const { 
				return vector<float,4>::dot(&data[0], &other.data[0]);
			}
			inline float length() const { 
				return vector<float,4>::length(data.data());
			}
			inline float inv_length() const { 
				return vector<float,4>::inv_length(data.data());
			}
			inline float sqrlength() const {
				return dot(*this);
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
			static float length(const float* source);
			static float inv_length(const float* source);
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
