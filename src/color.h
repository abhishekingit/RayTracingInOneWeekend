#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

using color = vec3;

inline double LinearToGamma(double linearComponent) {
	if (linearComponent > 0)
		return std::sqrt(linearComponent);

	return 0;
}

void write_color(std::ostream& stream, const color& pixelColor) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	r = LinearToGamma(r);
	g = LinearToGamma(g);
	b = LinearToGamma(b);

	static const interval intensity(0.000, 0.999);


	int rByte = int(256 * intensity.clamp(r));
	int gByte = int(256 * intensity.clamp(g));
	int bByte = int(256 * intensity.clamp(b));

	stream << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif // !
