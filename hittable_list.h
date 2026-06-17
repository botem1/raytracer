#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"
#include "interval.h"

using std::shared_ptr;
using std::make_shared;

class hittable_list: public hittable{
private:
	std::vector<shared_ptr<hittable>> objects;

public:
	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }

	void add(shared_ptr<hittable> object){ objects.push_back(object); }

	bool hit(const ray& r, const interval rayT, hit_record& rec) const override {
		bool isHit = false;
		double currSmallestT = rayT.max;
		hit_record tempRec;
		for(auto object: objects){
			if(object->hit(r, interval(rayT.min, currSmallestT), tempRec)){
				isHit = true;
				rec = tempRec;
				currSmallestT = rec.t;
			}
		}

		return isHit;
	}
};

#endif HITTABLE_LIST_H