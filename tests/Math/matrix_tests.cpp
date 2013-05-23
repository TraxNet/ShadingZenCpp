#include <boost/test/unit_test.hpp>
#include <shz/math/matrix.hpp>
 

BOOST_AUTO_TEST_CASE(matrixConstructors)
{
	
	auto m = shz::math::matrix<shz::math::f64, 2, 2>::identity();
	auto n = shz::math::matrix<shz::math::f64, 2, 2>::identity();
	
	BOOST_CHECK(true == m.is_identity());
	BOOST_CHECK(true == n.is_identity());
	
	BOOST_CHECK(1.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(1.f == m.data[3]);
}

BOOST_AUTO_TEST_CASE(matrixSizeConstructors)
{
	auto m = shz::math::matrix<shz::math::f64, 20, 30>::identity();
	auto n = shz::math::matrix<shz::math::f64, 20, 30>::identity();


	BOOST_CHECK(true == m.is_identity());
	BOOST_CHECK(true == n.is_identity());

	BOOST_CHECK(20*30 == m.size);
	BOOST_CHECK(20 == m.mindimension);
	BOOST_CHECK(20 == m.columns);
	BOOST_CHECK(30 == m.rows);
}

BOOST_AUTO_TEST_CASE(matrixAdds)
{
	auto m = shz::math::matrix<shz::math::f64, 2, 2>::identity();
	auto n = shz::math::matrix<shz::math::f64, 2, 2>::identity();

	auto j = m+n;
	BOOST_CHECK(true != j.is_identity());
	BOOST_CHECK(2*2 == j.size);
	BOOST_CHECK(2.f == j.data[0]);
	BOOST_CHECK(0.f == j.data[1]);
	BOOST_CHECK(0.f == j.data[2]);
	BOOST_CHECK(2.f == j.data[3]);

	m += n;
	BOOST_CHECK(2.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(2.f == m.data[3]);

	n += 2.f;
	BOOST_CHECK(3.f == n.data[0]);
	BOOST_CHECK(2.f == n.data[1]);
	BOOST_CHECK(2.f == n.data[2]);
	BOOST_CHECK(3.f == n.data[3]);
}

BOOST_AUTO_TEST_CASE(matrixSubs)
{
	auto m = shz::math::matrix<shz::math::f64, 2, 2>::identity();
	auto n = shz::math::matrix<shz::math::f64, 2, 2>::identity();

	auto j = m-n;
	BOOST_CHECK(true != j.is_identity());
	BOOST_CHECK(2*2 == j.size);
	BOOST_CHECK(0.f == j.data[0]);
	BOOST_CHECK(0.f == j.data[1]);
	BOOST_CHECK(0.f == j.data[2]);
	BOOST_CHECK(0.f == j.data[3]);

	m -= n;
	BOOST_CHECK(0.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(0.f == m.data[3]);

	n -= 2.f;
	BOOST_CHECK(-1.f == n.data[0]);
	BOOST_CHECK(-2.f == n.data[1]);
	BOOST_CHECK(-2.f == n.data[2]);
	BOOST_CHECK(-1.f == n.data[3]);
}


BOOST_AUTO_TEST_CASE(matrixMuls)
{
	auto m = shz::math::matrix<shz::math::f64, 2, 2>::identity();
	auto n = shz::math::matrix<shz::math::f64, 2, 2>::identity();

	auto j = m*n;
	BOOST_CHECK(true == j.is_identity());
	BOOST_CHECK(2*2 == j.size);
	BOOST_CHECK(1.f == j.data[0]);
	BOOST_CHECK(0.f == j.data[1]);
	BOOST_CHECK(0.f == j.data[2]);
	BOOST_CHECK(1.f == j.data[3]);

	auto v = shz::math::vector<shz::math::f64, 2>();
	v.data[0] = 2.f;
	v.data[1] = 2.f;
	auto b = m*v;
	BOOST_CHECK(2.f == b.data[0]);
	BOOST_CHECK(2.f == b.data[1]);

	m = n*2;
	BOOST_CHECK(true != m.is_identity());
	b = m*v;
	BOOST_CHECK(4.f == b.data[0]);
	BOOST_CHECK(4.f == b.data[1]);

	m *= n;
	BOOST_CHECK(true != m.is_identity());
	BOOST_CHECK(2.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(2.f == m.data[3]);

	m *= 2;
	BOOST_CHECK(true != m.is_identity());
	BOOST_CHECK(4.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(4.f == m.data[3]);

}




/*
BOOST_AUTO_TEST_CASE(matrixPerformance)
{
	auto m = shz::math::matrix<shz::math::f64, 200, 200>::identity();
	auto n = shz::math::matrix<shz::math::f64, 200, 200>::identity();

	for(size_t i=0; i<10000; i++)
		auto r = m*n;
}*/
