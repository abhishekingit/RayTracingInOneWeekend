#ifndef CAMERA_H
#define CAMERA_H

#include "hittableObject.h"
#include "material.h"

class Camera {
public:

	double aspect_ratio = 1.0;
	int image_width = 100;
	int samples_per_pixel = 10;
	int maxDepth = 10;

	double vfov = 90;
	point3 lookFrom = point3(0, 0, 0);
	point3 lookAt = point3(0, 0, -1);
	vec3 vup = point3(0, 1, 0);



	void render(const hittable_object& world) {
		initialize();

		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++) {			
			for (int i = 0; i < image_width; i++) {
				color pixelColor(0, 0, 0);
				//samples per pixel
				for (int sample = 0; sample < samples_per_pixel; sample++) {
					ray r = getRay(i, j);
					pixelColor += rayColor(r, maxDepth, world);
				}
				write_color(std::cout, pixel_samples_scale * pixelColor);
			}

		}

	}


private:
	int image_height;
	double pixel_samples_scale;
	point3 center;
	point3 pixel00_loc;
	vec3 pixelDeltaU;
	vec3 pixelDeltaV;
	vec3 u, v, w;

	void initialize() {
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		pixel_samples_scale = 1.0 / samples_per_pixel;

		center = lookFrom;

		auto focal_length = (lookFrom - lookAt).magnitude();
		auto theta = degree_to_radians(vfov);
		auto h = std::tan(theta / 2);
		auto viewport_height = 2 * h * focal_length;
		auto viewport_width = viewport_height * (double(image_width)/image_height);

		w = unit_vector(lookFrom - lookAt);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		auto viewportU = viewport_width * u;
		auto viewportV = viewport_height *  -v;

		pixelDeltaU = viewportU / image_width;
		pixelDeltaV = viewportV / image_height;

		auto viewportUpperLeft = center - (focal_length * w) - viewportU / 2 - viewportV / 2;
		pixel00_loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);


	}

	ray getRay(int i, int j) const {
		auto offset = sample_square();
		auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixelDeltaU) + ((j + offset.y()) * pixelDeltaV);
		auto rayOrigin = center;
		auto rayDir = pixel_sample - rayOrigin;
		return ray(rayOrigin, rayDir);
	}

	vec3 sample_square() const {
		return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
	}

	color rayColor(const ray& r, int maxDepth, const hittable_object& world) const {
		hit_record rec;

		if (maxDepth <= 0) {
			return color(0, 0, 0);
		}

		if (world.hit(r, interval(0.001, infinity), rec)) {
			ray scatteredRay;
			color attenuation;
			if (rec.mat->scatter(r, rec, attenuation, scatteredRay))
				return attenuation * rayColor(scatteredRay, maxDepth - 1, world);
			return color(0, 0, 0);																
		}

		auto unit_direction = unit_vector(r.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.7, 0.7, 1.0);
	}




};


#endif // !CAMERA_H
