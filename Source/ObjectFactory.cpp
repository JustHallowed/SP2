#include "ObjectFactory.h"

static Object* ObjectFactory::createObject(int objectType, Mesh* mesh)
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