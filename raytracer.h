#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <memory>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <random>

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265359;

double random_double() {
	static std::uniform_real_distribution<double> dis(0.0, 1.0);
	std::random_device rd;
	std::mt19937 gen(rd());
	return dis(gen);
}

double random_double(double min, double max){
	return min + (max-min) * random_double();
}

#endif RAYTRACER_H