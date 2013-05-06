#include <boost/test/unit_test.hpp>
#include <shz/math/quaternion.hpp>

#define ROUND_ERROR 0.00001

BOOST_AUTO_TEST_CASE(quaternionConstructors)
{
	shz::math::quaternion<shz::math::f64> q1 = shz::math::quaternion<shz::math::f64>();
	q1.x = 1.0;
	q1.y = 0.0;
	q1.z = 0.0;
	q1.w = 1.0;
	BOOST_CHECK_EQUAL(q1.data[0], q1.x);
	BOOST_CHECK_EQUAL(q1.data[1], q1.y);
	BOOST_CHECK_EQUAL(q1.data[2], q1.z);
	BOOST_CHECK_EQUAL(q1.data[3], q1.w);

	shz::math::quaternion<shz::math::f64> q2 = shz::math::quaternion<shz::math::f64>(q1);
	BOOST_CHECK_EQUAL(q1.data[0], q2.x);
	BOOST_CHECK_EQUAL(q1.data[1], q2.y);
	BOOST_CHECK_EQUAL(q1.data[2], q2.z);
	BOOST_CHECK_EQUAL(q1.data[3], q2.w);

	shz::math::vector<shz::math::f64, 3> v = shz::math::vector<shz::math::f64, 3>();
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
	shz::math::quaternion<shz::math::f64> q1 = shz::math::quaternion<shz::math::f64>(0.0, 1.0, 0.0, shz::math::HALF_PI);
	shz::math::matrix<shz::math::f64, 4, 4> matrix;

	q1.to_matrix(matrix);
	

}


BOOST_AUTO_TEST_CASE(quaternionMuls)
{

}

BOOST_AUTO_TEST_CASE(quaternionSlerp)
{

}