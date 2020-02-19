#pragma once
#include "Object.h"
#include "Application.h"
#include "Camera.h"

class Vehicle
{
	Object* object;
	Vector3 acceleration;
	Vector3 velocity;
public:
	Vehicle();
	

	Vector3 getVelocity();
	Vector3 getAcceleration();

	void setObject(Object* object);
	void setVelocity(Vector3 velocity);
	void setAcceleration(Vector3 acceleration);
	void update(double dt);
};

