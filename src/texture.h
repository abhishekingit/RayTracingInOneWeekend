#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.h"
#include <memory>
#include <cmath>
#include <rtwstbimage.h>
#include "perlin.h"

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

class imageTexture : public texture {
public:
	imageTexture(const char* filename) : image(filename) {}

	color value(double u, double v, const point3& p) const override {
		if (image.height() <= 0) return color(0, 1, 1);
		u = interval(0, 1).clamp(u);
		v = 1.0 - interval(0, 1).clamp(v);
		auto i = int(u * image.width());
		auto j = int(v * image.height());
		auto pixel = image.pixel_data(i, j);

		auto color_scale = 1.0 / 255.0;
		return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
	}



private:
	rtw_image image;
};

class noiseTexture : public texture {
public:
	noiseTexture() {}

	color value(double u, double v, const point3& p) const override {
		return color(1, 0.4, 0.2) * noise.noise(p);
	}


private:
	perlin noise;
};


#endif // !TEXTURE_H
