// ShadingZen_Tests.cpp: define el punto de entrada de la aplicación de consola.
//



#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>
 
int add(int i, int j)
{
    return i + j;
}
 
BOOST_AUTO_TEST_CASE(universeInOrder)
{
    BOOST_CHECK(add(2, 2) == 4);
}
