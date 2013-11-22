#pragma once

#include "Vec3.hpp"

class Light {
public:
	Light(Vec3 position, double intensity, Vec3 colour): position(position), intensity(intensity), colour(colour) {}

	virtual ~Light(){}


	double intensity;
	Vec3 position, colour;
};
