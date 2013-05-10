#include <smmintrin.h>
#include <shz/math/vector.hpp>



void shz::math::vector<float,4>::add(const float* left, const float* right, float* target){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load_ps(right);
	__m128 r = _mm_add_ps(a, b);
	_mm_store_ps(target, r);
}

void shz::math::vector<float,4>::add(const float* left, const float value, float* target){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load1_ps(&value);
	__m128 r = _mm_add_ps(a, b);
	_mm_store_ps(target, r);
}

void shz::math::vector<float,4>::sub(const float* left, const float* right, float* target){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load_ps(right);
	__m128 r = _mm_sub_ps(a, b);
	_mm_store_ps(target, r);
}

void shz::math::vector<float,4>::sub(const float* left, const float value, float* target){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load1_ps(&value);
	__m128 r = _mm_sub_ps(a, b);
	_mm_store_ps(target, r);
}

void shz::math::vector<float,4>::mul(const float* left, const float* right, float* target){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load_ps(right);
	__m128 r = _mm_mul_ps(a, b);
	_mm_store_ps(target, r);
}

void shz::math::vector<float,4>::mul(const float* left, const float value, float* target){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load1_ps(&value);
	__m128 r = _mm_mul_ps(a, b);
	_mm_store_ps(target, r);
}

void shz::math::vector<float,4>::div(const float* left, const float* right, float* target){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load_ps(right);
	__m128 r = _mm_div_ps(a, b);
	_mm_store_ps(target, r);
}

void shz::math::vector<float,4>::div(const float* left, const float value, float* target){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load1_ps(&value);
	__m128 r = _mm_div_ps(a, b);
	_mm_store_ps(target, r);
}

float shz::math::vector<float,4>::dot(const float* left, const float* right){
	__m128 a = _mm_load_ps(left);
	__m128 b = _mm_load_ps(right);
	__m128 r = _mm_dp_ps(a, b, 0xF1); // Dot product all 4 lanes with mask 1111 0001 ([op4:7][write0:3]

	float _ALIGNED(16) ret[4];
	_mm_store_ps(ret, r);

	return ret[0];
}

float shz::math::vector<float,4>::length(const float* source){
	const __m128 a = _mm_load_ps(source);
	const __m128 d = _mm_dp_ps(a, a, 0xFF); // Dot product with mask 1111 1111 ([op4:7][write0:3]
	const __m128 r = _mm_sqrt_ps(d);

	float _ALIGNED(16) ret[4];
	_mm_store_ps(ret, r);

	return ret[0];
}

float shz::math::vector<float,4>::inv_length(const float* source){
	const __m128 a = _mm_load_ps(source);
	const __m128 d = _mm_dp_ps(a, a, 0xFF); // Dot product with mask 1111 1111 ([op4:7][write0:3]
	__m128 r = _mm_rsqrt_ps(d);
	const __m128 mask = _mm_cmpgt_ps(d, _mm_set1_ps(shz::math::EPSILON_F32));
	r = _mm_and_ps(mask, r);

	float _ALIGNED(16) ret[4];
	_mm_store_ps(ret, r);

	return ret[0];
}

void shz::math::vector<float,4>::normalize(const float* source, float* target){
	const __m128 a = _mm_load_ps(source);
	const __m128 d = _mm_dp_ps(a, a, 0xFF); // Dot product with mask 1111 1111 ([op4:7][write0:3]
	__m128 sqr = _mm_rsqrt_ps(d);
	const __m128 mask = _mm_cmpgt_ps(d, _mm_set1_ps(shz::math::EPSILON_F32));
	sqr = _mm_and_ps(mask, sqr);
	const __m128 r = _mm_mul_ps(a, sqr);
	_mm_store_ps(target, r);
}
