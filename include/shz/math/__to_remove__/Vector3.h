#ifndef __SHZ_MATH_VECTOR3__
#define __SHZ_MATH_VECTOR3__

#include "Math.h"

namespace Shz{
	namespace Math{
		template <typename T> struct Vector3
		{
			Vector3(){ x = T(); y = T(); z = T(); }
			Vector3(T x, T y, T z){ this->x = x; this->y = y; this->z = z; }
			Vector3(const Vector3<T>& other){ x = other.x; y = other.y; z = other.z; }
			explicit Vector3(const T value){ x = y = z = value; }

			Vector3<T>& operator=(const Vector3<T>& other) { x = other.x; y = other.y; z = other.z; return *this; }

			Vector3<T> operator + (const Vector3<T>& other) const { return Vector3<T>(x + other.x, y + other.y, z + other.z); }
			Vector3<T> operator + (const T value) const { return Vector3<T>(x + value, y + value, z + value); }
			Vector3<T>& operator += (const Vector3<T>& other) { x += other.x; y += other.y; z += other.z; return *this; }
			Vector3<T>& operator += (const T value) { x += value; y += value; z += value; return *this; }

			Vector3<T> operator - (const Vector3<T>& other) const { return Vector3<T>(x - other.x, y - other.y, z - other.z); }
			Vector3<T> operator - (const T value) const { return Vector3<T>(x - value, y- value, z - value); }
			Vector3<T>& operator -= (const Vector3<T>& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
			Vector3<T>& operator -= (const T value) { x -= value; y -= value; z -= value; return *this; }

			Vector3<T> operator * (const Vector3<T>& other) const { return Vector3<T>(x*other.x, y*other.y, z*other.z); }
			Vector3<T> operator * (const T value) const { return Vector3<T>(x*value, y*value, z*value); }
			Vector3<T>& operator *= (const Vector3<T>& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
			Vector3<T>& operator *= (const T value) { x *= value; y *= value; z *= value; return *this; }

			Vector3<T> operator / (const Vector3<T>& other) const { return Vector3<T>(x/other.x, y/other.y, z/other.z); }
			Vector3<T> operator / (const T value) const { return Vector3<T>(x/value, y/value, z/value); }
			Vector3<T>& operator /= (const Vector3<T>& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
			Vector3<T>& operator /= (const T value) { x /= value; y /= value; z /= value; return *this; }

			T dot(const Vector3<T>& other) { return x*other.x + y*other.y + z*other.z; }
			T length(){ return x*x + y*y + z*z; }
			T sqrLength(){ return sqrt(x*x + y*y + z*z); }
			Vector3<T> normalize(){
				T len = sqrLength();
				if(equals(len, 0)){
					return Vector3<T>(0, 0, 0);
				}

				return Vector3<T>(x/len, y/len, z/len);
			}
			void normalizeInplace(){
				T len = sqrLength();
				if(!equals(len, 0)){
					x /= len;
					y /= len;
					z /= len;
				}
			}


			T x, y, z;
		};
	}
}

#endif // __SHZ_MATH_VECTOR3__

