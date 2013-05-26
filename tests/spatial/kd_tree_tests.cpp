#include <iostream>
#include <boost/test/unit_test.hpp>
#include <shz/spatial/kd_tree.hpp>
#include <shz/math/bbox.hpp>

using namespace shz::math;
using namespace shz::spatial;

std::ostream& operator<<(std::ostream& os, const kd_tree<bbox<f32, 2>, std::string>::pair_type & p)
{
    os << "[ first:" << p.first << " second:" << p.second << " ]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<kd_tree<bbox<f32, 2>, std::string>::pair_type>& p)
{
    os << "[ " << std::endl;
    
    for(auto element : p){
        os << element << "," << std::endl;
    }
    
    os << " ]" << std::endl;
    
    return os;
}



BOOST_AUTO_TEST_CASE(kdtreeConstructors)
{
	typedef kd_tree<bbox<f32, 2>, std::string>::pair_type pair_type;
	std::vector<pair_type> vec;
    
    f32 separation = 1.f;
    f32 size = 1.f;
    
    for (size_t i=0; i < 2; ++i) {
        for (size_t j=0; j < 2; ++j) {
            std::stringstream id;
            id << i << "_" << j;
            
            bbox<f32, 2> bounding_box;
            bounding_box.lower_bound[0] = i*size + separation*i;
            bounding_box.lower_bound[1] = j*size + separation*j;
            bounding_box.upper_bound[0] = i*size + size + separation*i;
            bounding_box.upper_bound[1] = j*size + size + separation*j;
            
            vec.push_back(pair_type(bounding_box, id.str()));
        }
    }
    
    std::cout << vec;
	
	kd_tree<bbox<f32, 2>, std::string> tree;
	kd_tree<bbox<f32, 2>, std::string> tree2(vec.begin(), vec.end());
    
}