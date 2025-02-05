#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittableObject.h"


class material {
	
public:
	virtual ~material() = default;

	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const {
		return false;
	}


};

class lambertian : public material {
public:
	lambertian(const color& albedo): albedo(albedo) {}

	bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered) const override {
		auto scatterDirection = rec.normal + randomUnitVector();

		if (scatterDirection.near_zero())
			scatterDirection = rec.normal;

		scattered = ray(rec.p, scatterDirection);
		attenuation = albedo;
		return true;
	}

private:
	color albedo;

};

class metal : public material {
public:
	metal(const color& albedo): albedo(albedo) {}

	bool scatter(const ray& incRay, const hit_record& rec, color& attenuation, ray& scattered) const override {
		vec3 reflectedRay = reflect(incRay.direction(), rec.normal);
		scattered = ray(rec.p, reflectedRay);
		attenuation = albedo;
		return true;
	}


private:
	color albedo;
	
};




#endif // !MATERIAL_H
