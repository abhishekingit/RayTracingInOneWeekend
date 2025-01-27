#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& stream, const color& pixelColor) {
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	int rByte = int(255.999 * r);
	int gByte = int(255.999 * g);
	int bByte = int(255.999 * b);

	stream << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif // !
