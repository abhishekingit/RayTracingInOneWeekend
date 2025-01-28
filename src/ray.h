#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
	ray() {}

	ray(const point3& origin, const vec3& direction): rayOrig(origin), rayDir(direction) {}

	const point3& origin() const { return rayOrig;  }
	const vec3& direction() const { return rayDir; }

	point3 aT(double t) const {
		return rayOrig + t * rayDir;
	}


private:
	point3 rayOrig;
	vec3 rayDir;
};



#endif // !RAY_H
