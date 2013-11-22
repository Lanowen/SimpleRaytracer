#pragma once

#include "Shape.hpp"

class Sphere : public Shape {
public:
	Sphere(Vec3 position, double radius, Vec3 colour, double diffuse, double reflection) : Shape(position, colour, diffuse, reflection), radius(radius) {}

	virtual ~Sphere() {}

	virtual bool raycastSurface(Ray& ray, Vec3& intersectionPoint, Vec3& normal, double& dis) {
		double b, c;

		Vec3 offset = ray.position - position;
		dis = 0;

		b = ray.direction.dot(offset);
		c = offset.magnitudeSquared() - (radius*radius);

		double d = (b*b) - c;
 
		if (d > 0) { //hit
			double n1 = sqrt(d), n2 = -n1;

			n1 -= b;
			n2 -= b;

			if(n1 > 1e-10){
				if(n2 < 0){
					intersectionPoint = ray.position + ray.direction*n1;
					dis = n1;
				}
				else {
					intersectionPoint = ray.position + ray.direction*n2;
					dis = n2;
				}

				normal = intersectionPoint - position;
				normal.normalize();

				return true;
			}
		}

		return false;
	}

public:
	double radius;
};