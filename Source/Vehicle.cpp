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
	float accelerationConstant = 1;
	float maxVelocity = 3;
	//float accelerationFriction = 0.1;
	Vector3 front,movementDir;
	front = Vector3(sin(Math::DegreeToRadian(object->getAngle().y)), 0, -cos(Math::DegreeToRadian(object->getAngle().y))).Normalize();
	if (velocity != Vector3(0, 0, 0))
		movementDir = velocity.Normalize();
	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = false;
	keyPress[4] = true;
	acceleration.SetZero();


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
		if (keyPress[A_KEY])
		{
			object->addRotation(60 * dt, 'y');
		}
		if (keyPress[D_KEY])
		{
			object->addRotation(-60 * dt, 'y');
		}
		front = Vector3(sin(Math::DegreeToRadian(-object->getAngle().y)), 0, -cos(Math::DegreeToRadian(-object->getAngle().y))).Normalize();
		if (velocity != Vector3(0, 0, 0))
			movementDir = velocity.Normalize();

		if ((velocity - (movementDir * 0.7 * accelerationConstant)).Length() < 0.1f)
		{
			velocity.SetZero();
		}
		else
			acceleration -= (movementDir * 0.7 * accelerationConstant);
		if (velocity.Length() <= maxVelocity)
		{

			if (keyPress[W_KEY])
			{
				if ((front - movementDir).Length() > 0.5)
					acceleration += front * 2 * accelerationConstant;
				else
				{
					acceleration += front * accelerationConstant;
				}
			}
			if (keyPress[S_KEY])
			{
				if ((-front - movementDir).Length() > 0.5)
					acceleration -= front * 2 * accelerationConstant;
				else
				{
					acceleration -= front * accelerationConstant;
				}
			}
		}


	velocity += acceleration;
	object->setTranslation(object->getTranslation().x + velocity.x, object->getTranslation().y + velocity.y, object->getTranslation().z + velocity.z);
}