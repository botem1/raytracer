#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "vec3.h"

class hit_record{
public:
	point3 p;
	vec3 normal;
	double t;
	bool isFrontFace;

	void setFaceNormal(const ray& r, const vec3& outwardNormal){
		// NOTE: it is assumed that outwardNormal has a unit length.
		isFrontFace = (dot(r.direction(), outwardNormal) < 0);

		if(isFrontFace) normal = outwardNormal;
		else normal = -outwardNormal;
	}
};

class hittable{
public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, double tMin, double tMax, hit_record& rec) const = 0;
};

#endif