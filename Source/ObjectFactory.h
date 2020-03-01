#pragma once
#include "Object.h"
#include "ObjectTypes.h"
#include "Enum.h"
class ObjectFactory
{
public:

	static Object* createObject(int objectType,Mesh* mesh)
	{
		switch (objectType)
		{
		case OBJ_VEHICLE:
			return new Vehicle(mesh);
			break;
		case OBJ_JOINT:
			return new Joint(mesh);
			break;
		case OBJ_RIGIDBODY:
			return new RigidBody(mesh);
			break;
		case OBJ_EMPTY:
			new Object(mesh);
		}
	}
};

