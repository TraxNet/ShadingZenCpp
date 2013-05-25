#include <boost/test/unit_test.hpp>
#include <shz/spatial/kd_tree.hpp>
#include <shz/math/bbox.hpp>

using namespace shz::math;
using namespace shz::spatial;

BOOST_AUTO_TEST_CASE(kdtreeConstructors)
{
	typedef kd_tree<bbox<f32, 2>, vector<f32, 2>>::pair_type pair_type;
	std::vector<pair_type> vec;
	vec.push_back(pair_type(bbox<f32, 2>(), vector<f32, 2>()));
	vec.push_back(pair_type(bbox<f32, 2>(), vector<f32, 2>()));
	vec.push_back(pair_type(bbox<f32, 2>(), vector<f32, 2>()));

	kd_tree<bbox<f32, 2>, vector<f32, 2>> tree;
	kd_tree<bbox<f32, 2>, vector<f32, 2>> tree2(vec.begin(), vec.end());
    
}