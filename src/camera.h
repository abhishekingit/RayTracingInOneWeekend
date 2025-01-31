#ifndef CAMERA_H
#define CAMERA_H

#include "hittableObject.h"

class Camera {
public:

	double aspect_ratio = 1.0;
	int image_width = 100;


	void render(const hittable_object& world) {
		initialize();

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++) {
			for (int i = 0; i < image_width; i++) {
				auto pixelCenter = pixel00_loc + (i * pixelDeltaU) + (j * pixelDeltaV);
				auto rayDirection = pixelCenter - center;
				ray r1(center, rayDirection);
				color pixelColor = rayColor(r1, world);
				write_color(std::cout, pixelColor);
			}

		}

	}


private:
	int image_height;
	point3 center;
	point3 pixel00_loc;
	vec3 pixelDeltaU;
	vec3 pixelDeltaV;

	void initialize() {
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		center = point3(0, 0, 0);

		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (double(image_width)/image_height);

		auto viewportU = vec3(viewport_width, 0, 0);
		auto viewportV = vec3(0, -viewport_height, 0);

		pixelDeltaU = viewportU / image_width;
		pixelDeltaV = viewportV / image_height;

		auto viewportUpperLeft = center - vec3(0, 0, focal_length) - viewportU/2 - viewportV/2;
		pixel00_loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);


	}

	color rayColor(const ray& r, const hittable_object& world) const {
		hit_record rec;
		if (world.hit(r, interval(0, infinity), rec)) {
			return 0.5 * (rec.normal + color(1, 1, 1));
		}

		auto unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}




};


#endif // !CAMERA_H
