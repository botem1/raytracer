#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
private:
	vec3 orig;
	vec3 dir;
public:
	ray() {}

	ray(const vec3& _orig, const vec3& _dir)
	: orig{_orig}, dir{_dir}
	{}

	const vec3& origin() const { return orig; }
	const vec3& direction() const { return dir; }

	vec3 at(double t) const { return orig + dir * t; }
};

#endif