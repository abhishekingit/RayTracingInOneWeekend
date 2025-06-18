#ifndef PERLIN_H
#define PERLIN_H

#include "commonConstants.h"

class perlin {
public:
	perlin() {
		for (int i = 0; i < pointCount; i++) {
			randfloat[i] = randomDouble();
		}

		perlin_generate_perm(perm_X);
		perlin_generate_perm(perm_Y);
		perlin_generate_perm(perm_Z);
	}

	double noise(const point3& p) const {
		auto i = int(8 * p.x()) & 255;
		auto j = int(8 * p.y()) & 255;
		auto k = int(8 * p.z()) & 255;

		return randfloat[perm_X[i] ^ perm_Y[j] ^ perm_Z[k]];
	}


private:
	static const int pointCount = 256;
	double randfloat[pointCount];
	int perm_X[pointCount];
	int perm_Y[pointCount];
	int perm_Z[pointCount];

	static void perlin_generate_perm(int* p) {
		for (int i = 0; i < pointCount; i++)
			p[i] = i;

		permute(p, pointCount);
	}


	static void permute(int* p, int n) {
		for (int i = n - 1; i > 0; i--) {
			int target = randomInt(0, i);
			int tmp = p[i];
			p[i] = p[target];
			p[target] = tmp;
		}
	}


};



#endif // !PERLIN_H
