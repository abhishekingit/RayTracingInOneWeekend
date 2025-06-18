#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
	ray() {}

	ray(const point3& origin, const vec3& direction, double time): rayOrig(origin), rayDir(direction), rtime(time) {}

	ray(const point3& origin, const vec3& direction): ray(origin, direction, 0) {}

	const point3& origin() const { return rayOrig;  }
	const vec3& direction() const { return rayDir; }

	double time() const { return rtime;  }

	point3 aT(double t) const {
		return rayOrig + t * rayDir;
	}


private:
	point3 rayOrig;
	vec3 rayDir;
	double rtime;
};



#endif // !RAY_H
