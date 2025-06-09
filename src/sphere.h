#ifndef SPHERE_H
#define SPHERE_H

#include "hittableObject.h"

class sphere : public hittable_object {
public:
	sphere(const point3& staticCenter, double radius, std::shared_ptr<material> mat) : center(staticCenter, vec3(0,0,0)), radius(std::fmax(0, radius)), mat(mat)  {}

	sphere(const point3& center1, const point3& center2, double radius, std::shared_ptr<material> mat) : center(center1, center2 - center1), radius(std::fmax(0, radius)), mat(mat) {}
	
	bool hit(const ray& r, interval tInterval, hit_record& rec) const override {
		point3 currentCenter = center.aT(r.time());
		vec3 centerVec = currentCenter - r.origin();
		auto a = r.direction().length_squared();
		auto h = dot(r.direction(), centerVec);
		auto c = centerVec.length_squared() - radius * radius;
		auto SphereEqDiscriminant = h * h - a * c;

		if (SphereEqDiscriminant < 0) {
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
		vec3 outward_normal = (rec.p - currentCenter) / radius;
		rec.set_face_normal(r, outward_normal);
		rec.mat = mat;

		return true;
	}



private:
	ray center;
	double radius;
	std::shared_ptr<material> mat;

};


#endif // ! SPHERE_H
