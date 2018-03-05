#pragma once

#include "Vec3.hpp"

class Ray {
public:
	Ray(Vec3 position, Vec3 direction) : position(position) , direction(direction) {
		this->direction.normalize();
	}

	Ray() : position() , direction() {
	}

	Ray(Vec3 position) : position(position) , direction() {
	}

	/*Ray(Ray& other) : position(other.position) , direction(other.direction) {
	}*/

    Ray(const Ray& other) : position(other.position), direction(other.direction) {
	}

    //Ray(const Ray&& other) : position(other.position), direction(other.direction) {
    //}

	double setDirection(Vec3 dir){
		direction = dir;
		return direction.normalize();
	}

	string toString(){
		return position.toString() + "~" + direction.toString();
	}

	virtual ~Ray(){}

	Vec3 direction, position;
};