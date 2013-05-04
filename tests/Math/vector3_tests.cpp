#include <boost/test/unit_test.hpp>
#include <shz/math/vector.hpp>

/*
	VS2012 Compiler Bug makes impossible to use auto keyword for memory aligned structures.
	See: http://connect.microsoft.com/VisualStudio/feedback/details/775238/visual-c-2012-auto-keyword-ignores-structure-memory-alignment
	Workaround: either declare the variable with the 16bytes alignment or don't use the auto keyword
*/

extern bool is_aligned(void *p, intptr_t N);

BOOST_AUTO_TEST_CASE(vector3fConstructors)
{
	shz::math::vector<shz::math::f32, 3> v  = shz::math::vector<shz::math::f32, 3>(0.f);
	BOOST_CHECK(is_aligned(&v, 16));
	BOOST_CHECK(v.x == 0.f);
	BOOST_CHECK(v.y  == 0.f);
	BOOST_CHECK(v.z  == 0.f);

	v = shz::math::vector<shz::math::f32, 3>(1.f);
	BOOST_CHECK(v.data[0]  == 1.f);
	BOOST_CHECK(v.data[1]  == 1.f);

	v = shz::math::vector<shz::math::f32, 3>(1.4f);
	v -= 0.4f;
	BOOST_CHECK(v.data[0]  == 1.f);
	BOOST_CHECK(v.data[1]  == 1.f);
	BOOST_CHECK(v.z  == 1.f);
}

BOOST_AUTO_TEST_CASE(vector3fAdds)
{
	shz::math::vector<shz::math::f32, 3> v = shz::math::vector<shz::math::f32, 3>(1.4f);
	BOOST_CHECK(is_aligned(&v, 16));
	v += 0.4f;
	BOOST_CHECK(v.x  == 1.8f);
	BOOST_CHECK(v.y  == 1.8f);
	BOOST_CHECK(v.z  == 1.8f);

	shz::math::vector<shz::math::f32, 3> w = shz::math::vector<shz::math::f32, 3>(-1.4f);
	v += w;
	BOOST_CHECK_CLOSE(v.data[0], .4f,  0.00001f);
	BOOST_CHECK_CLOSE(v.data[1], .4f,  0.00001f);
}

BOOST_AUTO_TEST_CASE(vector3fSubs)
{
	shz::math::vector<shz::math::f32, 3> v = shz::math::vector<shz::math::f32, 3>(1.4f);
	v -= 0.4f;
	BOOST_CHECK(v.data[0]  == 1.f);
	BOOST_CHECK(v.data[1]  == 1.f);

	shz::math::vector<shz::math::f32, 3> w = shz::math::vector<shz::math::f32, 3>(-1.4f);
	v -= w;
	BOOST_CHECK_CLOSE(v.data[0], 2.4f,  0.00001f);
	BOOST_CHECK_CLOSE(v.data[1], 2.4f,  0.00001f);
}

BOOST_AUTO_TEST_CASE(vector3fMuls)
{
	shz::math::vector<shz::math::f32, 3> v = shz::math::vector<shz::math::f32, 3>(1.4f);
	v *= 0.5f;
	BOOST_CHECK(v.data[0]  == 0.7f);
	BOOST_CHECK(v.data[2]  == 0.7f);

	shz::math::vector<shz::math::f32, 3> w = shz::math::vector<shz::math::f32, 3>(-1.4f);
	v *= w;
	BOOST_CHECK_CLOSE(v.data[0], -0.98f,  0.00001f);
	BOOST_CHECK_CLOSE(v.data[1], -0.98f,  0.00001f);
}

BOOST_AUTO_TEST_CASE(vector3fDivs)
{
	shz::math::vector<shz::math::f32, 3> v = shz::math::vector<shz::math::f32, 3>(1.4f);
	v /= 0.5f;
	BOOST_CHECK(v.data[0]  == 2.8f);
	BOOST_CHECK(v.data[1]  == 2.8f);

	shz::math::vector<shz::math::f32, 3> w = shz::math::vector<shz::math::f32, 3>(2.f);
	v /= w;
	BOOST_CHECK_CLOSE(v.data[0], 1.4f,  0.00001f);
	BOOST_CHECK_CLOSE(v.data[1], 1.4f,  0.00001f);
}

BOOST_AUTO_TEST_CASE(vector3fDot)
{
	shz::math::vector<shz::math::f32, 3> v = shz::math::vector<shz::math::f32, 3>(1.4f);
	shz::math::vector<shz::math::f32, 3> w = shz::math::vector<shz::math::f32, 3>(0.5f);

	auto value = v.dot(w); 
	BOOST_CHECK_CLOSE(value, 2.1f, 0.00001f);
}

BOOST_AUTO_TEST_CASE(vector3fLength)
{
	shz::math::vector<shz::math::f32, 3> v = shz::math::vector<shz::math::f32, 3>(1.4f);
	BOOST_CHECK_CLOSE(v.sqrtlength(), 2.4249f, 0.01f);
	BOOST_CHECK_CLOSE(v.length(), 5.88f, 0.00001f);
}

BOOST_AUTO_TEST_CASE(vector3fNormalize)
{
	shz::math::vector<shz::math::f32, 3> v = shz::math::vector<shz::math::f32, 3>(1.4f);
	shz::math::vector<shz::math::f32, 3> w = v.normalize();
	BOOST_CHECK_CLOSE(w.data[0], 0.577350269f,  0.0001f);
	BOOST_CHECK_CLOSE(w.data[1], 0.577350269f,  0.0001f);
}