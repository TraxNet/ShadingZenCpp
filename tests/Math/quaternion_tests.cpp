#include <boost/test/unit_test.hpp>
#include <shz/math/quaternion.hpp>

#define ROUND_ERROR 0.00001

BOOST_AUTO_TEST_CASE(quaternionConstructors)
{
	shz::math::quaternion<shz::math::f64> q1;
	q1.x = 1.0;
	q1.y = 0.0;
	q1.z = 0.0;
	q1.w = 1.0;
	BOOST_CHECK_EQUAL(q1.data[0], q1.x);
	BOOST_CHECK_EQUAL(q1.data[1], q1.y);
	BOOST_CHECK_EQUAL(q1.data[2], q1.z);
	BOOST_CHECK_EQUAL(q1.data[3], q1.w);

	shz::math::quaternion<shz::math::f64> q2(q1);
	BOOST_CHECK_EQUAL(q1.data[0], q2.x);
	BOOST_CHECK_EQUAL(q1.data[1], q2.y);
	BOOST_CHECK_EQUAL(q1.data[2], q2.z);
	BOOST_CHECK_EQUAL(q1.data[3], q2.w);

	shz::math::vector<shz::math::f64, 3> v;
	v.data[0] = 0.0;
	v.data[1] = 1.0;
	v.data[2] = 0.0;
	q2 = shz::math::quaternion<shz::math::f64>(v, shz::math::HALF_PI);
	BOOST_CHECK_CLOSE(0.0, q2.x, ROUND_ERROR);
	BOOST_CHECK_CLOSE(0.70710679664085752, q2.y, ROUND_ERROR);
	BOOST_CHECK_CLOSE(0.0, q2.z, ROUND_ERROR);
	BOOST_CHECK_CLOSE(0.70710679664085752, q2.w, ROUND_ERROR);

	q2 = shz::math::quaternion<shz::math::f64>(0.0, 1.0, 0.0, shz::math::HALF_PI);
	BOOST_CHECK_CLOSE(0.0, q2.x, ROUND_ERROR);
	BOOST_CHECK_CLOSE(0.70710679664085752, q2.y, ROUND_ERROR);
	BOOST_CHECK_CLOSE(0.0, q2.z, ROUND_ERROR);
	BOOST_CHECK_CLOSE(0.70710679664085752, q2.w, ROUND_ERROR);
}

BOOST_AUTO_TEST_CASE(quaternionToMatrix)
{
	shz::math::quaternion<shz::math::f64> q1(0.0, 1.0, 0.0, shz::math::HALF_PI);
	shz::math::matrix<shz::math::f64, 4, 4> matrix;

	q1.to_matrix(matrix);
	
	shz::math::matrix<shz::math::f32, 4, 4> m = shz::math::matrix<shz::math::f32, 4, 4>::from_rotation(0.f, 1.f, 0.f, shz::math::HALF_PI);

	BOOST_CHECK_CLOSE(matrix[0], m[0], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[1], m[1], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[2], m[2], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[3], m[3], ROUND_ERROR);
	
	BOOST_CHECK_CLOSE(matrix[4], m[4], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[5], m[5], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[6], m[6], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[7], m[7], ROUND_ERROR);
	
	BOOST_CHECK_CLOSE(matrix[8], m[8], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[9], m[9], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[10], m[10], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[11], m[11], ROUND_ERROR);
	
	BOOST_CHECK_CLOSE(matrix[12], m[12], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[13], m[13], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[14], m[14], ROUND_ERROR);
	BOOST_CHECK_CLOSE(matrix[15], m[15], ROUND_ERROR);
	
}


BOOST_AUTO_TEST_CASE(quaternionMuls)
{
	shz::math::quaternion<shz::math::f64> q1(0.0, 1.0, 0.0, shz::math::HALF_PI);
	shz::math::quaternion<shz::math::f64> q2(0.0, 1.0, 0.0, shz::math::HALF_PI);
	shz::math::quaternion<shz::math::f64> q3(0.0, 1.0, 0.0, shz::math::PI);

	shz::math::quaternion<shz::math::f64> q12 = q1 * q2;

	BOOST_CHECK_CLOSE(q12.x, q3.x, ROUND_ERROR);
	BOOST_CHECK_CLOSE(q12.y, q3.y, ROUND_ERROR);
	BOOST_CHECK_CLOSE(q12.z, q3.z, ROUND_ERROR);
	BOOST_CHECK_CLOSE(q12.w, q3.w, ROUND_ERROR);

	q12 = q1;
	q12 *= q2;

	BOOST_CHECK_CLOSE(q12.x, q3.x, ROUND_ERROR);
	BOOST_CHECK_CLOSE(q12.y, q3.y, ROUND_ERROR);
	BOOST_CHECK_CLOSE(q12.z, q3.z, ROUND_ERROR);
	BOOST_CHECK_CLOSE(q12.w, q3.w, ROUND_ERROR);
}

BOOST_AUTO_TEST_CASE(quaternionSlerp)
{
	shz::math::quaternion<shz::math::f64> q1(0.0, 1.0, 0.0, 0.0);
	shz::math::quaternion<shz::math::f64> q2(0.0, 1.0, 0.0, shz::math::HALF_PI/2);
	shz::math::quaternion<shz::math::f64> q3(0.0, 1.0, 0.0, shz::math::HALF_PI);

	auto half = shz::math::quaternion<shz::math::f64>::slerp(q1, q3, 0.5);

	BOOST_CHECK_CLOSE(half.x, q2.x, ROUND_ERROR);
	BOOST_CHECK_CLOSE(half.y, q2.y, ROUND_ERROR);
	BOOST_CHECK_CLOSE(half.z, q2.z, ROUND_ERROR);
	BOOST_CHECK_CLOSE(half.w, q2.w, ROUND_ERROR);

	half = shz::math::quaternion<shz::math::f64>::slerp(q1, q1, 0.5);
	BOOST_CHECK_CLOSE(half.x, q1.x, ROUND_ERROR);
	BOOST_CHECK_CLOSE(half.y, q1.y, ROUND_ERROR);
	BOOST_CHECK_CLOSE(half.z, q1.z, ROUND_ERROR);
	BOOST_CHECK_CLOSE(half.w, q1.w, ROUND_ERROR);
}