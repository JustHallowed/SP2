#include "Vehicle.h"

Vehicle::Vehicle()
{
	object = nullptr;
	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = false;
	keyPress[4] = true;
}
Object* Vehicle::getObject()
{
	return object;
}
void Vehicle::setObject(Object* object)
{
	this->object = object;
}

void Vehicle::update(double dt)
{
	float accelerationConstant = 8;	//acceleration multiplier
	float maxVelocity = 3;	//maximum velocity vehicle can travel
	Vector3 front,movementDir;	//vehicle fromt, direction of movement
	if (object->getVelocity() != Vector3(0, 0, 0))
		movementDir = object->getVelocity().Normalized();

	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = keyPress[4] = keyPress[5] = false;
	
	object->setAcceleration(0,0,0);

		//sets keypress boolean
		if (Application::IsKeyPressed(VK_UP))
		{
			keyPress[W_KEY] = true;
		}
		if (Application::IsKeyPressed(VK_DOWN))
		{
			keyPress[S_KEY] = true;
		}
		if (Application::IsKeyPressed(VK_LEFT))
		{
			keyPress[A_KEY] = true;
		}
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			keyPress[D_KEY] = true;
		}
		if (Application::IsKeyPressed(VK_SHIFT))
		{
			keyPress[SHIFT_KEY] = true;
		}
		if (Application::IsKeyPressed(VK_SPACE))
		{
			keyPress[SPACE_KEY] = true;
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
		if ((object->getVelocity() - (movementDir * accelerationConstant * 0.2f * dt)).Length() < 0.1f)//to prevent movement caused by friction
		{
			object->setVelocity(0, 0, 0);
		}
		else
			if (object->getVelocity().Length() != 0)
				object->setAcceleration(object->getAcceleration() - (movementDir * accelerationConstant * 0.5f * dt));

		if (object->getVelocity().Length() <= maxVelocity)
		{
			if (keyPress[W_KEY])//accelerate front
			{
				if ((front - movementDir).Length() > 0.5)
					object->setAcceleration(object->getAcceleration() + (front * accelerationConstant * 2 * dt));
				else
				{
					object->setAcceleration(object->getAcceleration() + (front * accelerationConstant * dt));
				}
			}
			if (keyPress[S_KEY])//accelerate back
			{
				if ((front - movementDir).Length() > 0.5)
					object->setAcceleration(object->getAcceleration() - (front * accelerationConstant * 2 * dt));
				else
				{
					object->setAcceleration(object->getAcceleration() - (front * accelerationConstant * dt));
				}
			}
			if (keyPress[SPACE_KEY])//accelerate UP
			{
				if ((Vector3(0, 1, 0) - movementDir).Length() > 0.5)
					object->setAcceleration(object->getAcceleration() + (Vector3(0,1,0) * accelerationConstant * 1. * dt));
				else
				{
					object->setAcceleration(object->getAcceleration() + (Vector3(0, 1, 0) * accelerationConstant * dt));
				}
			}
			if (keyPress[SHIFT_KEY])//accelerate UP
			{
				if ((Vector3(0, -1, 0) - movementDir).Length() > 0.5)
					object->setAcceleration(object->getAcceleration() + (Vector3(0, -1, 0) * accelerationConstant * 1.5 * dt));
				else
				{
					object->setAcceleration(object->getAcceleration() + (Vector3(0, -1, 0) * accelerationConstant * dt));
				}
			}
		}



		object->setVelocity(object->getVelocity() + object->getAcceleration());
}