#include "Vehicle.h"

Vehicle::Vehicle()
{
	object = nullptr;
	acceleration.SetZero();
	velocity.SetZero();
	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = false;
	keyPress[4] = true;
}
Vector3 Vehicle::getVelocity()
{
	return velocity;
}
Vector3 Vehicle::getAcceleration()
{
	return acceleration;
}
Object* Vehicle::getObject()
{
	return object;
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
	float accelerationConstant = 8;	//acceleration multiplier
	float maxVelocity = 3;	//maximum velocity vehicle can travel
	Vector3 front,movementDir;	//vehicle fromt, direction of movement
	if (velocity != Vector3(0, 0, 0))
		movementDir = velocity.Normalized();

	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = false;
	keyPress[4] = true;
	acceleration.SetZero();

		//sets keypress boolean
		if (Application::IsKeyPressed('W'))
		{
			keyPress[W_KEY] = true;
			keyPress[NO_KEY] = false;

		}
		if (Application::IsKeyPressed('S'))
		{
			keyPress[S_KEY] = true;
			keyPress[NO_KEY] = false;

		}
		if (Application::IsKeyPressed('A'))
		{
			keyPress[A_KEY] = true;
			keyPress[NO_KEY] = false;

		}
		if (Application::IsKeyPressed('D'))
		{
			keyPress[D_KEY] = true;
			keyPress[NO_KEY] = false;

		}
		if (keyPress[A_KEY])//turn left
		{
			object->addRotation(80 * dt, 'y');
		}
		if (keyPress[D_KEY])//turn right
		{
			object->addRotation(-80 * dt, 'y');
		}

		front = Vector3(sin(Math::DegreeToRadian(-object->getAngle().y)), 0, -cos(Math::DegreeToRadian(-object->getAngle().y))).Normalized();

		//friction
		if ((velocity - (movementDir * accelerationConstant * 0.2f * dt)).Length() < 0.1f)//to prevent movement caused by friction
		{
			velocity.SetZero();
		}
		else
			if (velocity.Length() != 0)
				acceleration -= (movementDir * accelerationConstant * 0.5f) * dt;

		if (velocity.Length() <= maxVelocity)
		{
			if (keyPress[W_KEY])//accelerate front
			{
				if ((front - movementDir).Length() > 0.5)
					acceleration += front * 2 * accelerationConstant * dt;
				else
				{
					acceleration += front * accelerationConstant * dt;
				}
			}
			if (keyPress[S_KEY])//accelerate back
			{
				if ((-front - movementDir).Length() > 0.5)
					acceleration -= front * 2 * accelerationConstant * dt;
				else
				{
					acceleration -= front * accelerationConstant*dt;
				}
			}
		}



	velocity += acceleration;
	object->setTranslation(object->getTranslation().x + velocity.x, object->getTranslation().y + velocity.y, object->getTranslation().z + velocity.z);
}