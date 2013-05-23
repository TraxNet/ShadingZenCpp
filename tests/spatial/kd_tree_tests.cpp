#include <boost/test/unit_test.hpp>
#include <shz/spatial/kd_tree.hpp>
#include <shz/math/bbox.hpp>

BOOST_AUTO_TEST_CASE(kdtreeConstructors)
{
	shz::spatial::kd_tree<shz::math::bbox<shz::math::f32, 2>, int> tree;
    
}