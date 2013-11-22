#pragma once

#include "Light.hpp"
#include "Shape.hpp"

#include <vector>

typedef vector<pair<Light*, Vec3>> lightNormalPair;
typedef vector<pair<Light*, Vec3>>::iterator lightNormalPairItr;

class Scene {
public:

	typedef vector<Shape*>::iterator shapeItr;
	typedef vector<Light*>::iterator lightItr;
	
	enum colorMode {solid, normals, fullNormals, shaded};

	colorMode mode;

	Scene() : mode(shaded) {}

	virtual ~Scene(){
		for(shapeItr itr = shapes.begin(); itr != shapes.end(); itr++){
			delete *itr;
		}

		for(lightItr itr = lights.begin(); itr != lights.end(); itr++){
			delete *itr;
		}
	}

	bool raycastAll(Ray& ray, Vec3& intersectionPoint, Vec3& normal, Shape*& shape, double& distanceTravelled){
		Vec3 tempIP, tempNormal;
		double tempDis;
		distanceTravelled = DBL_MAX;
		bool retVal = false;

		shapeItr end = shapes.end();
		for(shapeItr itr = shapes.begin(); itr != end; itr++){
			if((*itr)->raycastSurface(ray, tempIP, tempNormal, tempDis)){
				if(tempDis < distanceTravelled){
					distanceTravelled = tempDis;
					intersectionPoint = tempIP;
					normal = tempNormal;
					shape = (*itr);
					retVal = true;
				}
			}
		}

		return retVal;
	}

	bool lightcastAll(Vec3& pos, Vec3& hitNormal, lightNormalPair& lightsHit){
		Ray toLight(pos);
		Vec3 intersection, normal;
		bool retVal = false;
		double distanceTravelled = 0;

		lightItr end = lights.end();
		for(lightItr itr = lights.begin(); itr != end; itr++){
			double lightDis = toLight.setDirection((*itr)->position - pos);
			if(hitNormal.dot(toLight.direction) > 0){ //quick fix for double sided planes not to darken on opposite side of light
				lightDis *= lightDis;
				Shape *nothing;

				bool raycast = raycastAll(toLight, intersection, normal, nothing, distanceTravelled);

				if(!raycast || ((intersection - pos).magnitudeSquared() > lightDis)){
					lightsHit.push_back(pair<Light*, Vec3>((*itr), toLight.direction));
					retVal = true;
				}
			}
		}

		return retVal;
	}

	void addShape(Shape* shape){
		shapes.push_back(shape);
	}

	void addLight(Light* light){
		lights.push_back(light);
	}

private:
	vector<Shape*> shapes;
	vector<Light*> lights;
};