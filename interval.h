#ifndef INTERVAL_H
#define INTERVAL_H

#include "raytracer.h"

class interval{
public:
	static const interval universe;
	static const interval empty;

	double min;
	double max;
public:
	interval()
	: min{infinity}, max{-infinity}
	{}

	interval(double _min, double _max)
	: min{_min}, max{_max}
	{}

	bool surrounds(double t) const { return min <= t && t <= max; }
	bool contains(double t) const { return min < t && t < max; }

	double size() { return max - min; }
};

const interval interval::universe = interval(-infinity, infinity);
const interval interval::empty = interval(infinity, -infinity);

#endif