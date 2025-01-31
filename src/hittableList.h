#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include<vector>

#include "hittableObject.h"


class hittable_list: public hittable_object {
public:
	std::vector<std::shared_ptr<hittable_object>> objects;

	hittable_list() {};

	hittable_list(std::shared_ptr<hittable_object> object) {
		add(object);
	}

	void clear() {
		objects.clear();
	}

	void add(std::shared_ptr<hittable_object> object) {
		objects.push_back(object);
	}

	bool hit(const ray& r, interval tInterval, hit_record& rec) const override {
		hit_record temp_rec;
		bool hit_object = false;
		auto closest_so_far = tInterval.max;

		for (const auto& object : objects) {
			if (object->hit(r, interval(tInterval.min, closest_so_far), temp_rec)) {
				hit_object = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_object;
	}

};


#endif // !HITTABLE_LIST_H
