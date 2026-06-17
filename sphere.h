#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include "ray.h"

class sphere: public hittable{
private:
	double radius;
	point3 center;
public:
	sphere(point3 _center, double _radius)
	: center{_center}, radius{std::fmax(0, _radius)}
	{}

	bool hit(const ray& r, const interval rayT, hit_record& rec) const override {
		double a = dot(r.direction(), r.direction());
		double h = dot(r.direction(), center - r.origin());
		double b = -2 * dot(r.direction(), center - r.origin());
		double c = dot(center - r.origin(), center - r.origin()) - radius * radius;

		double d = h * h - a * c;
		double D = b * b - 4 * a * c;

		if(D < 0.0) return false;

		double t = (-b - sqrt(d)) / a / 2;
		if(t <= rayT.min || t >= rayT.max){
			t = (-b + sqrt(d)) / a / 2;
			if(t <= rayT.min || t >= rayT.max){
				return false;
			}
			return false;
		}

		rec.t = t;
		rec.p = r.at(t);
		
		vec3 outwardNormal = unitVector((rec.p - center));
		rec.setFaceNormal(r, outwardNormal);
		return true;
	}
};

#endif