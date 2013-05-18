#ifndef __SHZ_MATH_FRUSTUM__
#define __SHZ_MATH_FRUSTUM__

#include <array>
#include <shz/math/matrix.hpp>
#include <shz/math/plane.hpp>

namespace shz{ namespace math{

	template <typename T> struct frustum {
		static const size_t num_planes = 6;

		frustum(){}
		frustum(const shz::math::matrix<T, 4, 4>& clip){
			generate_planes_from_projection(clip);
		}

		bool is_point_inside(T x, T y, T z){
			for(size_t i=0; i < num_planes; ++i){
				if(planes[i].is_point_behind(x, y, z))
					return false;
			}
		}
		bool is_point_inside(const vector<T, 3>& p){
			for(size_t i=0; i < num_planes; ++i){
				if(planes[i].is_point_behind(p))
					return false;
			}
		}
		bool is_point_inside(const vector<T, 4>& p){
			for(size_t i=0; i < num_planes; ++i){
				if(planes[i].is_point_behind(p))
					return false;
			}
		}
		bool is_sphere_inside(T x, T y, T z, T radius) {
			for(size_t i=0; i < num_planes; ++i){
				if(planes[i].is_sphere_behind(x, y, z, radius))
					return false;
			}

			return true;
		}

		/*
		public boolean is_bbox_inside(BBox bbox) {
			for(int index=0; index < 6; index++){
				Plane plane = planes[index];

				Vector3 mins = bbox.getMins();
				Vector3 maxs = bbox.getMaxs();
				T x, y, z;
				x = mins.x;
				y = mins.y;
				z = mins.z;

				if(!plane.isPointBehind(x, y, z))
					continue;

				x = maxs.x;
				y = mins.y;
				z = mins.z;

				if(!plane.isPointBehind(x, y, z))
					continue;

				x = mins.x;
				y = maxs.y;
				z = mins.z;

				if(!plane.isPointBehind(x, y, z))
					continue;

				x = maxs.x;
				y = maxs.y;
				z = mins.z;

				if(!plane.isPointBehind(x, y, z))
					continue;

				x = mins.x;
				y = mins.y;
				z = maxs.z;

				if(!plane.isPointBehind(x, y, z))
					continue;

				x = maxs.x;
				y = mins.y;
				z = maxs.z;

				if(!plane.isPointBehind(x, y, z))
					continue;

				x = mins.x;
				y = maxs.y;
				z = maxs.z;

				if(!plane.isPointBehind(x, y, z))
					continue;

				x = maxs.x;
				y = maxs.y;
				z = maxs.z;

				if(!plane.isPointBehind(x, y, z))
					continue;

				return false;
			}

			return true;
		}*/
                
        enum plane_names{
			REAR = 0,
			FRONT,
			RIGHT,
			LEFT,
			TOP,
			BOTTOM
		};

		void generate_planes_from_projection(const matrix<T, 4, 4> clip){
			shz::math::plane<T>& plane = planes[plane_names::RIGHT];
			plane.eq[0] = clip[3] - clip[0];
			plane.eq[1] = clip[7] - clip[4];
			plane.eq[2] = clip[11] - clip[8];
			plane.eq[3] = clip[15] - clip[12];

			T t = plane.sqrtlength();
			plane.eq[0] /= t;
			plane.eq[1] /= t;
			plane.eq[2] /= t;
			plane.eq[3] /= t;

			plane = planes[plane_names::LEFT];
			plane.eq[0] = clip[3] + clip[0];
			plane.eq[1] = clip[7] + clip[4];
			plane.eq[2] = clip[11] + clip[8];
			plane.eq[3] = clip[15] + clip[12];

			t = plane.sqrtlength();
			plane.eq[0] /= t;
			plane.eq[1] /= t;
			plane.eq[2] /= t;
			plane.eq[3] /= t;

			plane = planes[plane_names::BOTTOM];
			plane.eq[0] = clip[3] + clip[1];
			plane.eq[1] = clip[7] + clip[5];
			plane.eq[2] = clip[11] + clip[9];
			plane.eq[3] = clip[15] + clip[13];

			t = (T) plane.sqrtlength();
			plane.eq[0] /= t;
			plane.eq[1] /= t;
			plane.eq[2] /= t;
			plane.eq[3] /= t;

			plane = planes[plane_names::TOP];
			plane.eq[0] = clip[3] - clip[1];
			plane.eq[1] = clip[7] - clip[5];
			plane.eq[2] = clip[11] - clip[9];
			plane.eq[3] = clip[15] - clip[13];

			t = plane.sqrtlength();
			plane.eq[0] /= t;
			plane.eq[1] /= t;
			plane.eq[2] /= t;
			plane.eq[3] /= t;

			plane = planes[plane_names::FRONT];
			plane.eq[0] = clip[3] - clip[2];
			plane.eq[1] = clip[7] - clip[6];
			plane.eq[2] = clip[11] - clip[10];
			plane.eq[3] = clip[15] - clip[14];

			t = plane.sqrtlength();
			plane.eq[0] /= t;
			plane.eq[1] /= t;
			plane.eq[2] /= t;
			plane.eq[3] /= t;

			plane = planes[plane_names::REAR];
			plane.eq[0] = clip[3] + clip[2];
			plane.eq[1] = clip[7] + clip[6];
			plane.eq[2] = clip[11] + clip[10];
			plane.eq[3] = clip[15] + clip[14];

			t = plane.sqrtlength();
			plane.eq[0] /= t;
			plane.eq[1] /= t;
			plane.eq[2] /= t;
			plane.eq[3] /= t;

		}

		

		std::array<shz::math::plane<T>, num_planes> planes;
	};


} }

#endif // __SHZ_MATH_FRUSTUM__