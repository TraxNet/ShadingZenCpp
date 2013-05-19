#include <boost/test/unit_test.hpp>
#include <shz/math/intersection.hpp>

using namespace shz::math;

BOOST_AUTO_TEST_CASE(ray_planeIntersection)
{
	vector<double, 3> o;
	o.data[0] = 0;
	o.data[1] = 1;
	o.data[2] = 0;
	vector<double, 3> d;
	d.data[0] = 0;
	d.data[1] = 0;
	d.data[2] = 1;
	ray<double> test_ray(o, d);
	plane<double> test_plane(0, 1, 0, 0);

	shz::math::intersector<ray<double>, plane<double>> check;
	BOOST_CHECK(!check(test_ray, test_plane));
	BOOST_CHECK(check.state == IntersectState::OUTSIDE);

	test_ray.origin.data[0] = 0;
	test_ray.origin.data[1] = 0;
	test_ray.origin.data[2] = 0;
	test_ray.direction.data[0] = 0;
	test_ray.direction.data[1] = 0;
	test_ray.direction.data[2] = 1;
	BOOST_CHECK(check(test_ray, test_plane));
	BOOST_CHECK(check.state == IntersectState::INSIDE); // Parallel, degenerated solution

	test_ray.origin.data[0] = 0;
	test_ray.origin.data[1] = 1;
	test_ray.origin.data[2] = 0;
	test_ray.direction.data[0] = 0;
	test_ray.direction.data[1] = -1;
	test_ray.direction.data[2] = 0;
	BOOST_CHECK(check(test_ray, test_plane));
	BOOST_CHECK(check.state == IntersectState::PARTIAL_INSIDE);
	BOOST_CHECK_CLOSE(check.length, 1.0, 0.00001);
}

BOOST_AUTO_TEST_CASE(ray_bboxIntersection)
{
	vector<double, 3> o, d;
	o.data[0] = 0;
	o.data[1] = 2;
	o.data[2] = 0;
	d.data[0] = 0;
	d.data[1] = 1;
	d.data[2] = 0;
	ray<double> test_ray(o, d);
	bbox<double> test_bbox(-1, -1, -1, 1, 1, 1);

	shz::math::intersector<ray<double>, bbox<double>> check;
	BOOST_CHECK(!check(test_ray, test_bbox));
	BOOST_CHECK(check.state == IntersectState::OUTSIDE);

	o.data[0] = 0;
	o.data[1] = -2;
	o.data[2] = 0;
	test_ray.origin = o;
	test_ray.direction = d;
	BOOST_CHECK(check(test_ray, test_bbox));
	BOOST_CHECK(check.state == IntersectState::PARTIAL_INSIDE);
	BOOST_CHECK_CLOSE(check.length, 1, 0.0001);

	o.data[0] = 0;
	o.data[1] = 0;
	o.data[2] = 0;
	test_ray.origin = o;
	BOOST_CHECK(check(test_ray, test_bbox));
	BOOST_CHECK(check.state == IntersectState::INSIDE);
}

BOOST_AUTO_TEST_CASE(ray_sphereIntersection)
{
	ray<double> test_ray;
	sphere<double> test_sphere;
	test_ray.origin.data[0] = 0;
	test_ray.origin.data[1] = 0;
	test_ray.origin.data[2] = 0;
	test_ray.direction.data[0] = 0;
	test_ray.direction.data[1] = 1;
	test_ray.direction.data[2] = 0;
	test_ray.length = 10;
	test_sphere.center.data[0] = 0;
	test_sphere.center.data[1] = 0;
	test_sphere.center.data[2] = 0;
	test_sphere.radius = 1;

	shz::math::intersector<ray<double>, sphere<double>> check;
	BOOST_CHECK(check(test_ray, test_sphere));
	BOOST_CHECK(check.state == IntersectState::INSIDE);

	test_sphere.center.data[0] = 0;
	test_sphere.center.data[1] = 5;
	test_sphere.center.data[2] = 0;
	test_sphere.radius = 1;
	BOOST_CHECK(check(test_ray, test_sphere));

	shz::math::intersector<ray<double>, sphere<double>, shz::math::partial_resolve_intersector> partial_check;
	test_sphere.center.data[0] = 0;
	test_sphere.center.data[1] = 5;
	test_sphere.center.data[2] = 0;
	test_sphere.radius = 1;
	BOOST_CHECK(partial_check(test_ray, test_sphere));
}