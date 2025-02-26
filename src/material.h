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

		double cosTheta = std::fmin(dot(-unitDirection, rec.normal), 1.0);
		double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

		bool canInternallyReflect = refIndex * sinTheta > 1.0;
		vec3 direction;
		if (canInternallyReflect || reflectance(cosTheta, refIndex) > randomDouble()) {
			direction = reflect(unitDirection, rec.normal);
		}
		else {
			direction = refract(unitDirection, rec.normal, refIndex);
		}

		scattered = ray(rec.p, direction);
		return true;
	}


private:
	double refractiveIndex;


	static double reflectance(double cosine, double refIndex) {
		auto r0 = (1 - refIndex) / (1 + refIndex);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow((1 - cosine), 5);
	}
};




#endif // !MATERIAL_H
