#ifndef VEC3_H
#define VEC3_H

class vec3 {
public:
	double e[3];

	vec3()
		: e{0, 0, 0} {}

	vec3(double e0, double e1, double e2)
		: e{e0, e1, e2} {}

	double x() const {
		return e[0];
	}

	double y() const {
		return e[1];
	}

	double z() const {
		return e[2];
	}

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

	double& operator[](int x) { return e[x]; }

	vec3& operator+= (const vec3& other) {
		e[0] += other.e[0];
		e[1] += other.e[1];
		e[2] += other.e[2];
		return *this;
	}

	vec3& operator*= (double x) {
		e[0] *= x;
		e[1] *= x;
		e[2] *= x;
		return *this;
	}

	vec3& operator/= (double x) {
		return *this *= 1 / x;
	}

	static vec3 random() {
		return vec3(randomDouble(), randomDouble(), randomDouble());
	}

	static vec3 random(double min, double max) {
		return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}

	double magnitude() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

};

using point3 = vec3;


inline std::ostream& operator<< (std::ostream& stream, const vec3& x) {
	return std::cout << x.e[0] << ' ' << x.e[1] << ' ' << x.e[2];
}

inline vec3 operator+ (const vec3& first, const vec3& other) {
	return vec3(first.e[0] + other.e[0], first.e[1] + other.e[1], first.e[2] + other.e[2]);
}

inline vec3 operator- (const vec3& first, const vec3& other) {
	return vec3(first.e[0] - other.e[0], first.e[1] - other.e[1], first.e[2] - other.e[2]);
}

inline vec3 operator* (const vec3& first, const vec3& other) {
	return vec3(first.e[0] * other.e[0], first.e[1] * other.e[1], first.e[2] * other.e[2]);
}

inline vec3 operator* (double x, const vec3& other) {
	return vec3(x * other.e[0], x * other.e[1], x * other.e[2]);
}

inline vec3 operator* (const vec3& other, double x) {
	return x * other;
}

inline vec3 operator/ (const vec3& other, double x) {
	return (1 / x) * other;
}

inline double dot(const vec3& first, const vec3& other) {
	return first.e[0] * other.e[0] + first.e[1] * other.e[1] + first.e[2] * other.e[2];
}

inline vec3 cross(const vec3& first, const vec3& other) {
	return vec3(first.e[1] * other.e[2] - first.e[2] * other.e[1],
		first.e[2] * other.e[0] - first.e[0] * other.e[2],
		first.e[0] * other.e[1] - first.e[1] * other.e[0]
		);
}

inline vec3 unit_vector(const vec3& v) {
	return v / v.magnitude();
}

inline vec3 randomUnitVector() {
	while (true) {
		auto tempVec = vec3::random(-1, 1);
		auto genVecLengthSquared = tempVec.length_squared();
		if (1e-160 < genVecLengthSquared && genVecLengthSquared <= 1) {
			return tempVec / std::sqrt(genVecLengthSquared);
		}
	}
}

inline vec3 randomVecOnHemisphere(const vec3& surfaceNormal) {
	vec3 randomVec = randomUnitVector();
	if (dot(randomVec, surfaceNormal) > 0.0) {
		return randomVec;
	}
	else {
		return -randomVec;
	}
}

#endif // !VEC3_H
