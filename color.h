#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.h"
#include "interval.h"

using color = vec3;

const int MAX_COLOR_VAL = 256;

void write_color(std::ostream& out, const color& pixelColor){
	double r = pixelColor.x();
	double g = pixelColor.y();
	double b = pixelColor.z();

	interval intensity(0.0, 1.0);
	int ir = int(256.0 * intensity.clamp(r));
	int ig = int(256.0 * intensity.clamp(g));
	int ib = int(256.0 * intensity.clamp(b));
	out << ir << ' ' << ig << ' ' << ib;
}

#endif COLOR_H