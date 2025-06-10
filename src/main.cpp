#include "commonConstants.h"
#include "camera.h"
#include "hittableObject.h"
#include "hittableList.h"
#include "material.h"

#include "sphere.h"
#include "texture.h"

int main() {
	hittable_list world;

	//auto material_ground = std::make_shared<lambertian>(color(0.4, 0.1, 0.1));
	auto checkerGround = std::make_shared<checkeredTexture>(0.32, color(0.4, 0.1, 0.1), color(0.9, 0.9, 0.9));
	auto material_ground = std::make_shared<lambertian>(checkerGround);
	/*auto material_ground = std::make_shared<lambertian>(color(0.4, 0.1, 0.1));*/
	auto material_sphere1 = std::make_shared<lambertian>(color(0.0, 0.4, 0.5));
	auto material_sphere2 = std::make_shared<lambertian>(color(0.2, 0.8, 0.3));
	auto material_sphere3 = std::make_shared<lambertian>(color(0.6, 0.3, 0.2));
	auto material_glassSphere = std::make_shared<dielectric>(1.5);
	auto material_bubbleGlassSphere = std::make_shared<dielectric>(1.00 / 1.50);
	auto material_metalSphere = std::make_shared<metal>(color(0.3, 0.7, 0.4), 0.3);

	auto material_metalSphere2 = std::make_shared<metal>(color(0.3, 0.6, 0.8), 0.0);

	auto dispCenter1 = point3(-0.5, 0.9, -1) + vec3(0, randomDouble(0, 0.5), 0);

	auto dispCenter2 = point3(-4 + 0.9 * randomDouble(), 0.9, 8.0 + 0.9 * randomDouble()) + vec3(0, randomDouble(0, 0.5), 0);

	auto dispCenter3 = point3(-1 + 0.9 * randomDouble(), 0.9, 5.0 + 0.9 * randomDouble()) + vec3(randomDouble(0, 0.5), 0, 0);

	world.add(std::make_shared<sphere>(point3(-0.5, 0.9, -1), dispCenter1, 0.5, material_sphere1));
	world.add(std::make_shared<sphere>(point3(-4 + 0.9 * randomDouble(), 0.9, 8.0 + 0.9 * randomDouble()), dispCenter2, 0.5, material_sphere2));
	world.add(std::make_shared<sphere>(point3(-1 + 0.9 * randomDouble(), 0.9, 5.0 + 0.9 * randomDouble()), dispCenter3, 0.6, material_sphere3));
	world.add(std::make_shared<sphere>(point3(0, -1000, -1), 1000, material_ground));
	world.add(std::make_shared<sphere>(point3(-2, 1, 3.0), 1.0, material_glassSphere));
	//world.add(std::make_shared<sphere>(point3(1.0, 0.7, -3.0), 0.8, material_bubbleGlassSphere));
	world.add(std::make_shared<sphere>(point3(1.1, 0.3, -1.2), 0.3, material_metalSphere));
	world.add(std::make_shared<sphere>(point3(0.5, 0.8, 1.0), 0.8, material_metalSphere2));
	
	Camera camera;
	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 1200;
	camera.samples_per_pixel = 500;
	camera.maxDepth = 50;

	camera.vfov = 12;
	camera.lookFrom = point3(15, 7, -19);
	camera.lookAt = point3(0, 1.2, -1);
	camera.vup = point3(0, 1, 0);

	camera.render(world);

	return 0;
}