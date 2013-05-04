#include <boost/test/unit_test.hpp>
#include <shz/math/matrix.hpp>
 
extern bool is_aligned(void *p, intptr_t N);

BOOST_AUTO_TEST_CASE(matrix4fConstructors)
{
	shz::math::matrix4f m = shz::math::matrix4f::identity();
	shz::math::matrix4f n = shz::math::matrix4f::identity();
	shz::math::matrix4f nn = shz::math::matrix4f(n);
	BOOST_CHECK(is_aligned(&m, 16));
	BOOST_CHECK(is_aligned(&n, 16));
	BOOST_CHECK(is_aligned(&nn, 16));
	
	BOOST_CHECK(true == m.is_identity());
	BOOST_CHECK(true == n.is_identity());
	BOOST_CHECK(true == nn.is_identity());
	
	BOOST_CHECK(1.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(0.f == m.data[3]);

	BOOST_CHECK(0.f == m.data[4]);
	BOOST_CHECK(1.f == m.data[5]);
	BOOST_CHECK(0.f == m.data[6]);
	BOOST_CHECK(0.f == m.data[7]);

	BOOST_CHECK(0.f == m.data[8]);
	BOOST_CHECK(0.f == m.data[9]);
	BOOST_CHECK(1.f == m.data[10]);
	BOOST_CHECK(0.f == m.data[11]);

	BOOST_CHECK(0.f == m.data[12]);
	BOOST_CHECK(0.f == m.data[13]);
	BOOST_CHECK(0.f == m.data[14]);
	BOOST_CHECK(1.f == m.data[15]);
}

BOOST_AUTO_TEST_CASE(matrix4fSizeConstructors)
{
	shz::math::matrix4f m = shz::math::matrix4f::identity();
	shz::math::matrix4f n = shz::math::matrix4f::identity();


	BOOST_CHECK(true == m.is_identity());
	BOOST_CHECK(true == n.is_identity());

	BOOST_CHECK(4*4 == m.size);
	BOOST_CHECK(4 == m.mindimension);
	BOOST_CHECK(4 == m.columns);
	BOOST_CHECK(4 == m.rows);
}

BOOST_AUTO_TEST_CASE(matrix4fAdds)
{
	shz::math::matrix4f m = shz::math::matrix4f::identity();
	shz::math::matrix4f n = shz::math::matrix4f::identity();

	shz::math::matrix4f j = m+n;
	BOOST_CHECK(true != j.is_identity());
	BOOST_CHECK(4*4 == j.size);
	BOOST_CHECK(2.f == j.data[0]);
	BOOST_CHECK(0.f == j.data[1]);
	BOOST_CHECK(0.f == j.data[2]);
	BOOST_CHECK(0.f == j.data[3]);

	BOOST_CHECK(0.f == j.data[4]);
	BOOST_CHECK(2.f == j.data[5]);
	BOOST_CHECK(0.f == j.data[6]);
	BOOST_CHECK(0.f == j.data[7]);

	BOOST_CHECK(0.f == j.data[8]);
	BOOST_CHECK(0.f == j.data[9]);
	BOOST_CHECK(2.f == j.data[10]);
	BOOST_CHECK(0.f == j.data[11]);

	BOOST_CHECK(0.f == j.data[12]);
	BOOST_CHECK(0.f == j.data[13]);
	BOOST_CHECK(0.f == j.data[14]);
	BOOST_CHECK(2.f == j.data[15]);

	m += n;
	BOOST_CHECK(2.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(0.f == m.data[3]);

	BOOST_CHECK(0.f == m.data[4]);
	BOOST_CHECK(2.f == m.data[5]);
	BOOST_CHECK(0.f == m.data[6]);
	BOOST_CHECK(0.f == m.data[7]);

	BOOST_CHECK(0.f == m.data[8]);
	BOOST_CHECK(0.f == m.data[9]);
	BOOST_CHECK(2.f == m.data[10]);
	BOOST_CHECK(0.f == m.data[11]);

	BOOST_CHECK(0.f == m.data[12]);
	BOOST_CHECK(0.f == m.data[13]);
	BOOST_CHECK(0.f == m.data[14]);
	BOOST_CHECK(2.f == m.data[15]);

	n += 2.f;
	BOOST_CHECK(3.f == n.data[0]);
	BOOST_CHECK(2.f == n.data[1]);
	BOOST_CHECK(2.f == n.data[2]);
	BOOST_CHECK(2.f == n.data[3]);

	BOOST_CHECK(2.f == n.data[4]);
	BOOST_CHECK(3.f == n.data[5]);
	BOOST_CHECK(2.f == n.data[6]);
	BOOST_CHECK(2.f == n.data[7]);

	BOOST_CHECK(2.f == n.data[8]);
	BOOST_CHECK(2.f == n.data[9]);
	BOOST_CHECK(3.f == n.data[10]);
	BOOST_CHECK(2.f == n.data[11]);

	BOOST_CHECK(2.f == n.data[12]);
	BOOST_CHECK(2.f == n.data[13]);
	BOOST_CHECK(2.f == n.data[14]);
	BOOST_CHECK(3.f == n.data[15]);
}

BOOST_AUTO_TEST_CASE(matrix4fSubs)
{
	shz::math::matrix4f m = shz::math::matrix4f::identity();
	shz::math::matrix4f n = shz::math::matrix4f::identity();

	shz::math::matrix4f j = m-n;
	BOOST_CHECK(true != j.is_identity());
	BOOST_CHECK(16 == j.size);
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
	BOOST_CHECK(-2.f == n.data[3]);

	BOOST_CHECK(-2.f == n.data[4]);
	BOOST_CHECK(-1.f == n.data[5]);
	BOOST_CHECK(-2.f == n.data[6]);
	BOOST_CHECK(-2.f == n.data[7]);

	BOOST_CHECK(-2.f == n.data[8]);
	BOOST_CHECK(-2.f == n.data[9]);
	BOOST_CHECK(-1.f == n.data[10]);
	BOOST_CHECK(-2.f == n.data[11]);

	BOOST_CHECK(-2.f == n.data[12]);
	BOOST_CHECK(-2.f == n.data[13]);
	BOOST_CHECK(-2.f == n.data[14]);
	BOOST_CHECK(-1.f == n.data[15]);
}


BOOST_AUTO_TEST_CASE(matrix4fMuls)
{
	shz::math::matrix4f m = shz::math::matrix4f::identity();
	shz::math::matrix4f n = shz::math::matrix4f::identity();

	shz::math::matrix4f j = m*n;
	BOOST_CHECK(true == j.is_identity());
	BOOST_CHECK(4*4 == j.size);

	shz::math::vector4f v = shz::math::vector4f();
	v.data[0] = 2.f;
	v.data[1] = 2.f;
	v.data[2] = 0.f;
	v.data[3] = 0.f;
	shz::math::vector4f b = m*v;
	BOOST_CHECK(2.f == b.data[0]);
	BOOST_CHECK(2.f == b.data[1]);
	BOOST_CHECK(0.f == b.data[2]);
	BOOST_CHECK(0.f == b.data[3]);

	m = n*2;
	BOOST_CHECK(true != m.is_identity());
	b = m*v;
	BOOST_CHECK(4.f == b.data[0]);
	BOOST_CHECK(4.f == b.data[1]);
	BOOST_CHECK(0.f == b.data[2]);
	BOOST_CHECK(0.f == b.data[3]);

	m *= n;
	BOOST_CHECK(true != m.is_identity());
	BOOST_CHECK(2.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(0.f == m.data[3]);

	BOOST_CHECK(0.f == m.data[4]);
	BOOST_CHECK(2.f == m.data[5]);
	BOOST_CHECK(0.f == m.data[6]);
	BOOST_CHECK(0.f == m.data[7]);

	BOOST_CHECK(0.f == m.data[8]);
	BOOST_CHECK(0.f == m.data[9]);
	BOOST_CHECK(2.f == m.data[10]);
	BOOST_CHECK(0.f == m.data[11]);

	BOOST_CHECK(0.f == m.data[12]);
	BOOST_CHECK(0.f == m.data[13]);
	BOOST_CHECK(0.f == m.data[14]);
	BOOST_CHECK(2.f == m.data[15]);

	m *= 2;
	BOOST_CHECK(true != m.is_identity());
	BOOST_CHECK(4.f == m.data[0]);
	BOOST_CHECK(0.f == m.data[1]);
	BOOST_CHECK(0.f == m.data[2]);
	BOOST_CHECK(0.f == m.data[3]);

	BOOST_CHECK(0.f == m.data[4]);
	BOOST_CHECK(4.f == m.data[5]);
	BOOST_CHECK(0.f == m.data[6]);
	BOOST_CHECK(0.f == m.data[7]);

	BOOST_CHECK(0.f == m.data[8]);
	BOOST_CHECK(0.f == m.data[9]);
	BOOST_CHECK(4.f == m.data[10]);
	BOOST_CHECK(0.f == m.data[11]);

	BOOST_CHECK(0.f == m.data[12]);
	BOOST_CHECK(0.f == m.data[13]);
	BOOST_CHECK(0.f == m.data[14]);
	BOOST_CHECK(4.f == m.data[15]);

}

/*
BOOST_AUTO_TEST_CASE(matrixPerformance)
{
	auto m = shz::math::matrix<shz::math::f32, 200, 200>::identity();
	auto n = shz::math::matrix<shz::math::f32, 200, 200>::identity();

	for(size_t i=0; i<10000; i++)
		auto r = m*n;
}*/
