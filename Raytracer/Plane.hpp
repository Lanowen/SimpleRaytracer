#pragma once

#include "Shape.hpp"

class Plane : public Shape {
public:
	Plane(Vec3 position, Vec3 normal, Vec3 colour, double diffuse, double reflection) : Shape(position, colour, diffuse, reflection), planeNormal(normal) {
		planeNormal.normalize();
	}

	virtual ~Plane() {}

	virtual bool raycastSurface(Ray& ray, Vec3& intersectionPoint, Vec3& normal, double& dis) {
		if(abs(ray.position.dot(planeNormal) - position.dot(planeNormal)) < 1e-10)
			return false;

		double dot = planeNormal.dot(ray.direction);
		if(dot < 0){

			dis = -((ray.position).dot(planeNormal)-position.dot(planeNormal))/dot;

			if (dis < 0)
				return false;

			intersectionPoint = ray.position + ray.direction*dis;
			normal = planeNormal;

			return true;
		}
		else 
			if(dot > 0){
			dis = -((ray.position).dot(planeNormal)-position.dot(planeNormal))/dot;

			if (dis < 0)
				return false;

			intersectionPoint = ray.position + ray.direction*dis;
			normal = -planeNormal;

			return true;
		}
		return false;

		/*double dot = planeNormal.dot(ray.direction);
		if(dot < 0){

			dis = -((ray.position).dot(planeNormal)-position.dot(planeNormal))/dot;

			if (dis < 0)
				return false;

			intersectionPoint = ray.position + ray.direction*dis;
			normal = planeNormal;

			return true;
		}*/

		return false;
	}

public:
	Vec3 planeNormal;
};