#include "commonConstants.h"
#include "camera.h"
#include "hittableObject.h"
#include "hittableList.h"


#include "sphere.h"

int main() {
	hittable_list world;
	world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));
	
	Camera camera;
	camera.aspect_ratio = 16.0 / 9.0;
	camera.image_width = 400;
	camera.samples_per_pixel = 100;

	camera.render(world);

	return 0;
}