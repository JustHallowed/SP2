#pragma once
#include "Object.h"
#include "Application.h"
class Vehicle:public Object
{
	Vector3 acceleration;
	Vector3 velocity;
public:
	Vehicle();
	

	Vector3 getVelocity();
	Vector3 getAcceleration();

	void setVelocity(Vector3 velocity);
	void setAcceleration(Vector3 acceleration);
	void updateVehicle(double dt);
};

