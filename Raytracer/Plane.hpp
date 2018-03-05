#pragma once

#include "Shape.hpp"
#include "Utils.hpp"

class Plane : public Shape {
public:
	Plane(Vec3 position, Vec3 normal, Vec3 colour, double diffuse, double reflection) : Shape(position, colour, diffuse, reflection, SHAPETYPE::SPlane), planeNormal(normal) {
		planeNormal.normalize();
	}

	virtual ~Plane() {}

	bool raycastSurface(Ray& ray, Vec3& intersectionPoint, Vec3& normal, double& dis) {
		double rdn = ray.position.dot(planeNormal);
		double pdn = position.dot(planeNormal);

		double diff = rdn - pdn;

		if(abs(diff) < 1e-10)
			return false;

		double dot = planeNormal.dot(ray.direction);

        dis = -diff / dot;

        intersectionPoint = ray.position + ray.direction*dis;
        normal = planeNormal -2.0 * planeNormal * (Utils::MyFSel(dot > 0, 1.0, 0.0));

		//if(dot > 0)
		//normal = -planeNormal;

        return dis > 0;

		/*double dot = planeNormal.dot(ray.direction);
		if(dot < 0){

			dis = -((ray.position).dot(planeNormal)-position.dot(planeNormal))/dot;

			if (dis < 0)
				return false;

			intersectionPoint = ray.position + ray.direction*dis;
			normal = planeNormal;

			return true;
		}*/

		//return false;
	}

public:
	Vec3 planeNormal;
};