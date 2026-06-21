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
	int samplesPerPixel;
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

	vec3 sample_offset() const {
		return vec3(
			random_double(0.0, 0.5),
			random_double(0.0, 0.5),
			0
		) - vec3(0.5, 0.5, 0);
	}

public:

	camera(int _imageWidth, double _aspectRatio, int _samplesPerPixel)
	:	imageWidth{_imageWidth},
		aspectRatio{_aspectRatio},
		samplesPerPixel{_samplesPerPixel}
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
				vec3 pixel_color(0, 0, 0);
				for(int sample = 0;sample < samplesPerPixel;++sample){
					ray sampleRay = get_ray(i, j);
					pixel_color += ray_color(sampleRay, world);
				}

				pixel_color /= (double)samplesPerPixel;
				write_color(std::cout, pixel_color);
				std::cout << "\n";
			}
		}
	}

	ray get_ray(int i, int j) const {
		vec3 offset = sample_offset();
		vec3 pixelSample = pixel00Location
							+ ((i + offset.x()) * pixelDeltaV)
							+ ((j + offset.y()) * pixelDeltaU);

		point3 rayOrigin = center;
		vec3 rayDirection = pixelSample - center;

		return ray(rayOrigin, rayDirection);
	}
};

#endif