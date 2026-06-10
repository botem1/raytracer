#include <iostream>
#include <algorithm>
#include <memory>

#include "raytracer.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"

color ray_color(const ray& r, const hittable_list& world){
	hit_record rec;
	if(world.hit(r, 0.0, infinity, rec)){
		return (rec.normal + vec3(1, 1, 1)) / 2;
	}

	vec3 unitDirection = unitVector(r.direction());
	double p =  0.5 * (unitDirection.y() + 1);

	return (1 - p) * color(1, 1, 1) + p * color(0.5, 0.7, 1);
}

int main(){

	int maxColorVal = 256;
	double aspectRatio = 16.0 / 9.0;

	int imageWidth = 1000;
	int imageHeight = std::max(1, int(imageWidth / aspectRatio));

	double viewportWidth = 2.0;
	double viewportHeight = viewportWidth / (double(imageWidth) / imageHeight);

	point3 cameraCenter = point3(0, 0, 0);
	vec3 cameraV = vec3(0, -viewportHeight, 0);
	vec3 cameraU = vec3(viewportWidth, 0, 0);
	vec3 pixelDeltaV = cameraV / imageHeight;
	vec3 pixelDeltaU = cameraU / imageWidth;

	double focalLength = 1.0;

	point3 viewportUpperLeft = cameraCenter - point3(0, 0, focalLength) - cameraV / 2 - cameraU / 2;
	point3 pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

	hittable_list world;
	world.add(make_shared<sphere>(vec3(0, 0, -3), 0.7));
	// world.add(make_shared<sphere>(vec3(0, -20, -40), 20));

	std::cout << "P3\n";
	std::cout << imageWidth << " " << imageHeight << "\n";
	std::cout << 256 << "\n";

	for(int i = 0;i < imageHeight;++i){
		for(int j = 0;j < imageWidth;++j){

			point3 pixelCenter = pixel00Location + (i * pixelDeltaV) + (j * pixelDeltaU);
			vec3 rayDirection = pixelCenter - cameraCenter;
			// std::cerr << "ray dir = " << rayDirection << "\n";
			ray r(pixelCenter, rayDirection);

			vec3 pixel_color = ray_color(r, world);
			write_color(std::cout, pixel_color);
			std::cout << "\n";
		}
	}
	return 0;
}