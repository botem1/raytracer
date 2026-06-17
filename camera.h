#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"

class camera{
private:
	double aspectRatio;
	int imageWidth;
	int imageHeight;
	double viewportWidth;
	double focalLength;

	point3 center;
	point3 pixel00Location;
	vec3 pixelDeltaV;
	vec3 pixelDeltaU;

	ray get_ray() const {}

	color ray_color(const ray& r, const hittable_list& world) const {
		hit_record rec;
		if(world.hit(r, interval::universe, rec)){
			return (rec.normal + vec3(1, 1, 1)) / 2;
		}

		vec3 unitDirection = unitVector(r.direction());
		double p =  0.5 * (unitDirection.y() + 1);

		return (1 - p) * color(1, 1, 1) + p * color(0.5, 0.7, 1);
	}

public:

	camera(int _imageWidth, double _aspectRatio)
	: imageWidth{_imageWidth}, aspectRatio{_aspectRatio}
	{
		imageHeight = std::max(1, int(imageWidth / aspectRatio));

		double focalLength = 1.0;
		viewportWidth = 2.0;
		double viewportHeight = viewportWidth / (double(imageWidth) / imageHeight);

		vec3 cameraV = vec3(0, -viewportHeight, 0);
		vec3 cameraU = vec3(viewportWidth, 0, 0);
		pixelDeltaV = cameraV / imageHeight;
		pixelDeltaU = cameraU / imageWidth;

		center = point3(0, 0, 0);

		point3 viewportUpperLeft = center - point3(0, 0, focalLength) - cameraV / 2 - cameraU / 2;
		pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
	}

	void render(const hittable_list& world){
		std::cout << "P3\n";
		std::cout << imageWidth << " " << imageHeight << "\n";
		std::cout << 256 << "\n";

		for(int i = 0;i < imageHeight;++i){
			for(int j = 0;j < imageWidth;++j){

				point3 pixelCenter = pixel00Location + (i * pixelDeltaV) + (j * pixelDeltaU);
				vec3 rayDirection = pixelCenter - center;

				ray r(pixelCenter, rayDirection);

				vec3 pixel_color = ray_color(r, world);
				write_color(std::cout, pixel_color);
				std::cout << "\n";
			}
		}
	}
};

#endif