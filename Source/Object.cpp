#include "Object.h"

Object::Object()
{
	meshType = nullptr;
	parent = nullptr;
	pos.SetZero();
	translation.SetZero();
	angle.SetZero();
	scale.Set(1, 1, 1);
	render = true;
	clockwise = false;
	parentRotation = false;
	parentScale = false;
	interactable = false;
	movable = false;
	collisionAt[0] = false;
	collisionAt[1] = false;
	collisionAt[2] = false;
	collisionAt[3] = false;
	collisionAt[4] = false;
	collisionAt[5] = false;
}

Object::~Object()
{
}

void Object::setPos(float x, float y, float z)
{
	translation += (Vector3(x, y, z) - pos);
	pos.Set(x, y, z);
}
void Object::setTranslation(float x, float y, float z)
{
	translation.Set(x, y, z);
	if (parent != nullptr)
	{
		pos = parent->getPos() + translation;
	}
	else
		pos = translation;
}
void Object::setVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}
void Object::setAcceleration(Vector3 acceleration)
{
	this->acceleration = acceleration;
}
void Object::setVelocity(float x, float y, float z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}
void Object::setAcceleration(float x, float y, float z)
{
	acceleration.x = x;
	acceleration.y = y;
	acceleration.z = z;
}
void Object::moveBy(float x, float y, float z)
{
	translation.Set(translation.x + x, translation.y + y, translation.z + z);
	if (parent != nullptr)
	{
		pos = parent->getPos() + translation;
	}
	else
		pos = translation;
}
void Object::setRotation(float angle, char axis)
{
	Mtx44 rotation;
	if (axis == 'x')
	{
		this->angle.x = std::fmod(angle, 360);

	}
	else
		if (axis == 'y')
		{
			this->angle.y = std::fmod(angle, 360);
		}
		else
			if (axis == 'z')
			{
				this->angle.z = std::fmod(angle, 360);
			}
}
void Object::addRotation(float angle, char axis)
{
	Mtx44 rotation;
	if (axis == 'x')
	{
		setRotation(this->angle.x + angle, 'x');
	}
	else
		if (axis == 'y')
		{
			setRotation(this->angle.y + angle, 'y');
		}
		else
			if (axis == 'z')
			{
				setRotation(this->angle.z + angle, 'z');
			}
}
void Object::setScale(float x, float y, float z)
{
	if (parent == nullptr)
		scale.Set(x, y, z);
	else
		scale.Set(x, y, z);
}
void Object::setScale(float scale)
{
	if (parent == nullptr)
	{
		this->scale.Set(scale, scale, scale);
	}
	else
		this->scale.Set(scale, scale, scale);
}
void Object::setParent(Object* parent)
{
	this->parent = parent;
}
void Object::setChild(Object* child)
{
	this->child.push_back(child);
}
void Object::setMesh(Mesh* mesh)
{
	meshType = mesh;
}

void Object::setMesh(Mesh* mesh, Object parent, Vector3 translation)
{
	meshType = mesh;
	this->parent = &parent;
	pos = parent.pos + translation;
	this->translation = translation;
}

void Object::setMesh(Mesh* mesh, Object* parent)
{
	meshType = mesh;
	this->parent = parent;
	pos = parent->getPos();
}

void Object::setMesh(Mesh* mesh, Vector3 translation)
{
	meshType = mesh;
	this->translation = translation;
}
void Object::setDimension(float x, float y, float z)
{
	dimension = Vector3(x, y, z);
}
void Object::setIsClockwise(bool boolean)
{
	clockwise = boolean;
}
void Object::setRender(bool render)//set if is object rendered in the scene
{
	this->render = render;
}
void Object::setMovable(bool movable)
{
	this->movable = movable;
}
void Object::resetCollision()
{
	collisionAt[0] = false;
	collisionAt[1] = false;
	collisionAt[2] = false;
	collisionAt[3] = false;
	collisionAt[4] = false;
	collisionAt[5] = false;
}
bool Object::isClockwise()
{
	return clockwise;
}
bool Object::followParentRotation()
{
	return parentRotation;
}
bool Object::followParentScale()
{
	return parentScale;

}
bool Object::isInteractable()
{
	return interactable;
}
Vector3 Object::getScale()
{
	return scale;
}
Object* Object::getParent()
{
	return parent;
}
std::vector<Object*> Object::getChild()
{
	return child;
}
Vector3 Object::getPos()
{
	return pos;
}
Vector3 Object::getTranslation()
{
	return translation;
}
Vector3 Object::getAngle()
{
	return angle;
}
Mesh* Object::getMesh()
{
	return meshType;
}
Vector3 Object::getDimension()
{
	return dimension;
}
Vector3 Object::getVelocity()
{
	return velocity;
}
Vector3 Object::getAcceleration()
{
	return acceleration;
}
bool Object::isRender()
{
	return render;
}
bool Object::isMovable()
{
	return movable;
}
void Object::setInteractable(bool canInteract)
{
	interactable = canInteract;
}
void Object::updateCollision(Object* b, double dt)
{
	Vector3 displacementA, displacementB;//magnitude of displacement the two object will be applied if there is collision 
	Vector3 T = b->pos - pos;//displacement between the two object's centre
	float Wa, Ha, Da;// half dimensions of A (Width, Height, Depth)
	float Wb, Hb, Db;// half dimensions of B (Width, Height, Depth)
	Vector3 Ax, Ay, Az;// unit vector of the axes of A
	Vector3 Bx, By, Bz;// unit vector of the axes of B
	Mtx44 rAx, rAy, rAz, rBx, rBy, rBz;

	bool faceCollision, edgeCollision = false;
	
	if (angle != Vector3(0, 0, 0))
	{
		rAx.SetToRotation(angle.x, 1, 0, 0);
		rAy.SetToRotation(angle.y, 0, 1, 0);
		rAz.SetToRotation(angle.z, 0, 0, 1);
	}
	if (b->angle != Vector3(0, 0, 0))
	{
		rBx.SetToRotation(b->angle.x, 1, 0, 0);
		rBy.SetToRotation(b->angle.y, 0, 1, 0);
		rBz.SetToRotation(b->angle.z, 0, 0, 1);
	}

	Wa = dimension.x / 2;
	Ha = dimension.y / 2;
	Da = dimension.z / 2;

	Wb = b->dimension.x / 2;
	Hb = b->dimension.y / 2;
	Db = b->dimension.z / 2;

	Vector3 penetration = Vector3(abs(T.x), abs(T.y), abs(T.z));

	Ax = Vector3(1, 0, 0);
	Ay = Vector3(0, 1, 0);
	Az = Vector3(0, 0, 1);

	Bx = Vector3(1, 0, 0);
	By = Vector3(0, 1, 0);
	Bz = Vector3(0, 0, 1);
	if (angle != Vector3(0, 0, 0))
	{
		Ax = rAx * rAy * rAz * Ax;
		Ay = rAx * rAy * rAz * Ay;
		Az = rAx * rAy * rAz * Az;
	}
	if (b->angle != Vector3(0, 0, 0))
	{
		Bx = rBx * rBy * rBz * Bx;
		By = rBx * rBy * rBz * By;
		Bz = rBx * rBy * rBz * Bz;
	}

	float greatestFaceIntersectionA = 0; //for checking which face collides
	float greatestEdgeIntersectionA = 0;
	float greatestFaceIntersectionB = 0;
	float greatestEdgeIntersectionB = 0;

	Vector3 collidingFaceAxisA; //for storing collding axes
	Vector3 collidingEdgeAxisA;
	Vector3 collidingFaceAxisB;
	Vector3 collidingEdgeAxisB;

	faceCollision = hasFaceIntersection(b,&greatestFaceIntersectionA,&collidingFaceAxisA,&greatestFaceIntersectionB,&collidingFaceAxisB,&penetration);
	
	edgeCollision = hasEdgeIntersection(b, &greatestEdgeIntersectionA, &collidingEdgeAxisA, &greatestEdgeIntersectionB, &collidingEdgeAxisB, &penetration);

	if (faceCollision)//find if face collision is at positive or negative axis
	{
		findCollisionDirection(b, &collidingFaceAxisA, &collidingFaceAxisB);

		if (faceCollision || edgeCollision)
		{

			if (!b->isMovable())
			{
				if (velocity.x != 0)//changes velocity towards object b to 0
				{
					if (collidingFaceAxisB.x < 0)
					{
						if (velocity.x > 0)
							velocity.x += collidingFaceAxisB.x * velocity.x;
					}
					else if (collidingFaceAxisB.x > 0)
					{
						if (velocity.x < 0)
							velocity.x -= collidingFaceAxisB.x * velocity.x;
					}
				}
				if (velocity.y != 0)
				{
					if (collidingFaceAxisB.y < 0)
					{
						if (velocity.y > 0)
							velocity.y += collidingFaceAxisB.y * velocity.y;
					}
					else if (collidingFaceAxisB.y > 0)
					{
						if (velocity.y < 0)
							velocity.y -= collidingFaceAxisB.y * velocity.y;
					}
				}
				if (velocity.z != 0)
				{
					if (collidingFaceAxisB.z < 0)
					{
						if (velocity.z > 0)
							velocity.z += collidingFaceAxisB.z * velocity.z;
					}
					else if (collidingFaceAxisB.z > 0)
					{
						if (velocity.z < 0)
							velocity.z -= collidingFaceAxisB.z * velocity.z;
					}
				}

				if (penetration.x < penetration.y) //find lowest penetration among the axis
				{
					if (penetration.y < penetration.z)
					{
						if (penetration.z < 0)
						{
							if (collidingFaceAxisA.z > 0)
								translation.z += penetration.z;
							else if (collidingFaceAxisA.z < 0)
								translation.z -= penetration.z;
						}
					}
					else
					{
						if (penetration.y < 0)
						{
							if (collidingFaceAxisA.y>0)
								translation.y += penetration.y;
							else if (collidingFaceAxisA.y<0)
								translation.y -= penetration.y;
						}
					}
				}
				else if (penetration.x < penetration.z)
				{
					if (penetration.z < 0)
					{
						if (collidingFaceAxisA.z>0)
							translation.z += penetration.z;
						else if (collidingFaceAxisA.z < 0)
							translation.z -= penetration.z;
					}
				}
				else if (penetration.x < 0)
				{
					if (collidingFaceAxisA.x>0)
						translation.x += penetration.x;
					else if (collidingFaceAxisA.x < 0)
						translation.x -= penetration.x;
				}
			}
			//if(edgeCollision)
			//std::cout << "EDGE COLLISION\n";

			//if (faceCollision)

				std::cout << collidingFaceAxisB.x << "," << collidingFaceAxisB.y << "," << collidingFaceAxisB.z;
		}
	}
	moveBy(velocity.x, velocity.y, velocity.z);
}

bool Object::hasFaceIntersection(Object* b, float* greatestFaceIntersectionA, Vector3* collidingFaceAxisA,
	float* greatestFaceIntersectionB, Vector3* collidingFaceAxisB, Vector3* penetration)
{
	Vector3 T = b->pos - pos;
	Vector3 Ax, Ay, Az;// unit vector of the axes of A
	Vector3 Bx, By, Bz;// unit vector of the axes of B
	Mtx44 rAx, rAy, rAz, rBx, rBy, rBz;
	if (angle != Vector3(0, 0, 0))
	{
		rAx.SetToRotation(angle.x, 1, 0, 0);
		rAy.SetToRotation(angle.y, 0, 1, 0);
		rAz.SetToRotation(angle.z, 0, 0, 1);
	}
	if (b->angle != Vector3(0, 0, 0))
	{
		rBx.SetToRotation(b->angle.x, 1, 0, 0);
		rBy.SetToRotation(b->angle.y, 0, 1, 0);
		rBz.SetToRotation(b->angle.z, 0, 0, 1);
	}
	Ax = Vector3(1, 0, 0);
	Ay = Vector3(0, 1, 0);
	Az = Vector3(0, 0, 1);

	Bx = Vector3(1, 0, 0);
	By = Vector3(0, 1, 0);
	Bz = Vector3(0, 0, 1);

	if (angle != Vector3(0, 0, 0))
	{
		Ax = rAx * rAy * rAz * Ax;
		Ay = rAx * rAy * rAz * Ay;
		Az = rAx * rAy * rAz * Az;
	}
	if (b->angle != Vector3(0, 0, 0))
	{
		Bx = rBx * rBy * rBz * Bx;
		By = rBx * rBy * rBz * By;
		Bz = rBx * rBy * rBz * Bz;
	}

	float Wa, Ha, Da;// half dimensions of A (Width, Height, Depth)
	float Wb, Hb, Db;// half dimensions of B (Width, Height, Depth)

	Wa = dimension.x / 2;
	Ha = dimension.y / 2;
	Da = dimension.z / 2;

	Wb = b->dimension.x / 2;
	Hb = b->dimension.y / 2;
	Db = b->dimension.z / 2;
	//Checking by A
	float LHS = abs(T.Dot(Ax)); //Projection of T onto plane with normal Ax
	float RHS = Wa + abs(Wb * Ax.Dot(Bx)) + abs(Hb * Ax.Dot(By)) + abs(Db * Ax.Dot(Bz));
	if (LHS <= RHS)
	{
		*greatestFaceIntersectionA = RHS - LHS;//intersection at X plane
		*collidingFaceAxisA = Ax;
		penetration->x -= dimension.x / 2;
	}
	else
	{
		return false;
	}

	LHS = abs(T.Dot(Ay)); //Projection of T onto plane with normal Ax
	RHS = Ha + abs(Hb * Ay.Dot(By)) + abs(Db * Ay.Dot(Bz));
	if (LHS <= RHS)
	{
		if (RHS - LHS < * greatestFaceIntersectionA)
		{
			*greatestFaceIntersectionA = RHS - LHS;
			*collidingFaceAxisA = Ay;
		}
		penetration->y -= dimension.y /2;
	}
	else
	{
		return false;
	}

	LHS =abs(T.Dot( Az)); //Projection of T onto plane with normal Az
	RHS = Da + abs(Wb * Az.Dot(Bx)) + abs(Hb * Az.Dot(By)) + abs(Db * Az.Dot(Bz));
	if (LHS <= RHS)//if collision
	{
		if (RHS - LHS < *greatestFaceIntersectionA)
		{
			*greatestFaceIntersectionA = RHS - LHS;
			*collidingFaceAxisA = Az;
		}
		penetration->z -= dimension.z /2;
	}
	else
	{
		return false;
	}

	//Checking by B

	LHS = abs(T.Dot(Bx)); //Projection of T onto plane with normal Bx
	RHS = abs(Wa * Ax.Dot(Bx)) + abs(Ha * Ay.Dot(Bx)) + abs(Da * Az.Dot(Bx)) + Wb;
	if (LHS <= RHS)//Collision
	{
		*greatestFaceIntersectionB = RHS - LHS;
		*collidingFaceAxisB = Bx;
		penetration->x -= b->dimension.x /2;
	}
	else
	{
		return false;
	}

	LHS = abs(T.Dot(By)); //Projection of T onto plane with normal By
	RHS = abs(Wa * Ax.Dot(By)) + abs(Ha * Ay.Dot(By)) + abs(Da * Az.Dot(By)) + Hb;
	if (LHS <= RHS)//Collision
	{
		if (RHS - LHS < *greatestFaceIntersectionB)
		{
			*greatestFaceIntersectionB = RHS - LHS;
			*collidingFaceAxisB = By;
		}
		penetration->y -= b->dimension.y/2 ;
	}
	else
	{
		return false;
	}

	LHS = abs(T.Dot(Bz)); //Projection of T onto plane with normal Bz
	RHS = abs(Wa * Ax.Dot(Bz)) + abs(Ha * Ay.Dot(Bz)) + abs(Da * Az.Dot(Bz)) + Db;
	if (LHS <= RHS)//Collision
	{

		if (RHS - LHS < *greatestFaceIntersectionB)	
		{
			*greatestFaceIntersectionB = RHS - LHS;
			*collidingFaceAxisB = Bz;
		}
		penetration->z -= b->dimension.z /2;
	}
	else
	{
		return false;
	}
}
bool Object::hasEdgeIntersection(Object* b, float* greatestEdgeIntersectionA, Vector3* collidingEdgeAxisA,
	float* greatestEdgeIntersectionB, Vector3* collidingEdgeAxisB, Vector3* penetration)
{
	Vector3 T = b->pos - pos;
	Vector3 Ax, Ay, Az;// unit vector of the axes of A
	Vector3 Bx, By, Bz;// unit vector of the axes of B
	Mtx44 rAx, rAy, rAz, rBx, rBy, rBz;
	if (angle != Vector3(0, 0, 0))
	{
		rAx.SetToRotation(angle.x, 1, 0, 0);
		rAy.SetToRotation(angle.y, 0, 1, 0);
		rAz.SetToRotation(angle.z, 0, 0, 1);
	}
	if (b->angle != Vector3(0, 0, 0))
	{
		rBx.SetToRotation(b->angle.x, 1, 0, 0);
		rBy.SetToRotation(b->angle.y, 0, 1, 0);
		rBz.SetToRotation(b->angle.z, 0, 0, 1);
	}
	Ax = Vector3(1, 0, 0);
	Ay = Vector3(0, 1, 0);
	Az = Vector3(0, 0, 1);

	Bx = Vector3(1, 0, 0);
	By = Vector3(0, 1, 0);
	Bz = Vector3(0, 0, 1);
	if (angle != Vector3(0, 0, 0))
	{
		Ax = rAx * rAy * rAz * Ax;
		Ay = rAx * rAy * rAz * Ay;
		Az = rAx * rAy * rAz * Az;
	}
	if (b->angle != Vector3(0, 0, 0))
	{
		Bx = rBx * rBy * rBz * Bx;
		By = rBx * rBy * rBz * By;
		Bz = rBx * rBy * rBz * Bz;
	}

	float Wa, Ha, Da;// half dimensions of A (Width, Height, Depth)
	float Wb, Hb, Db;// half dimensions of B (Width, Height, Depth)

	Wa = dimension.x / 2;
	Ha = dimension.y / 2;
	Da = dimension.z / 2;

	Wb = b->dimension.x / 2;
	Hb = b->dimension.y / 2;
	Db = b->dimension.z / 2;

	bool hasEdgeCollision = false;

	Vector3 L = Ax.Cross(Bx); //Normal of separating plane aka separating axis
	float LHS = projPlane(T, L).Length();
	float RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	L = Ax.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	L = Ax.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	L = Ay.Cross(Bx); //Normal of separating plane
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	L = Ay.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	L = Ay.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	L = Az.Cross(Bx); //Normal of separating plane
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	L = Az.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	L = Az.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
		hasEdgeCollision = true;
	}
	else return false;

	return hasEdgeCollision;
}

void Object::findCollisionDirection(Object* b, Vector3* uniqueAxisA, Vector3* uniqueAxisB)
{
	Vector3 T = b->pos - pos;
	Vector3 Ax, Ay, Az;// unit vector of the axes of A
	Vector3 Bx, By, Bz;// unit vector of the axes of B
	Mtx44 rAx, rAy, rAz, rBx, rBy, rBz;
	if (angle != Vector3(0, 0, 0))
	{
		rAx.SetToRotation(angle.x, 1, 0, 0);
		rAy.SetToRotation(angle.y, 0, 1, 0);
		rAz.SetToRotation(angle.z, 0, 0, 1);
	}
	if (b->angle != Vector3(0, 0, 0))
	{
		rBx.SetToRotation(b->angle.x, 1, 0, 0);
		rBy.SetToRotation(b->angle.y, 0, 1, 0);
		rBz.SetToRotation(b->angle.z, 0, 0, 1);
	}
	Ax = Vector3(1, 0, 0);
	Ay = Vector3(0, 1, 0);
	Az = Vector3(0, 0, 1);

	Bx = Vector3(1, 0, 0);
	By = Vector3(0, 1, 0);
	Bz = Vector3(0, 0, 1);
	if (angle != Vector3(0, 0, 0))
	{
		Ax = rAx * rAy * rAz * Ax;
		Ay = rAx * rAy * rAz * Ay;
		Az = rAx * rAy * rAz * Az;
	}
	if (b->angle != Vector3(0, 0, 0))
	{
		Bx = rBx * rBy * rBz * Bx;
		By = rBx * rBy * rBz * By;
		Bz = rBx * rBy * rBz * Bz;
	}
	if (*uniqueAxisA == Ax)//find if collision is at positive or negative axis
	{
		if (T.x>0 && (angle.y > 90 && angle.y < 270) || (angle.z > 90 && angle.z < 270))
		{
			*uniqueAxisA = -*uniqueAxisA;
		}
		else if (T.x < 0 && (angle.y < 90 || angle.y >270) && (angle.z < 90 || angle.z >270))
		{
			*uniqueAxisA = -*uniqueAxisA;
		}
	}
	else if (*uniqueAxisA == Ay)
	{
		if (T.x > 0 && (angle.x > 90 && angle.x < 270) || (angle.z > 90 && angle.z < 270))
		{
			*uniqueAxisA = -*uniqueAxisA;
		}
		else if (T.x < 0 && (angle.x < 90 || angle.x >270) && (angle.z < 90 || angle.z >270))
		{
			*uniqueAxisA = -*uniqueAxisA;
		}
	}
	else if (*uniqueAxisA == Az)
	{
		if (T.z > 0 && (angle.x > 90 && angle.x < 270) || (angle.y > 90 && angle.y < 270))
		{
			*uniqueAxisA = -*uniqueAxisA;
		}
		else if (T.z < 0 && (angle.x < 90 || angle.x >270) && (angle.z < 90 || angle.z >270))
		{
			*uniqueAxisA = -*uniqueAxisA;
		}
	}

	if (*uniqueAxisB == Bx)//find if collision is at positive or negative axis
	{
		if (T.x < 0 && (b->angle.z > 90 && b->angle.z < 270) || (b->angle.x > 90 && b->angle.x < 270))
		{
			*uniqueAxisB = -*uniqueAxisB;
		}
		else if (T.x > 0 && (b->angle.z < 90 || b->angle.z >270) && (b->angle.x < 90 || b->angle.x >270))
		{
			*uniqueAxisB = -*uniqueAxisB;
		}
	}
	else if (*uniqueAxisB == By)
	{
		if (T.y < 0 && (b->angle.z > 90 && b->angle.z < 270) || (b->angle.x > 90 && b->angle.x < 270))
		{
			*uniqueAxisB = -*uniqueAxisB;
		}
		else if (T.y > 0 && (b->angle.z < 90 || b->angle.z >270) && (b->angle.x < 90 || b->angle.x >270))
		{
			*uniqueAxisB = -*uniqueAxisB;
		}
	}
	else if (*uniqueAxisB == Bz)
	{
		if (T.z < 0 && (b->angle.y > 90 && b->angle.y < 270) || (b->angle.x > 90 && b->angle.x < 270))
		{
			*uniqueAxisB = -*uniqueAxisB;
		}
		else if (T.z > 0 && (b->angle.y < 90 || b->angle.y >270) && (b->angle.x < 90 || b->angle.x >270))
		{
			*uniqueAxisB = -*uniqueAxisB;
		}
	}
}
Vector3 Object::projPlane(Vector3 vector, Vector3 planeNormal)
{
	return vector - vector.Dot(planeNormal) * (planeNormal);
}
void Object::unbindChild(Object* child)
{
	for (int i = 0; i < this->child.size(); ++i)//scans through all parent's children
	{
		if (this->child[i] == child)
		{
			this->child.erase(this->child.begin() + i);//unbinds child
			break;
		}
	}
}
void Object::bind(Object* parent, Object* child, bool followParentRotation, bool followParentScale)
{
	parent->setChild(child);
	child->setParent(parent);
	child->parentRotation = followParentRotation;
	child->parentScale = followParentRotation;
}

void Object::unbind(Object* child)
{
	if (child->getParent() != nullptr)
	{
		child->getParent()->unbindChild(child);
		child->setParent(nullptr);
	}
}

float Object::checkDist(Vector3 playerpos)
{
	float x = pow(pos.x - playerpos.x, 2.0);
	float z = pow(pos.z - playerpos.z, 2.0);
	return sqrt(x + z);
}
