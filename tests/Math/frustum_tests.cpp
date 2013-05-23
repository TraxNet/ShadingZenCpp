#include <boost/test/unit_test.hpp>
#include <shz/math/frustum.hpp>


BOOST_AUTO_TEST_CASE(frustumConstructors)
{
    shz::math::matrix<shz::math::f32, 4, 4> projection;
	shz::math::frustum<shz::math::f32> f;
    
    projection = shz::math::matrix<shz::math::f32, 4, 4> ::ortho(-1, 1, -1, 1, 0.1f, 100.f);

    f.generate_planes_from_projection(projection);
    
    BOOST_CHECK(f.num_planes == 6);
}