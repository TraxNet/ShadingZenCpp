#ifndef __SHZ_MATH_VECTOR2__
#define __SHZ_MATH_VECTOR2__

//#include <initializer_list>
#include "Math.h"


namespace Shz{
	namespace Math{
		template <typename T> struct Vector2
		{
			Vector2(){ x = T(); y = T(); }
			Vector2(T x, T y){ this->x = x; this->y = y; }
			Vector2(const Vector2<T>& other){ x = other.x; y = other.y; }
			/*Vector2(std::initializer_list<T> list){ 
				assert(list.size() >= 2);
				x = list[0];
				y = list[1];
			}*/
			explicit Vector2(const T value){ x = y = value; }

			Vector2<T>& operator = (const Vector2<T>& other) { x = other.x; y = other.y; return *this; }

			Vector2<T> operator + (const Vector2<T>& other) const { return Vector2<T>(x + other.x, y + other.y); }
			Vector2<T> operator + (const T value) const { return Vector2<T>(x + value, y + value); }
			Vector2<T>& operator += (const Vector2<T>& other) { x += other.x; y += other.y; return *this; }
			Vector2<T>& operator += (const T value) { x += value; y += value; return *this; }

			Vector2<T> operator - (const Vector2<T>& other) const { return Vector2<T>(x - other.x, y - other.y); }
			Vector2<T> operator - (const T value) const { return Vector2<T>(x - value, y- value); }
			Vector2<T>& operator -= (const Vector2<T>& other) { x -= other.x; y -= other.y; return *this; }
			Vector2<T>& operator -= (const T value) { x -= value; y -= value; return *this; }

			Vector2<T> operator * (const Vector2<T>& other) const { return Vector2<T>(x*other.x, y*other.y); }
			Vector2<T> operator * (const T value) const { return Vector2<T>(x*value, y*value); }
			Vector2<T>& operator *= (const Vector2<T>& other) { x*=other.x; y*=other.y; return *this; }
			Vector2<T>& operator *= (const T value) { x*=value; y*=value; return *this; }

			Vector2<T> operator / (const Vector2<T>& other) const { return Vector2<T>(x/other.x, y/other.y); }
			Vector2<T> operator / (const T value) const { return Vector2<T>(x/value, y/value); }
			Vector2<T>& operator /= (const Vector2<T>& other) { x/=other.x; y/=other.y; return *this; }
			Vector2<T>& operator /= (const T value) { x/=value; y/=value; return *this; }

			T dot(const Vector2<T>& other) { return x*other.x + y*other.y; }
			T length(){ return x*x + y*y; }
			Vector2<T> normalize(){
				T len = length();
				if(equals(len, 0)){
					return Vector2<T>(0, 0);
				}

				return Vector2<T>(x/len, y/len);
			}
			void normalizeInplace(){
				T len = length();
				if(!equals(len, 0)){
					x /= len;
					y /= len;
				}
			}


			T x, y;
		};

		typedef Vector2<f32> Vector2f;
		typedef Vector2<f64> Vector2d;
	}
}

#endif // __SHZ_MATH_VECTOR2__
