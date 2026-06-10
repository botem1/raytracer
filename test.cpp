#include <iostream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

int main(){
	vec3 o(1, 2, 3);
	vec3 d(1, 1, 1);
	ray r(o, d);
	std::cout << r.at(1);
	return 0;
}