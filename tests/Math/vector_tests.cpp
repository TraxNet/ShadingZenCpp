#define BOOST_TEST_MODULE Math
#include <boost/test/unit_test.hpp>
#include <shz/math/vector.hpp>
 

BOOST_AUTO_TEST_CASE(vectorConstructors)
{
	auto v = shz::math::vector<shz::math::f64, 2>(0.0);
    BOOST_CHECK(v.data[0] == 0.f);
	BOOST_CHECK(v.data[1]  == 0.f);

	v = shz::math::vector<shz::math::f64, 2>(1.0);
	BOOST_CHECK(v.data[0]  == 1.f);
	BOOST_CHECK(v.data[1]  == 1.f);

	v = shz::math::vector<shz::math::f64, 2>(1.4);
	v -= 0.4;
	BOOST_CHECK_CLOSE(v.data[0], 1.0, 0.000001);
	BOOST_CHECK_CLOSE(v.data[1], 1.0, 0.000001);
}

BOOST_AUTO_TEST_CASE(vectorAdds)
{
	auto v = shz::math::vector<shz::math::f64, 2>(1.4);
	v += 0.4;
	BOOST_CHECK_CLOSE(v.data[0], 1.8, 0.000001);
	BOOST_CHECK_CLOSE(v.data[1], 1.8, 0.000001);

	auto w = shz::math::vector<shz::math::f64, 2>(-1.4);
	v += w;
	BOOST_CHECK_CLOSE(v.data[0], .4,  0.00001);
	BOOST_CHECK_CLOSE(v.data[1], .4,  0.00001);
}

BOOST_AUTO_TEST_CASE(vectorSubs)
{
	auto v = shz::math::vector<shz::math::f64, 2>(1.4);
	v -= 0.4;
	BOOST_CHECK_CLOSE(v.data[0], 1.0, 0.000001);
	BOOST_CHECK_CLOSE(v.data[1], 1.0, 0.000001);

	auto w = shz::math::vector<shz::math::f64, 2>(-1.4);
	v -= w;
	BOOST_CHECK_CLOSE(v.data[0], 2.4,  0.00001);
	BOOST_CHECK_CLOSE(v.data[1], 2.4,  0.00001);
}

BOOST_AUTO_TEST_CASE(vectorMuls)
{
	auto v = shz::math::vector<shz::math::f64, 2>(1.4);
	v *= 0.5;
	BOOST_CHECK_CLOSE(v.data[0], 0.7, 0.000001);
	BOOST_CHECK_CLOSE(v.data[1], 0.7, 0.000001);

	auto w = shz::math::vector<shz::math::f64, 2>(-1.4);
	v *= w;
	BOOST_CHECK_CLOSE(v.data[0], -0.98f,  0.00001);
	BOOST_CHECK_CLOSE(v.data[1], -0.98f,  0.00001);
}

BOOST_AUTO_TEST_CASE(vectorDivs)
{
	auto v = shz::math::vector<shz::math::f64, 2>(1.4);
	v /= 0.5;
	BOOST_CHECK_CLOSE(v.data[0], 2.8, 0.00001);
	BOOST_CHECK_CLOSE(v.data[1], 2.8, 0.00001);

	auto w = shz::math::vector<shz::math::f64, 2>(2.0);
	v /= w;
	BOOST_CHECK_CLOSE(v.data[0], 1.4,  0.00001);
	BOOST_CHECK_CLOSE(v.data[1], 1.4,  0.00001);
}

BOOST_AUTO_TEST_CASE(vectorDot)
{
	auto v = shz::math::vector<shz::math::f64, 2>(1.4f);
	auto w = shz::math::vector<shz::math::f64, 2>(0.5f);

	auto value = v.dot(w);
	BOOST_CHECK_CLOSE(value, 1.4f, 0.00001f);
}

BOOST_AUTO_TEST_CASE(vectorLength)
{
	auto v = shz::math::vector<shz::math::f64, 2>(1.4f);
	BOOST_CHECK_CLOSE(v.sqrtlength(), 1.9798f, 0.01f);
	BOOST_CHECK_CLOSE(v.length(), 3.92f, 0.00001f);
}

BOOST_AUTO_TEST_CASE(vectorNormalize)
{
	auto v = shz::math::vector<shz::math::f64, 2>(1.4f);
	auto w = v.normalize();
	BOOST_CHECK_CLOSE(w.data[0], ::sqrt(0.5f),  0.00001f);
	BOOST_CHECK_CLOSE(w.data[1], ::sqrt(0.5f),  0.00001f);
}

void init_array(shz::math::f64 *taret, shz::math::f64 value, size_t array_size){
	for(size_t i=0; i<array_size; i++)
		taret[i] = value;
}

BOOST_AUTO_TEST_CASE(vectorArrayAdd)
{
	const size_t array_size = 128;
	

	shz::math::f64 left[array_size], right[array_size], target[array_size];

	init_array(left, 1.0, array_size);
	init_array(right, 2.0, array_size);

	shz::math::add_array<shz::math::vector<shz::math::f64,4>,array_size>(left, right, target);

	for(size_t i=0; i<array_size; ++i){
		BOOST_CHECK_CLOSE(target[i], 3.0,  0.00001f);
	}
}







