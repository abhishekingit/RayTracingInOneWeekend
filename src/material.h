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
	metal(const color& albedo, double fuzz): albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

	bool scatter(const ray& incRay, const hit_record& rec, color& attenuation, ray& scattered) const override {
		vec3 reflectedRay = reflect(incRay.direction(), rec.normal);
		reflectedRay = unit_vector(reflectedRay) + (fuzz * randomUnitVector());
		scattered = ray(rec.p, reflectedRay);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}


private:
	color albedo;
	double fuzz;
	
};

class dielectric : public material {
public:
	dielectric(double refractiveIndex): refractiveIndex(refractiveIndex) {}

	bool scatter(const ray& incRay, const hit_record& rec, color& attenuation, ray& scattered) const override {
		attenuation = color(1.0, 1.0, 1.0);
		double refIndex = rec.front_face ? (1.0 / refractiveIndex) : refractiveIndex;
		vec3 unitDirection = unit_vector(incRay.direction());
		vec3 refracted = refract(unitDirection, rec.normal, refIndex);
		scattered = ray(rec.p, refracted);
		return true;
	}


private:
	double refractiveIndex;
};




#endif // !MATERIAL_H
