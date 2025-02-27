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
	auto material_sphere2 = std::make_shared<lambertian>(color(0.2, 0.8, 0.3));
	auto material_glassSphere = std::make_shared<dielectric>(1.5);
	auto material_bubbleGlassSphere = std::make_shared<dielectric>(1.00 / 1.50);
	auto material_metalSphere = std::make_shared<metal>(color(0.3, 0.7, 0.4), 0.3);

	auto material_metalSphere2 = std::make_shared<metal>(color(0.3, 0.6, 0.8), 0.0);


	world.add(std::make_shared<sphere>(point3(-0.5, 0.5, -1), 0.5, material_sphere1));
	world.add(std::make_shared<sphere>(point3(-4, 0.4, 8.0), 0.5, material_sphere2));
	world.add(std::make_shared<sphere>(point3(0, -100, -1), 100, material_ground));
	world.add(std::make_shared<sphere>(point3(-2, 1, 3.0), 1.0, material_glassSphere));
	//world.add(std::make_shared<sphere>(point3(1.0, 0.7, -3.0), 0.8, material_bubbleGlassSphere));
	world.add(std::make_shared<sphere>(point3(1.1, 0.3, -1.2), 0.3, material_metalSphere));
	world.add(std::make_shared<sphere>(point3(0.5, 0.8, 1.0), 0.8, material_metalSphere2));
	
	Camera camera;
	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 1200;
	camera.samples_per_pixel = 500;
	camera.maxDepth = 50;

	camera.vfov = 10;
	camera.lookFrom = point3(8, 5, -16);
	camera.lookAt = point3(0, 1.2, -1);
	camera.vup = point3(0, 1, 0);

	camera.render(world);

	return 0;
}