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
void Vehicle::setObject(Object* object)
{
	this->object = object;
}
void Vehicle::setVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}
void Vehicle::setAcceleration(Vector3 acceleration)
{
	this->acceleration = acceleration;
}
void Vehicle::update(double dt)
{
	float accelerationConstant = 1;
	float accelerationFriction = 0.1;
	Vector3 front, up,right;
	front = Vector3(sin(Math::DegreeToRadian(object->getAngle().y)), 0, -cos(Math::DegreeToRadian(object->getAngle().y))).Normalize();

	if (velocity.Length() != 0)
	{
		if (velocity.x > 0)
		{
			if ((velocity.x - acceleration.x - accelerationFriction*dt) <= 0)
			{
				velocity.x = 0;
			}
			else
				acceleration.x - accelerationFriction;
		}
		else
		{
			if ((velocity.x + acceleration.x + accelerationFriction * dt) >= 0)
			{
				velocity.x = 0;
			}
			else
				acceleration.x + accelerationFriction;
		}

		if (velocity.z > 0)
		{
			if ((velocity.z - acceleration.z - accelerationFriction * dt) <= 0)
			{
				velocity.z = 0;
			}
			else
				acceleration.z - accelerationFriction;
		}
		else
		{
			if ((velocity.z + acceleration.z + accelerationFriction * dt) >= 0)
			{
				velocity.z = 0;
			}
			else
				acceleration.z + accelerationFriction;
		}
	}
	if (Application::IsKeyPressed('W'))
	{
		acceleration += accelerationConstant * front * dt;
	}
	if (Application::IsKeyPressed('S'))
	{
		acceleration -= accelerationConstant * front * dt;
	}
	if (Application::IsKeyPressed('A'))
	{
		object->addRotation(30*dt,'y');
	}
	if (Application::IsKeyPressed('D'))
	{
		object->addRotation(-30 * dt, 'y');
	}
	velocity += acceleration;
	object->setTranslation(object->getTranslation().x + velocity.x*dt, object->getTranslation().y + velocity.y * dt, object->getTranslation().z + velocity.z * dt);
}