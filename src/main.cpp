#include "commonConstants.h"
#include "camera.h"
#include "hittableObject.h"
#include "hittableList.h"
#include "material.h"

#include "sphere.h"

int main() {
	hittable_list world;

	auto material_ground = std::make_shared<lambertian>(color(0.4, 0.1, 0.1));
	auto material_sphere1 = std::make_shared<lambertian>(color(0.0, 0.4, 0.5));
	auto material_metalSphere = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.1);


	world.add(std::make_shared<sphere>(point3(-0.5, 0, -1), 0.5, material_sphere1));
	world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
	world.add(std::make_shared<sphere>(point3(1.0, 1.0, -3.0), 1.0, material_metalSphere));
	
	Camera camera;
	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 1920;
	camera.samples_per_pixel = 100;
	camera.maxDepth = 20;

	camera.render(world);

	return 0;
}