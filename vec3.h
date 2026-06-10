#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3{
private:
	double c[3];

public:
	vec3()
	: c{0.0, 0.0, 0.0}
	{}

	vec3(double x, double y, double z)
	: c{x, y, z}
	{}

	double x() const { return c[0]; }
	double y() const { return c[1]; }
	double z() const { return c[2]; }

	double length_sq() const { return c[0] * c[0] + c[1] * c[1] + c[2] * c[2]; }
	double length() const { return std::sqrt(length_sq()); }

	vec3 operator-() const { return vec3(-c[0], -c[1], -c[2]); }
	double operator[](int index) const { return c[index]; }
	double& operator[](int index) { return c[index]; }

	vec3& operator+=(const vec3& other){
		c[0] += other[0];
		c[1] += other[1];
		c[2] += other[2];

		return *this;
	}

	vec3& operator-=(const vec3& other){
		*this += (-other);
		return *this;
	}

	vec3 operator*=(double n){
		c[0] *= n;
		c[1] *= n;
		c[2] *= n;
		return *this;
	}

	vec3 operator/=(double n){
		*this *= (1 / n);
		return *this;
	}
};

using point3 = vec3;

vec3 operator+(const vec3& a, const vec3& b){
	return vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

vec3 operator-(const vec3& a, const vec3& b){
	return a + (-b);
}

vec3 operator*(const vec3& a, double n){
	return vec3(a[0] * n, a[1] * n, a[2] * n);
}

vec3 operator*(double n, const vec3& a){
	return a * n;
}


vec3 operator/(const vec3& a, double n){
	return a * (1 / n);
}

vec3 operator/(double n, const vec3& a){
	return a / n;
}

double dot(const vec3& a, const vec3& b){
	return a[0] * b[0]
		+ a[1] * b[1]
		+ a[2] * b[2];
}

vec3 unitVector(const vec3& a){
	return a / a.length();
}

std::ostream& operator<<(std::ostream& out, const vec3& v){
	out << "(" << v.x() << "; " << v.y() << "; " << v.z() << ")";
	return out;
}

#endif
