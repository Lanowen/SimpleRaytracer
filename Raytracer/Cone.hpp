#pragma once

#include "Utils.hpp"
#include "Shape.hpp"
#include "CirularPlane.hpp"

#define PI 3.14159265358979323846

class Cone : public Shape {
public:
	Cone(Vec3 up, double height, double baseRadius, Vec3 position, Vec3 colour, double diffuse, double reflection) : Shape(position, colour, diffuse, reflection, SHAPETYPE::SCone), /*up(up),*/ height(height), /*baseRadius(baseRadius), baseNormal(Vec3(up)),*/ cap(Vec3(0), -up, baseRadius, colour, diffuse, reflection)  {
		up.normalize();

		this->position += up*height;
		position += up*height;

		cap.planeNormal = -up;
		cap.position = position-up*height;

		up.y*=-1;
		double phi = acos(up.y);
        double theta = atan2(-up.z,up.x);

		alpha = (baseRadius*baseRadius)/(height*height);

		//angle = atan(alpha);
		cosTheta = cos(theta);
		sinTheta = sin(theta);
		cosPhi = cos(phi);
		sinPhi = sin(phi);

		this->position.x = position.x*cosTheta -position.z*sinTheta;
		this->position.z = position.x*sinTheta +position.z*cosTheta;

		this->position.y = position.y*cosPhi -this->position.x*sinPhi;
		this->position.x = position.y*sinPhi +this->position.x*cosPhi;
	}

	virtual ~Cone() {}

	Ray transformRay(const Ray& ray){
		Ray newRay = ray;

		newRay.direction.x = ray.direction.x*cosTheta-ray.direction.z*sinTheta;
		newRay.direction.z = ray.direction.x*sinTheta +ray.direction.z*cosTheta;

		newRay.position.x = ray.position.x*cosTheta -ray.position.z*sinTheta;
		newRay.position.z = ray.position.x*sinTheta +ray.position.z*cosTheta;

		double tempY = newRay.direction.y;

		newRay.direction.y = tempY*cosPhi -newRay.direction.x*sinPhi;
		newRay.direction.x = tempY*sinPhi +newRay.direction.x*cosPhi;

		tempY = newRay.position.y;

		newRay.position.y = tempY*cosPhi -newRay.position.x*sinPhi;
		newRay.position.x = tempY*sinPhi +newRay.position.x*cosPhi;

		return newRay;
	}

	bool raycastSurface(Ray& ray, Vec3& intersectionPoint, Vec3& normal, double& dis) {
		double a, b, c;
		dis = 0;

		Ray transformedRay = std::move(transformRay(ray));

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
				//intersectionPoint = ray.position + ray.direction*n2;
				//double yPos = transformedRay.position.y + transformedRay.direction.y*n2 + originalPosition.dot(up);

				Vec3 tP;

                //float maxn = Utils::minss(n1, n2);

                //intersectionPoint = ray.position + ray.direction*maxn;
                //tP = transformedRay.position + transformedRay.direction*maxn;
                //dis = maxn;

				if(n2 < 0){
                    double n = Utils::MyFSel(n2 < 0, n1, n2);
					intersectionPoint = std::move(ray.position + ray.direction*n1);
					//yPos = transformedRay.position.y + transformedRay.direction.y*n1 + originalPosition.dot(up);
					tP = transformedRay.position + transformedRay.direction*n1;
					dis = n1;
				}
				else {
                    double n = Utils::MyFSel(n2 < 0, n1, n2);
					intersectionPoint = std::move(ray.position + ray.direction*n2);
					//yPos = transformedRay.position.y + transformedRay.direction.y*n2 + originalPosition.dot(up);
					tP = transformedRay.position + transformedRay.direction*n2;
					dis = n2;
				}

				tP -= position;

				if(tP.y < 0 || tP.y > height){
					return cap.raycastSurface(ray,intersectionPoint, normal, dis);
				}

				normal = std::move(Vec3(2*tP.x, 2*tP.y*alpha*alpha, 2*tP.z));

				double a, b;

				a = normal.x;
				b = normal.y;

				normal.x = a*cosPhi +b*sinPhi;
				normal.y = a*-sinPhi +b*cosPhi;

				a = normal.x;
				b = normal.z;

				normal.x = a*cosTheta +b*sinTheta;
				normal.z = a*-sinTheta +b*cosTheta;

				normal.y *=-1;

				normal.normalize();								

				return true;
			}
		}

		return false;
	}
	
	double //angle,
		cosTheta,
		sinTheta,
		cosPhi,
		sinPhi,
        alpha;
	//double phi, theta, alpha;
    double height;// , baseRadius;
	//Vec3 baseNormal;
	//Vec3 up;
	CircularPlane cap;
};