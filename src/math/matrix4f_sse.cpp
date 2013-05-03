#include <smmintrin.h>
#include <shz/math/matrix.hpp>

void shz::math::matrix<shz::math::f32, 4, 4>::add(const shz::math::f32* left, const shz::math::f32* right, shz::math::f32* target){
	for(size_t i=0; i < 4; ++i){
		__m128 a = _mm_load_ps(left);
		__m128 b = _mm_load_ps(right);
		__m128 r = _mm_add_ps(a, b);
		_mm_store_ps(target, r);
		left+=4; right+=4; target+=4;
	}
}

void shz::math::matrix<shz::math::f32, 4, 4>::add(const shz::math::f32* left, const shz::math::f32 value, shz::math::f32* target){
	__m128 b = _mm_load1_ps(&value);
	for(size_t i=0; i < 4; ++i){
		__m128 a = _mm_load_ps(left);
		__m128 r = _mm_add_ps(a, b);
		_mm_store_ps(target, r);
		left+=4; target+=4;
	}
}

void shz::math::matrix<shz::math::f32, 4, 4>::sub(const shz::math::f32* left, const shz::math::f32* right, shz::math::f32* target){
	for(size_t i=0; i < 4; ++i){
		__m128 a = _mm_load_ps(left);
		__m128 b = _mm_load_ps(right);
		__m128 r = _mm_sub_ps(a, b);
		_mm_store_ps(target, r);
		left+=4; right+=4; target+=4;
	}
}

void shz::math::matrix<shz::math::f32, 4, 4>::sub(const shz::math::f32* left, const shz::math::f32 value, shz::math::f32* target){
	__m128 b = _mm_load1_ps(&value);
	for(size_t i=0; i < 4; ++i){
		__m128 a = _mm_load_ps(left);
		__m128 r = _mm_sub_ps(a, b);
		_mm_store_ps(target, r);
		left+=4; target+=4;
	}
}

void shz::math::matrix<shz::math::f32, 4, 4>::mul(const shz::math::f32* left, const shz::math::f32*right, shz::math::f32* target) {
	shz::math::f32 left_transposed[shz::math::matrix<shz::math::f32, 4, 4>::size];
	matrix<shz::math::f32, 4, 4>::transpose(left, left_transposed);

	for(size_t m=0; m<4; ++m){
		__m128 right_operand = _mm_load_ps(right);
		shz::math::f32* transposed = left_transposed;

		for(size_t n=0; n<4; ++n){
			__m128 left_operand = _mm_load_ps(transposed);
			
			*target = shz::math::f32();

			for(size_t i=0; i<4; ++i){
				shz::math::f32 a = *(transposed + i);
				shz::math::f32 b = *(right + i);
				*target += a*b;
			}

			target++;
			transposed += 4;
		}

		right += 4;
	}
}

void shz::math::matrix<shz::math::f32, 4, 4>::mul(const shz::math::f32* left, const shz::math::f32 value, shz::math::f32 *target){
	__m128 b = _mm_load1_ps(&value);
	for(size_t i=0; i < 4; ++i){
		__m128 a = _mm_load_ps(left);
		__m128 r = _mm_mul_ps(a, b);
		_mm_store_ps(target, r);
		left+=4; target+=4;
	}
}

void shz::math::matrix<shz::math::f32, 4, 4>::mul_vec(const shz::math::f32* left, const shz::math::f32* right, shz::math::f32* target) {
	for(size_t m=0; m<4; ++m){
		*target = shz::math::f32();
		for(size_t n=0; n<4; ++n){
			*target += left[m*4 + n]*right[n];
		}
		target++;
	}
}

void shz::math::matrix<shz::math::f32, 4, 4>::transpose(const shz::math::f32* left, shz::math::f32* target){
	for(size_t n=0; n<4; ++n){
		for(size_t m=0; m<4; ++m){
			target[n*4 + m] = left[m*4 + n];
		}
	}
}