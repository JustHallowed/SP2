#include "Vehicle.h"

Vehicle::Vehicle()
{
	object = nullptr;
	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = keyPress[4] = keyPress[5] = keyPressed = false;
	disabledKey[0] = disabledKey[1] = disabledKey[2] = disabledKey[3] = disabledKey[4] = disabledKey[5] = false;
	isRotationMode = animation = true;
	keyCode[FRONT_KEY] = VK_UP;
	keyCode[LEFT_KEY] = VK_LEFT;
	keyCode[BACK_KEY] = VK_DOWN;
	keyCode[RIGHT_KEY] = VK_RIGHT;
	keyCode[UP_KEY] = VK_SPACE;
	keyCode[DOWN_KEY] = VK_SHIFT;
}

Object* Vehicle::getObject() const
{
	return object;
}
void Vehicle::setObject(Object* object, bool isRotationMode)
{
	this->object = object;
	this->isRotationMode = isRotationMode;
}
void Vehicle::disableKey(int keyCode)
{
	disabledKey[keyCode] = true;
}
void Vehicle::disableAnimation(bool animation)
{
	this->animation = !animation;
}
void Vehicle::setKeys(int FRONT, int LEFT, int BACK, int RIGHT, int UP, int DOWN)
{
	keyCode[FRONT_KEY] = FRONT;
	keyCode[LEFT_KEY] = LEFT;
	keyCode[BACK_KEY] = BACK;
	keyCode[RIGHT_KEY] = RIGHT;
	keyCode[UP_KEY] = UP;
	keyCode[DOWN_KEY] = DOWN;
}
void Vehicle::update(double dt)
{
	float accelerationConstant = 4;	//acceleration multiplier
	float maxVelocity = 2;	//maximum velocity vehicle can travel
	Vector3 front, right, movementDir;	//vehicle fromt, direction of movement
	if (object->getVelocity() != Vector3(0, 0, 0))
		movementDir = object->getVelocity().Normalized();

	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = keyPress[4] = keyPress[5] = false;
	object->setAcceleration(0, 0, 0);

	int count;
	const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

	//sets keypress boolean
	if(Application::IsKeyPressed(keyCode[FRONT_KEY])){
		keyPress[FRONT_KEY] = true;
	}
	if (Application::IsKeyPressed(keyCode[BACK_KEY]))
	{
		keyPress[BACK_KEY] = true;
	}
	if(Application::IsKeyPressed(keyCode[LEFT_KEY]) ||
		(this->keyCode[LEFT_KEY] == VK_LEFT && -(axes != 0 && axes[0] == int(axes[0]) ? axes[0] : 0) > 0) ||
		(this->keyCode[LEFT_KEY] == 'A' && -(axes != 0 && axes[2] == int(axes[2]) ? axes[2] : 0) > 0)){
		keyPress[LEFT_KEY] = true;
	}
	if(Application::IsKeyPressed(keyCode[RIGHT_KEY]) ||
		(this->keyCode[RIGHT_KEY] == VK_RIGHT && -(axes != 0 && axes[0] == int(axes[0]) ? axes[0] : 0) < 0) ||
		(this->keyCode[RIGHT_KEY] == 'D' && -(axes != 0 && axes[2] == int(axes[2]) ? axes[2] : 0) < 0)){
		keyPress[RIGHT_KEY] = true;
	}
	if(Application::IsKeyPressed(keyCode[DOWN_KEY]) ||
		(this->keyCode[DOWN_KEY] == VK_DOWN && -(axes != 0 && axes[3] == int(axes[3]) ? axes[3] : 0) < 0) ||
		(this->keyCode[DOWN_KEY] == 'S' && -(axes != 0 && axes[1] == int(axes[1]) ? axes[1] : 0) < 0)){
		keyPress[DOWN_KEY] = true;
	}
	if(Application::IsKeyPressed(keyCode[UP_KEY]) ||
		(this->keyCode[UP_KEY] == VK_UP && -(axes != 0 && axes[3] == int(axes[3]) ? axes[3] : 0) > 0) ||
		(this->keyCode[UP_KEY] == 'W' && -(axes != 0 && axes[1] == int(axes[1]) ? axes[1] : 0) > 0)){
		keyPress[UP_KEY] = true;
	}

	if (isRotationMode)
	{
		if (keyPress[LEFT_KEY] && !disabledKey[LEFT_KEY])//turn left
		{
			object->addRotation(80 * dt, 'y');
		}
		if (keyPress[RIGHT_KEY] && !disabledKey[RIGHT_KEY])//turn right
		{
			object->addRotation(-80 * dt, 'y');
		}
	}

	front = Vector3(sin(Math::DegreeToRadian(object->getAngle().y)), 0, cos(Math::DegreeToRadian(-object->getAngle().y))).Normalized();
	right = front.Cross(Vector3(0, 1, 0));
	//friction
	//if (!keyPressed) //if no movement key is pressed in the previous frame
	//{
	//	//to prevent movement caused by friction
	//	Vector3 friction = (movementDir * accelerationConstant * 0.5f * dt);
	//	if (abs(object->getVelocity().x - friction.x) < abs(friction.x) ||
	//		abs(object->getVelocity().y - friction.y) < abs(friction.y) ||
	//		abs(object->getVelocity().z - friction.z) < abs(friction.z))
	//	{
	//	object->setVelocity(0, 0, 0);
	//	movementDir.SetZero();
	//	}
	//}
	if (object->getVelocity().Length() != 0)
		object->setAcceleration(object->getAcceleration() - (object->getVelocity().Length() / maxVelocity) * (movementDir * accelerationConstant * 2));


	keyPressed = false;
	if (keyPress[FRONT_KEY] && !disabledKey[FRONT_KEY])//accelerate front
	{
		object->setAcceleration(object->getAcceleration() + (front * accelerationConstant * 2));
		keyPressed = true;
	}

	if (!isRotationMode)
	{
		if (keyPress[LEFT_KEY] && !disabledKey[LEFT_KEY])//accelerate left
		{
			object->setAcceleration(object->getAcceleration() + (-right * accelerationConstant * 2));
			keyPressed = true;

			if (animation && object->getAngle().z > -10)
			{
				object->addRotation(-object->getVelocity().x / 2, 'z');
			}
		}
		if (!keyPress[LEFT_KEY])
		{
			if (object->getAngle().z < 0)
			{
				object->addRotation(1, 'z');
			}
		}
		if (keyPress[RIGHT_KEY] && !disabledKey[RIGHT_KEY])//accelerate right
		{
			object->setAcceleration(object->getAcceleration() + (right * accelerationConstant * 2));
			keyPressed = true;

			if (animation && object->getAngle().z < 10)
			{
				object->addRotation(-object->getVelocity().x / 2, 'z');
			}
		}
		if (!keyPress[RIGHT_KEY])
		{
			if (object->getAngle().z > 0)
			{
				object->addRotation(-1, 'z');
			}
		}

		if (keyPress[BACK_KEY] && !disabledKey[BACK_KEY]) //accelerate back
		{
			object->setAcceleration(object->getAcceleration() - (front * accelerationConstant * 2));
			keyPressed = true;
		}
		if (keyPress[UP_KEY] && !disabledKey[UP_KEY]) //accelerate up
		{
			object->setAcceleration(object->getAcceleration() + (Vector3(0, 1, 0) * accelerationConstant * 1.5));
			keyPressed = true;
		}
		if (keyPress[DOWN_KEY] && !disabledKey[DOWN_KEY]) //accelerate down
		{
			object->setAcceleration(object->getAcceleration() + (Vector3(0, -1, 0) * accelerationConstant));
			keyPressed = true;
		}
	}
	if(object->hasGravity()&&!object->isGrounded()&&!keyPress[UP_KEY])
	object->setAcceleration(object->getAcceleration().x, object->getAcceleration().y - accelerationConstant * 5, object->getAcceleration().z);
	
	object->setVelocity(object->getVelocity() + object->getAcceleration() * dt);
}