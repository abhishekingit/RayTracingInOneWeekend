#include "color.h"
#include "vec3.h"
#include "ray.h"
#include <cmath>
#include <iostream>

double hitSphere(const point3& center, double radius, const ray& r) {
	vec3 centerVec = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = dot(-2 * r.direction(), centerVec);
	auto c = dot(centerVec, centerVec) - radius * radius;
	auto SphereEqDiscriminant = b * b - 4 * a * c;
	
	if (SphereEqDiscriminant < 0) {
		return -1.0;
	}
	else {
		return(-b - std::sqrt(SphereEqDiscriminant)) / (2.0 * a);
	}

}

color rayColor(const ray& r) {
	auto t = hitSphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		vec3 NormalV = unit_vector(r.aT(t) - point3(0, 0, -1));
		return 0.5 * color(NormalV.x() + 1, NormalV.y() + 1, NormalV.z() + 1);
	}


	auto unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(0.0, 1.0, 0.0) + a * color(0.5, 0.0, 1.0);
}

int main() {
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height);
	auto camera_center = point3(0, 0, 0);

	auto viewportU = vec3(viewport_width, 0, 0);
	auto viewportV = vec3(0, -viewport_height, 0);

	auto pixelDeltaU = viewportU / image_width;
	auto pixelDeltaV = viewportV / image_height;

	auto viewporUpperLeft = camera_center - vec3(0, 0, focal_length) - viewportU / 2 - viewportV / 2;
	auto pixel00_loc = viewporUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);


	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	
	for (int j = 0; j < image_height; j++) {
		for (int i = 0; i < image_width; i++) {
			auto pixelCenter = pixel00_loc + (i * pixelDeltaU) + (j * pixelDeltaV);
			auto rayDirection = pixelCenter - camera_center;
			ray r1(camera_center, rayDirection);
			color pixelColor = rayColor(r1);


			write_color(std::cout, pixelColor);
		}
	}

}