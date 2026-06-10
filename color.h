#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"

using color = vec3;

const int MAX_COLOR_VAL = 256;

void write_color(std::ostream& out, const color& pixelColor){
	double r = pixelColor.x();
	double g = pixelColor.y();
	double b = pixelColor.z();

	int ir = int(256.0 * r);
	int ig = int(256.0 * g);
	int ib = int(256.0 * b);

	out << ir << ' ' << ig << ' ' << ib;
}

#endif COLOR_H