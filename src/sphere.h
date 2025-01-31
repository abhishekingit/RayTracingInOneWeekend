#ifndef SPHERE_H
#define SPHERE_H

#include "hittableObject.h"

class sphere : public hittable_object {
public:
	sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}
	
	bool hit(const ray& r, interval tInterval, hit_record& rec) const override {
		vec3 centerVec = center - r.origin();
		auto a = r.direction().length_squared();
		auto h = dot(r.direction(), centerVec);
		auto c = centerVec.length_squared() - radius * radius;
		auto SphereEqDiscriminant = h * h - a * c;

		if (SphereEqDiscriminant < 0.0) {
			return false;
		}

		auto sqrtDisc = std::sqrt(SphereEqDiscriminant);
		
		auto root = (h - sqrtDisc) / a;

		if (!tInterval.surrounds(root)) {
			root = (h + sqrtDisc) / a;
			if (!tInterval.surrounds(root)) {
				return false;
			}
		}

		rec.t = root;
		rec.p = r.aT(rec.t);
		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}



private:
	point3 center;
	double radius;

};


#endif // ! SPHERE_H
