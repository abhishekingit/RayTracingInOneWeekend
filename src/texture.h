#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.h"
#include <memory>
#include <cmath>

class texture {
public:
	virtual ~texture() = default;

	virtual color value(double u, double v, const point3& p) const = 0;

};

class solidColor : public texture {
public:
	solidColor(const color& albedo) : albedo(albedo) {}

	solidColor(double red, double green, double blue) : solidColor(color(red, green, blue)) {}

	color value(double u, double v, const point3& p) const override {
		return albedo;
	}



private:
	color albedo;
};


class checkeredTexture : public texture {
public:
	checkeredTexture(double scale, std::shared_ptr<texture> even, std::shared_ptr<texture> odd) : invScale(1.0 / scale), even(even), odd(odd) {}

	checkeredTexture(double scale, const color& c1, const color& c2) : checkeredTexture(scale, std::make_shared<solidColor>(c1), std::make_shared<solidColor>(c2)) {}

	color value(double u, double v, const point3& p) const override {
		auto xInt = int(floor(invScale * p.x()));
		auto yInt = int(floor(invScale * p.y()));
		auto zInt = int(floor(invScale * p.z()));

		bool isEven = (xInt + yInt + zInt) % 2 == 0;

		return isEven ? even->value(u, v, p) : odd->value(u, v, p);
	}




private:
	double invScale;
	std::shared_ptr<texture> even;
	std::shared_ptr<texture> odd;


};



#endif // !TEXTURE_H
