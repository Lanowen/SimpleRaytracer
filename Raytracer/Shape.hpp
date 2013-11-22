#pragma once

#include "Ray.hpp"

class Shape {
public:
	virtual bool raycastSurface(Ray& ray, Vec3& intersectionPoint, Vec3& normal, double& dis) = 0;

	virtual ~Shape() {}

protected:
	Shape(Vec3 position, Vec3 colour, double diffuse, double reflection): position(position), colour(colour), diffuse(diffuse), reflection(reflection) {/*memcpy(this->colour,colour, sizeof(float)*3);*/ specular = 1-diffuse;}

public:

	Vec3 position, colour;
	double specular, diffuse, reflection;
};