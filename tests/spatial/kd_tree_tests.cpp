#include <iostream>
#include <boost/test/unit_test.hpp>
#include <shz/spatial/kd_tree.hpp>
#include <shz/math/bbox.hpp>
#include <shz/math/ray.hpp>
#include <shz/math/intersection.hpp>

using namespace shz::math;
using namespace shz::spatial;

std::ostream& operator<<(std::ostream& os, const kd_tree<bbox<f32, 3>, std::string>::pair_type & p)
{
    os << "[ first:" << p.first << " second:" << p.second << " ]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<kd_tree<bbox<f32, 3>, std::string>::pair_type>& p)
{
    os << "[ " << std::endl;
    
    for(auto element : p){
        os << element << "," << std::endl;
    }
    
    os << " ]" << std::endl;
    
    return os;
}


typedef kd_tree<bbox<f32, 3>, std::string>::pair_type pair_type;

std::vector<pair_type> create_evenly_distributed_set(const size_t dimension1, const size_t dimension2, const size_t dimension3, const float size, const float separation){
	std::vector<pair_type> vec;

	// Create a set of bounding boxes to be partitioned by the kd-tree
    for (size_t i=0; i < dimension1; ++i) {
        for (size_t j=0; j < dimension2; ++j) {
            for (size_t k=0; k< dimension3; ++k) {

                std::stringstream id;
                id << i << "_" << j << "_" << k;
            
                bbox<f32, 3> bounding_box;
                bounding_box.lower_bound[0] = i*size + separation*i;
                bounding_box.lower_bound[1] = j*size + separation*j;
                bounding_box.lower_bound[2] = j*size + separation*j;
                bounding_box.upper_bound[0] = i*size + size + separation*i;
                bounding_box.upper_bound[1] = j*size + size + separation*j;
                bounding_box.upper_bound[2] = j*size + size + separation*j;
            
                vec.push_back(pair_type(bounding_box, id.str()));
            }
        }
    }

	return vec;
}


BOOST_AUTO_TEST_CASE(kdtreeConstructors)
{
	    
    const f32 separation = 1.f;
    const f32 size = 1.f;
	const size_t test_bboxes_dimension1 = 2, test_bboxes_dimension2 = 2, test_bboxes_dimension3 = 2;
    
	std::vector<pair_type> vec = create_evenly_distributed_set(test_bboxes_dimension1, test_bboxes_dimension2, test_bboxes_dimension3, size, separation);
    
    std::cout << vec;
	
	kd_tree<bbox<f32, 3>, std::string> tree;
	BOOST_CHECK(tree.empty());
	BOOST_CHECK(tree.size() == 0);
	tree.build_from_set(vec.begin(), vec.end());
	BOOST_CHECK(!tree.empty());
	BOOST_CHECK(tree.size() == test_bboxes_dimension2*test_bboxes_dimension1*test_bboxes_dimension3);
    
}


BOOST_AUTO_TEST_CASE(kdtreeTraverse)
{
    const f32 separation = 1.f;
    const f32 size = 1.f;
	const size_t test_bboxes_dimension1 = 2, test_bboxes_dimension2 = 2, test_bboxes_dimension3 = 2;
    
	std::vector<pair_type> vec = create_evenly_distributed_set(test_bboxes_dimension1, test_bboxes_dimension2, test_bboxes_dimension3, size, separation);
    
    kd_tree<bbox<f32, 3>, std::string> tree;
    tree.build_from_set(vec.begin(), vec.end());
	BOOST_CHECK(!tree.empty());
	BOOST_CHECK(tree.size() == test_bboxes_dimension2*test_bboxes_dimension1*test_bboxes_dimension3);
    
    vector<shz::math::f32, 3> o;
	o.data[0] = 0;
	o.data[1] = 0;
    o.data[2] = 0;
	vector<shz::math::f32, 3> d;
	d.data[0] = 0;
	d.data[1] = 1;
    d.data[3] = 0;
    shz::math::ray<f32> r(o, d, 20.f, 0.f);
    BOOST_CHECK(tree.traverse(r, [](shz::math::ray<f32> input, bbox<f32, 3> key, shz::math::intersector<ray<f32>, bbox<f32, 3> > inter) -> bool {
        return false;
    }));
}