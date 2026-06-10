#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <cmath>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265359;

#endif RAYTRACER_H