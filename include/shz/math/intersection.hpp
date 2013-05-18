#ifndef __SHZ_MATH_INTERSECTION__
#define __SHZ_MATH_INTERSECTION__

#include <array>
#include <stdexcept> 
#include <shz/math/math.hpp>
#include <shz/math/ray.hpp>
#include <shz/math/plane.hpp>
#include <shz/math/sphere.hpp>
#include <shz/math/bbox.hpp>

namespace shz{ namespace math{

	/** template functor */
	template<typename T1, typename T2> struct intersector {
		bool intersect;
		T1 operand1;
		T2 operand2;
	};

	enum IntersectState {
		OUTSIDE,
		INSIDE,
		PARTIAL_INSIDE
	};
	
	/** Ray plane intersector functor */
	template<typename U> struct intersector <shz::math::ray<U>, shz::math::plane<U> > {

		bool operator()(const shz::math::ray<U>& operand1, const shz::math::plane<U>& operand2){
			return check(operand1, operand2);
		}	
		bool operator()(const shz::math::plane<U>& operand2, const shz::math::ray<U>& operand1){
			return check(operand1, operand2);
		}	
		bool check(const shz::math::ray<U>& operand1, const shz::math::plane<U>& operand2){
			U denominator = operand1.direction.dot(operand2.normal);

			if(isZero(denominator)){
				if(isZero(operand1.origin.dot(operand2.normal) - operand2.d)){
					state = IntersectState::INSIDE;
					return true;
				}else{
					state = IntersectState::OUTSIDE;
					return false;
				}
			}

			U t = -(operand1.origin.dot(operand2.normal) + operand2.d) / denominator;

			if(t == 0){
				state = IntersectState::INSIDE;
				length = t;
				point = operand1.origin;
				return true;
			}else if(t >= 0 && operand1.length >= t){
				state = IntersectState::PARTIAL_INSIDE;
				length = t;
				point = operand1.origin + operand1.direction*t;
			} else{
				state = IntersectState::OUTSIDE;
			}		

			return !(state == IntersectState::OUTSIDE);
		}
		
		IntersectState state;
		shz::math::vector<U, 3> point;
		U length;
	};

	template<typename U> struct intersector <shz::math::plane<U>, shz::math::ray<U>> 
		: intersector <shz::math::ray<U>, shz::math::plane<U>> {};

	template<typename U> struct intersector <shz::math::ray<U>, shz::math::bbox<U>> {

		bool operator()(const shz::math::ray<U>& operand1, const shz::math::bbox<U>& operand2){
			return check(operand1, operand2);
		}	
		bool operator()(const shz::math::bbox<U>& operand2, const shz::math::ray<U>& operand1){
			return check(operand1, operand2);
		}	
		bool check(const shz::math::ray<U>& operand1, const shz::math::bbox<U>& operand2){
			U MaxT[] = {-1, -1, -1};
			std::array<U, 3> Mins(operand2.mins.data);
			std::array<U, 3> Maxs(operand2.maxs.data);
			const U* origin = operand1.origin.data.data();
			const U* dir = operand1.direction.data.data();
			int i = 0;
			bool inside = true;
			state = IntersectState::OUTSIDE;

			// Find candidate planes.
			for( i=0; i<3; i++ ) {
				Mins[i] -= operand1.radius;
				Maxs[i] += operand1.radius;

				if( origin[i] < Mins[i] ) {
					point[i] = Mins[i];
					inside = false;

					// Calculate T distances to candidate planes
					MaxT[i] = (Mins[i] - origin[i]) / dir[i];
				}
				else if( origin[i] > Maxs[i] ) {
					point[i] = Maxs[i];
					inside = false;

					// Calculate T distances to candidate planes
					MaxT[i] = (Maxs[i] - origin[i]) / dir[i];
				}
			}

			// Ray origin inside bounding box
			if( inside ){ state = IntersectState::INSIDE; return true; }

			// Get largest of the maxT's for final choice of intersection
			int WhichPlane = 0;
			if( MaxT[1] > MaxT[WhichPlane])	WhichPlane = 1;
			if( MaxT[2] > MaxT[WhichPlane])	WhichPlane = 2;

			// Check final candidate actually inside box
			//if( IR(MaxT[WhichPlane])&SIGN_BITMASK ) return false;
			if( MaxT[WhichPlane] < 0) return false;

			for( i=0; i<3; i++ ) {
				if( i!=WhichPlane ) {
					point[i] = origin[i] + MaxT[WhichPlane] * dir[i];
					if( point[i]<Mins[i] || point[i]>Maxs[i] )	return false;
				}
			}

			length = (operand1.origin - point).length();
			state = IntersectState::PARTIAL_INSIDE;
			return true;
		}


		IntersectState state;
		shz::math::vector<U, 3> point;
		U length;
	};

	template<typename U> struct intersector <shz::math::bbox<U>, shz::math::ray<U>> 
		: intersector <shz::math::ray<U>, shz::math::bbox<U>> {};


	/** Ray sphere intersector functor */
	template<typename U> struct intersector <shz::math::ray<U>, shz::math::sphere<U> > {

		bool operator()(const shz::math::ray<U>& operand1, const shz::math::sphere<U>& operand2){
			return check(operand1, operand2);
		}	
		bool operator()(const shz::math::sphere<U>& operand2, const shz::math::ray<U>& operand1){
			return check(operand1, operand2);
		}	
		bool check(const shz::math::ray<U>& operand1, const shz::math::sphere<U>& operand2){
			shz::math::vector<U, 3> oc = operand1.origin - operand2.center;
			shz::math::vector<U, 3> co = operand2.center -  operand1.origin;
			U A = operand1.length;
			U B = 2*oc.dot(operand1.direction);
			U diam = operand2.radius*2;
			U C = oc.dot(oc)-operand2.radius*operand2.radius;
			U disc = B*B - 4*A*C;

			state = IntersectState::OUTSIDE;

			if( disc < 0.0f )
				return false;
			length = 0.f;

			U distSqrt = ::sqrt(disc);
			U q;
			if (B < 0)
				q = (-B - distSqrt)/2.f;
			else
				q = (-B + distSqrt)/2.f;

			// compute t0 and t1
			U t0 = q / A;
			U t1 = C / q;

			// make sure t0 is smaller than t1
			if (t0 > t1)
			{
				// if t0 is bigger than t1 swap them around
				U temp = t0;
				t0 = t1;
				t1 = temp;
			}

			// if t1 is less than zero, the object is in the ray's negative direction
			// and consequently the ray misses the sphere
			if (t1 < 0)
				return false;
	
			if (t0 < 0) // if t0 is less than zero, the intersection point is at t1
				length = t1;			
			else // else the intersection point is at t0
				length = t0;
				
			state = IntersectState::PARTIAL_INSIDE;
			point = operand1.origin + operand1.direction*length;
			return true;
		}


		IntersectState state;
		shz::math::vector<U, 3> point;
		U length;
	};

	template<typename U> struct intersector <shz::math::sphere<U>, shz::math::ray<U> > 
	: intersector <shz::math::ray<U>, shz::math::sphere<U> > {};
} }

#endif // __SHZ_MATH_INTERSECTION__