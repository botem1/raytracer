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

	bool hit(const ray& r, double tMin, double tMax, hit_record& rec) const override {
		double a = dot(r.direction(), r.direction());
		double h = dot(r.direction(), center - r.origin());
		double b = -2 * dot(r.direction(), center - r.origin());
		double c = dot(center - r.origin(), center - r.origin()) - radius * radius;

		// d = 1/4 * D
		double d = h * h - a * c;
		double D = b * b - 4 * a * c;

		if(D < 0.0) return false;

		double t = (-b - sqrt(d)) / a / 2;
		std::cerr << "t1 = " << t << "\n";
		if(t <= tMin || t >= tMax){
			t = (-b + sqrt(d)) / a / 2;
			std::cerr << "t2 = " << t << "\n";
			if(t <= tMin || t >= tMax){
				return false;
			}
			return false;
		}

		rec.t = t;
		rec.p = r.at(t);
		rec.normal = unitVector(rec.p - center);
		// std::cerr << "rec.p = " << rec.p << "\n";
		// std::cerr << "rec.p - center = " << rec.p - center << "\n";
		// std::cerr << "(rec.p - center).length() = " << (rec.p - center).length() << "\n";
		// std::cerr << "unitVector: " << unitVector(rec.p - center) << "\n";
		// std::cerr << "/radius: " << (rec.p - center) / radius << "\n";

		return true;
	}
};

#endif