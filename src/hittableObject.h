#ifndef HITTABLEOBJECT_H
#define HITTABLEOBJECT_H

#include <memory>

class material;

class hit_record {
public:
	point3 p;
	vec3 normal;
	std::shared_ptr<material> mat;
	double t;
	bool front_face;

	void set_face_normal(const ray& r, const vec3& outward_normal) {

		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};


class hittable_object {
public:
	virtual ~hittable_object() = default;

	virtual bool hit(const ray& r, interval tInterval, hit_record& h) const = 0;
};

#endif // !
