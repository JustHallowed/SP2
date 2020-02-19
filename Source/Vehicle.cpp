#include "Vehicle.h"

Vehicle::Vehicle()
{
	acceleration.SetZero();
	velocity.SetZero();
}
Vector3 Vehicle::getVelocity()
{
	return velocity;
}
Vector3 Vehicle::getAcceleration()
{
	return acceleration;
}

void Vehicle::setVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}
void Vehicle::setAcceleration(Vector3 acceleration)
{
	this->acceleration = acceleration;
}
void Vehicle::updateVehicle(double dt)
{
	Vector3 accelerationFriction;
	accelerationFriction.SetZero();
	float componentX = cos(Math::DegreeToRadian(angle.y));
	float componentZ = -sin(Math::DegreeToRadian(angle.y));

	if (velocity.Length() != 0)
	{
		if (velocity.x > 0)
			accelerationFriction.x = -0.5 * componentX;
		else
		{
			accelerationFriction.x = 0.5 * componentX;
		}
		if (velocity.z > 0)
			accelerationFriction.z = -0.5 * componentZ;
		else
		{
			accelerationFriction.z = 0.5 * componentZ;
		}
	}
	if (Application::IsKeyPressed('W'))
	{
		acceleration += (componentX,0, componentZ);
	}

	acceleration += accelerationFriction;
	velocity += acceleration;
}