#pragma once

#include "Shape.hpp"
#include "CirularPlane.hpp"

#define PI 3.14159265358979323846

class Cone : public Shape {
public:
	Cone(Vec3 up, double height, double baseRadius, Vec3 position, Vec3 colour, double diffuse, double reflection) : Shape(position, colour, diffuse, reflection), up(up), height(height), baseRadius(baseRadius), baseNormal(Vec3(up)), cap(Vec3(0), -up, baseRadius, colour, diffuse, reflection)  {
		this->up.normalize();

		this->position += this->up*height;
		position += this->up*height;

		cap.planeNormal = -this->up;
		cap.position = position-this->up*height;

		this->up.y*=-1;
		phi = acos(this->up.y);
		theta = atan2(-this->up.z,this->up.x);

		alpha = (baseRadius*baseRadius)/(height*height);

		double angle = atan(alpha);

		this->position.x = position.x*cos(theta)-position.z*sin(theta);
		this->position.z = position.x*sin(theta)+position.z*cos(theta);

		this->position.y = position.y*cos(phi)-this->position.x*sin(phi);
		this->position.x = position.y*sin(phi)+this->position.x*cos(phi);
	}

	virtual ~Cone() {}

	Ray transformRay(const Ray& ray){
		Ray newRay = ray;

		newRay.direction.x = ray.direction.x*cos(theta)-ray.direction.z*sin(theta);
		newRay.direction.z = ray.direction.x*sin(theta)+ray.direction.z*cos(theta);	

		newRay.position.x = ray.position.x*cos(theta)-ray.position.z*sin(theta);
		newRay.position.z = ray.position.x*sin(theta)+ray.position.z*cos(theta);

		double tempY = newRay.direction.y;

		newRay.direction.y = tempY*cos(phi)-newRay.direction.x*sin(phi);
		newRay.direction.x = tempY*sin(phi)+newRay.direction.x*cos(phi);

		tempY = newRay.position.y;

		newRay.position.y = tempY*cos(phi)-newRay.position.x*sin(phi);
		newRay.position.x = tempY*sin(phi)+newRay.position.x*cos(phi);		

		return newRay;
	}

	virtual bool raycastSurface(Ray& ray, Vec3& intersectionPoint, Vec3& normal, double& dis) {
		double a, b, c;
		dis = 0;

		Ray transformedRay = transformRay(ray);

		Vec3 offset = transformedRay.position - position;

		a = transformedRay.direction.magnitudeSquared() - transformedRay.direction.y*transformedRay.direction.y*(alpha+1);
		b = 2*(offset.dot(transformedRay.direction) - offset.y*transformedRay.direction.y*(alpha+1));
		c = offset.dot(offset) - offset.y*offset.y*(alpha+1);

		double d = (b*b) -4*a*c;
 
		if (d > 0) { //hit
			double n1 = sqrt(d)/(2*a), n2 = -n1;
			b/=2*a;

			n1 -= b;
			n2 -= b;

			if(n1 > 1e-10){
				intersectionPoint = ray.position + ray.direction*n2;
				//double yPos = transformedRay.position.y + transformedRay.direction.y*n2 + originalPosition.dot(up);

				Vec3 tP;

				if(n2 < 0){
					intersectionPoint = ray.position + ray.direction*n1;
					//yPos = transformedRay.position.y + transformedRay.direction.y*n1 + originalPosition.dot(up);
					tP = transformedRay.position + transformedRay.direction*n1;
					dis = n1;
				}
				else {
					intersectionPoint = ray.position + ray.direction*n2;
					//yPos = transformedRay.position.y + transformedRay.direction.y*n2 + originalPosition.dot(up);
					tP = transformedRay.position + transformedRay.direction*n2;
					dis = n2;
				}

				tP -= position;

				if(tP.y < 0 || tP.y > height){
					return cap.raycastSurface(ray,intersectionPoint, normal, dis);
				}

				normal = Vec3(2*tP.x, 2*tP.y*alpha*alpha, 2*tP.z);

				double a, b;

				a = normal.x;
				b = normal.y;

				normal.x = a*cos(-phi)-b*sin(-phi);
				normal.y = a*sin(-phi)+b*cos(-phi);	

				a = normal.x;
				b = normal.z;

				normal.x = a*cos(-theta)-b*sin(-theta);
				normal.z = a*sin(-theta)+b*cos(-theta);	

				normal.y *=-1;

				normal.normalize();								

				return true;
			}
		}

		return false;
	}
	
	double phi, theta, alpha;
	double height, baseRadius;
	Vec3 baseNormal;
	Vec3 up;
	CircularPlane cap;
};