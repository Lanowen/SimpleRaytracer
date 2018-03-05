#pragma once

#include "Ray.hpp"

enum SHAPETYPE
{
    SSphere,
    SPlane,
    SCone
};

class Shape {
public:
	//virtual bool raycastSurface(Ray& ray, Vec3& intersectionPoint, Vec3& normal, double& dis) = 0;

	virtual ~Shape() {}

    SHAPETYPE GetType() { return type; }

protected:
	Shape(Vec3 position, Vec3 colour, double diffuse, double reflection, SHAPETYPE type): type(type), position(position), colour(colour), diffuse(diffuse), reflection(reflection) {/*memcpy(this->colour,colour, sizeof(float)*3);*/ specular = 1-diffuse;}

    SHAPETYPE type;

public:
    
	Vec3 position, colour;
	double specular, diffuse, reflection;
};