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
	const f32 EPSILON_F32 = 0.000001f;
	const f64 EPSILON_F64 = 0.00000001;



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
} }

#endif // __SHZ_MATH__

