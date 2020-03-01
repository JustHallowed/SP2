#include "ObjectTypes.h"

Vehicle::Vehicle(Mesh* mesh)
{
	meshType = mesh;
	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = keyPress[4] = keyPress[5] = keyPressed = false;
	isRotationMode = disabledKey[0] = disabledKey[1] = disabledKey[2] = disabledKey[3] = disabledKey[4] = disabledKey[5] = false;
	animation = true;
	keyCode[FRONT_KEY] = VK_UP;
	keyCode[LEFT_KEY] = VK_LEFT;
	keyCode[BACK_KEY] = VK_DOWN;
	keyCode[RIGHT_KEY] = VK_RIGHT;
	keyCode[UP_KEY] = VK_SPACE;
	keyCode[DOWN_KEY] = VK_SHIFT;
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
	if (velocity != Vector3(0, 0, 0))
		movementDir = velocity.Normalized();

	keyPress[0] = keyPress[1] = keyPress[2] = keyPress[3] = keyPress[4] = keyPress[5] = false;

	setAcceleration(0, 0, 0);

	//sets keypress boolean
	if (Application::IsKeyPressed(keyCode[FRONT_KEY]))
	{
		keyPress[FRONT_KEY] = true;
	}
	if (Application::IsKeyPressed(keyCode[BACK_KEY]))
	{
		keyPress[BACK_KEY] = true;
	}
	if (Application::IsKeyPressed(keyCode[LEFT_KEY]))
	{
		keyPress[LEFT_KEY] = true;
	}
	if (Application::IsKeyPressed(keyCode[RIGHT_KEY]))
	{
		keyPress[RIGHT_KEY] = true;
	}
	if (Application::IsKeyPressed(keyCode[DOWN_KEY]))
	{
		keyPress[DOWN_KEY] = true;
	}
	if (Application::IsKeyPressed(keyCode[UP_KEY]))
	{
		keyPress[UP_KEY] = true;
	}

	if (isRotationMode)
	{
		if (keyPress[LEFT_KEY] && !disabledKey[LEFT_KEY])//turn left
		{
			addRotation(80 * dt, 'y');
		}
		if (keyPress[RIGHT_KEY] && !disabledKey[RIGHT_KEY])//turn right
		{
			addRotation(-80 * dt, 'y');
		}
	}

	front = Vector3(sin(Math::DegreeToRadian(angle.y)), 0, cos(Math::DegreeToRadian(-angle.y))).Normalized();
	right = front.Cross(Vector3(0, 1, 0));
	//friction
	//if (!keyPressed) //if no movement key is pressed in the previous frame
	//{
	//	//to prevent movement caused by friction
	//	Vector3 friction = (movementDir * accelerationConstant * 0.5f * dt);
	//	if (abs(velocity .x - friction.x) < abs(friction.x) ||
	//		abs(velocity .y - friction.y) < abs(friction.y) ||
	//		abs(velocity .z - friction.z) < abs(friction.z))
	//	{
	//	object->setVelocity(0, 0, 0);
	//	movementDir.SetZero();
	//	}
	//}
	if (velocity .Length() != 0)
		acceleration = (acceleration - (velocity .Length() / maxVelocity) * (movementDir * accelerationConstant * 2));


	keyPressed = false;
	if (keyPress[FRONT_KEY] && !disabledKey[FRONT_KEY])//accelerate front
	{
		acceleration = (acceleration + (front * accelerationConstant * 2));
		keyPressed = true;
	}

	if (!isRotationMode)
	{
		if (keyPress[LEFT_KEY] && !disabledKey[LEFT_KEY])//accelerate left
		{
			acceleration = (acceleration + (-right * accelerationConstant * 2));
			keyPressed = true;

			if (animation && angle.z > -10)
			{
				addRotation(-velocity .x / 2, 'z');
			}
		}
		if (!keyPress[LEFT_KEY])
		{
			if (angle.z < 0)
			{
				addRotation(1, 'z');
			}
		}
		if (keyPress[RIGHT_KEY] && !disabledKey[RIGHT_KEY])//accelerate right
		{
			acceleration = (acceleration + (right * accelerationConstant * 2));
			keyPressed = true;

			if (animation && angle.z < 10)
			{
				addRotation(-velocity .x / 2, 'z');
			}
		}
		if (!keyPress[RIGHT_KEY])
		{
			if (angle.z > 0)
			{
				addRotation(-1, 'z');
			}
		}

		if (keyPress[BACK_KEY] && !disabledKey[BACK_KEY])//accelerate back
		{
			acceleration =(acceleration - (front * accelerationConstant * 2));
			keyPressed = true;
		}
		if (keyPress[UP_KEY] && !disabledKey[UP_KEY])//accelerate up
		{
			acceleration = (acceleration + (Vector3(0, 1, 0) * accelerationConstant * 1.5));
			keyPressed = true;
		}
		if (keyPress[DOWN_KEY] && !disabledKey[DOWN_KEY])//accelerate down
		{
			acceleration = (acceleration + (Vector3(0, -1, 0) * accelerationConstant));
			keyPressed = true;
		}
	}
	if(hasGravity()&&!isGrounded()&&!keyPress[UP_KEY])
		acceleration = (acceleration.x, acceleration.y - accelerationConstant * 5, acceleration.z);
	
	velocity = (velocity  + acceleration * dt);
}
//================================================================================================================================


Joint::Joint(Mesh* mesh)
{
	meshType = mesh;
	parentRotation = true;
	parentScale = true;
}
//================================================================================================================================


RigidBody::RigidBody(Mesh* mesh)
{
	meshType = mesh;
	dimension.y = -1;
	gravity = true;
	movable = true;
}