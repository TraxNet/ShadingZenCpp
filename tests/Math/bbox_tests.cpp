#include <boost/test/unit_test.hpp>
#include <shz/math/bbox.hpp>


BOOST_AUTO_TEST_CASE(bboxConstructors)
{
	shz::math::bbox<shz::math::f64> p1;
    shz::math::bbox<shz::math::f32> p2;
    
    
    p1[0].data[0] = 0;
    p2[0].x = 0;
    p2[1].x = 0;
}


