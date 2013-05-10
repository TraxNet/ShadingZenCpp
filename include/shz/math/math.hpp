#ifndef __SHZ_MATH__
#define __SHZ_MATH__

#include <math.h>
#include <shz/math/types.hpp>

/*
	TODO: There is a hidden problem with all this classes if mixed with C++ STL containers. The default std::allocator
	does not have the memory alignment constraint we need, so any object that has a shz::math::vector, shz::math:matrix 
	and so on within it and is used in STL container, the standard allocator will corrupt the memory as we would operate 
	with non-aligned memory. The workaround is to create a new std::allocator or specialized std::allocator for our all 
	the types involved.

	For more information check this:
		- http://stackoverflow.com/questions/12502071/sse-intrinsics-and-alignment
		- http://msdn.microsoft.com/en-us/library/aa290049.aspx
		- http://www.codeproject.com/Articles/4795/C-Standard-Allocator-An-Introduction-and-Implement
		- http://en.cppreference.com/w/cpp/memory/allocator
		- http://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4079/Allocators-STL.htm
*/

#define ROUND_DOWN(x, s) ((x) & ~((s)-1))

namespace shz{ namespace math{	

	// MATH CONSTANTS
	const f32 EPSILON_F32 = 0.000001f;
	const f64 EPSILON_F64 = 0.00000001;
	const f32 PI = 3.141592653589f;
	const f32 HALF_PI = 1.5707963267946f;


	inline bool equals(const f32 a, const f32 b, const f32 epsilon=EPSILON_F32){
		return ((a - b) <= epsilon) && ((a + b) >= epsilon);
	}

	inline bool equals(const f64 a, const f64 b, const f64 epsilon=EPSILON_F64){
		return ((a - b) <= epsilon) && ((a + b) >= epsilon);
	}

	inline bool isZero(const f32 a, const f32 epsilon = EPSILON_F32)
	{
		return fabsf(a) <= epsilon;
	}

	inline bool isZero(const f64 a, const f64 epsilon = EPSILON_F64)
	{
		return fabs(a) <= epsilon;
	}	

	inline f32 toDegrees(f32 radians){
		return radians*180/PI;
	}

	inline f32 toRadians(f32 degrees){
		return degrees*PI/180;
	}

	/** TODO: Check concepts for MathType parameter and ensure if contains the required functionality */
	template<class MathType, size_t ArraySize> static void add_array(const typename MathType::underlaying_type* left, const typename MathType::underlaying_type* right, typename MathType::underlaying_type* target){	
		BOOST_STATIC_ASSERT(ArraySize%MathType::size == 0); /** Check ARRAY_SIZE is multiple of VectorType::size */

		for(size_t i=0; i < ROUND_DOWN(ArraySize, MathType::size); i+= MathType::size){
			MathType::add(left, right, target);
			left += MathType::size;
			right += MathType::size;
			target += MathType::size;
		}
	}

	/** Static (compiler time) helper templates */

	template <u64 Value1, u64 Value2>
	struct static_unsigned_min
	{
		static const u64 value = (Value1 > Value2) ? Value2 : Value1;			
	};

	template <u64 Value1, u64 Value2>
	struct static_unsigned_max
	{
		static const u64 value = (Value1 < Value2) ? Value2 : Value1;
	};
} }

#endif // __SHZ_MATH__

