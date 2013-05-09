#include <boost/test/unit_test.hpp>
#include <shz/math/plane.hpp>


BOOST_AUTO_TEST_CASE(planeConstructors)
{
	shz::math::plane<shz::math::f64> p1;
	shz::math::plane<shz::math::f64> p2(0.0, 1.0, 0.0, 0.0);

	BOOST_CHECK(p2.a == 0.0);
	BOOST_CHECK(p2.b == 1.0);
	BOOST_CHECK(p2.c == 0.0);
	BOOST_CHECK(p2.d == 0.0);

	BOOST_CHECK(p2.eq[0] == 0.0);
	BOOST_CHECK(p2.eq[1] == 1.0);
	BOOST_CHECK(p2.eq[2] == 0.0);
	BOOST_CHECK(p2.eq[3] == 0.0);
}

BOOST_AUTO_TEST_CASE(isPointBehindConstructors)
{
	shz::math::plane<shz::math::f64> p2(0.0, 1.0, 0.0, 0.0);

	BOOST_CHECK(p2.is_point_behind(0.0, -1.0, 0.0));
	BOOST_CHECK(!p2.is_point_behind(0.0, 1.0, 0.0));
	BOOST_CHECK(p2.is_point_behind(0.0, 0.0, 0.0));
}


BOOST_AUTO_TEST_CASE(isSphereBehindConstructors)
{
	shz::math::plane<shz::math::f64> p2(0.0, 1.0, 0.0, 0.0);

	BOOST_CHECK(p2.is_sphere_behind(0.0, -1.0, 0.0, 0.9));
	BOOST_CHECK(!p2.is_sphere_behind(0.0, 1.0, 0.0, 1.0));
	BOOST_CHECK(!p2.is_sphere_behind(0.0, 0.0, 0.0, 0.1));
	BOOST_CHECK(p2.is_sphere_behind(0.0, -2.0, 0.0, 1.0));
}


