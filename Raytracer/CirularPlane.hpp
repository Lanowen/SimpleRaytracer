#pragma once

#include "Plane.hpp"

class CircularPlane : public Plane {
public:
	CircularPlane(Vec3 position, Vec3 normal, double radius, Vec3 colour, double diffuse, double reflection) : Plane(position, normal, colour, diffuse, reflection), radius(radius), radiusSq(radius*radius) {
	}

	virtual ~CircularPlane() {}

	virtual bool raycastSurface(Ray& ray, Vec3& intersectionPoint, Vec3& normal, double& dis) {
		/*if(Plane::raycastSurface(ray, intersectionPoint, normal, dis)){
			if((intersectionPoint-position).magnitudeSquared() <= radiusSq)
				return true;
		}
        return false;*/
        Plane::raycastSurface(ray, intersectionPoint, normal, dis);
		return (intersectionPoint - position).magnitudeSquared() <= radiusSq;
	}

public:
	double radius;
	double radiusSq;
};