#include <iostream>
#include <algorithm>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"

const double INF = 1e6;
const double TMIN = 0.0;
const double TMAX = INF;

color ray_color(const ray& r){
	sphere s(vec3(1, 0, -2), 0.7);

	hit_record rec;
	if(s.hit(r, TMIN, TMAX, rec)){
		// std::cerr << "N = " << normal << "\n";
		vec3 shadeColor = (rec.normal + vec3(1, 1, 1)) / 2;
		return shadeColor;
	}

	vec3 unitDirection = unitVector(r.direction());

	double p =  0.5 * (unitDirection.y() + 1);
	color col = (1 - p) * color(1, 1, 1) + p * color(0.5, 0.7, 1);

	return col;
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
	std::cerr << "viewport = " << viewportUpperLeft << "\n";
	point3 pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

	std::cout << "P3\n";
	std::cout << imageWidth << " " << imageHeight << "\n";
	std::cout << 256 << "\n";

	for(int i = 0;i < imageHeight;++i){
		for(int j = 0;j < imageWidth;++j){

			point3 pixelCenter = pixel00Location + (i * pixelDeltaV) + (j * pixelDeltaU);
			vec3 rayDirection = pixelCenter - cameraCenter;
			// std::cerr << "ray dir = " << rayDirection << "\n";
			ray r(pixelCenter, rayDirection);

			vec3 pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
			std::cout << "\n";
		}
	}
	return 0;
}