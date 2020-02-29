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
	hasMoved = false;
	grounded = false;
	gravity = false;
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
void Object::setHasGravity(bool hasGravity)
{
	this->gravity = hasGravity;
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
void Object::resetCollision()
{
	hasMoved = false;
	grounded = false;
}
void Object::updatePosition(double dt)
{
	moveBy(velocity.x,velocity.y,velocity.z);
}
bool Object::updateCollision(Object* b, double dt)
{
	Vector3 T = b->pos - pos;//displacement between the two object's centre
	Vector3 penetration; //magnitude of overlapp of object
	Vector3 rotationAxis;//axis of rotation during collision

	bool faceCollision, edgeCollision = false;

	float greatestFaceIntersectionA = 0; //for checking which face collides
	float greatestFaceIntersectionB = 0;

	Vector3 collidingFaceAxisA; //for storing collding axes
	Vector3 collidingFaceAxisB;

	faceCollision = hasFaceIntersection(b, &greatestFaceIntersectionA, &collidingFaceAxisA, &greatestFaceIntersectionB, &collidingFaceAxisB, &penetration, &rotationAxis);
	if (faceCollision)
		edgeCollision = hasEdgeIntersection(b);

	if (faceCollision && edgeCollision)
	{
		findCollisionDirection(b, &collidingFaceAxisA, &collidingFaceAxisB);
 		if (collidingFaceAxisA.y < 0)
			grounded = true;
		else
		{
			int i =1;
		}
		penetration.Set(penetration.x * collidingFaceAxisA.x, penetration.y * collidingFaceAxisA.y, penetration.z * collidingFaceAxisA.z);
		if (!b->isMovable())
		{
			if (velocity.x != 0)
			{
				if (collidingFaceAxisB.x > 0 && velocity.x < 0)
					velocity.x -= collidingFaceAxisB.x * velocity.x;
				else
					if (collidingFaceAxisB.x < 0 && velocity.x > 0)
						velocity.x += collidingFaceAxisB.x * velocity.x;
			}
			if (velocity.y != 0)
			{
				if (collidingFaceAxisB.y > 0 && velocity.y < 0)
					velocity.y -= collidingFaceAxisB.y * velocity.y;
				else
					if (collidingFaceAxisB.y < 0 && velocity.y > 0)
						velocity.y += collidingFaceAxisB.y * velocity.y;
			}
			if (velocity.z != 0)
			{
				if (collidingFaceAxisB.z > 0 && velocity.z < 0)
					velocity.z -= collidingFaceAxisB.z * velocity.z;
				else
					if (collidingFaceAxisB.z < 0 && velocity.z > 0)
						velocity.z += collidingFaceAxisB.z * velocity.z;
			}
			moveBy(-penetration.x, -penetration.y, -penetration.z);
			if (movable)
			{
				angle.x += ((float)rotationAxis.x * (float)velocity.x - (float)b->velocity.x * 100 * dt);
				angle.y += (rotationAxis.y * velocity.y - b->velocity.y * 100 * dt);
				angle.z += (rotationAxis.z * velocity.z - b->velocity.z * 100 * dt);
			}
		}
		return true;
	}
	else
		return false;
}


bool Object::hasFaceIntersection(Object* b, float* greatestFaceIntersectionA, Vector3* collidingFaceAxisA,
	float* greatestFaceIntersectionB, Vector3* collidingFaceAxisB, Vector3* penetration, Vector3* rotationAxis)
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
	}
	else
	{
		return false;
	}

	LHS = abs(T.Dot(Ay)); //Projection of T onto plane with normal Ax
	RHS = Ha + abs(Hb * Ay.Dot(By)) + abs(Db * Ay.Dot(Bz));
	if (LHS <= RHS)
	{
		if (RHS - LHS < *greatestFaceIntersectionA)
		{
			*greatestFaceIntersectionA = RHS - LHS;
			*collidingFaceAxisA = Ay;
		}
	}
	else
	{
		return false;
	}

	LHS = abs(T.Dot(Az)); //Projection of T onto plane with normal Az
	RHS = Da + abs(Wb * Az.Dot(Bx)) + abs(Hb * Az.Dot(By)) + abs(Db * Az.Dot(Bz));
	if (LHS <= RHS)//if collision
	{
		if (RHS - LHS < *greatestFaceIntersectionA)
		{
			*greatestFaceIntersectionA = RHS - LHS;
			*collidingFaceAxisA = Az;
		}
	}
	else
	{
		return false;
	}

 	*penetration = (*greatestFaceIntersectionA) * (*collidingFaceAxisA);
	//Checking by B

	LHS = abs(T.Dot(Bx)); //Projection of T onto plane with normal Bx
	RHS = abs(Wa * Ax.Dot(Bx)) + abs(Ha * Ay.Dot(Bx)) + abs(Da * Az.Dot(Bx)) + Wb;
	if (LHS <= RHS)//Collision
	{
		*greatestFaceIntersectionB = RHS - LHS;
		*collidingFaceAxisB = Bx;
		//penetration->x -= b->dimension.x / 2; replace with separate penetration b
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
		//penetration->y -= b->dimension.y / 2; replace with separate penetration b
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
		//penetration->z -= b->dimension.z / 2; replace with separate penetration b
	}
	else
	{
		return false;
	}
	if (*greatestFaceIntersectionB < *greatestFaceIntersectionA)
	{
		*penetration = (*greatestFaceIntersectionB) * (*collidingFaceAxisA);
	}
	//*rotationAxis = collidingFaceAxisA->Cross(*collidingFaceAxisB);
}
bool Object::hasEdgeIntersection(Object* b)
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

	Vector3 L = Ax.Cross(Bx); //Normal of separating plane aka separating axis
	float LHS = projPlane(T, L).Length();
	float RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	L = Ax.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	L = Ax.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	L = Ay.Cross(Bx); //Normal of separating plane
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	L = Ay.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	L = Ay.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	L = Az.Cross(Bx); //Normal of separating plane
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	L = Az.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	L = Az.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else return false;

	return true;
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
		if (T.x > 0 && (angle.y > 90 && angle.y < 270) || (angle.z > 90 && angle.z < 270))
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
		if (T.y > 0 && (angle.x > 90 && angle.x < 270) || (angle.z > 90 && angle.z < 270))
		{
			*uniqueAxisA = -*uniqueAxisA;
		}
		else if (T.y < 0 && (angle.x < 90 || angle.x >270) && (angle.z < 90 || angle.z >270))
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
bool Object::isGrounded()
{
	return grounded;
}
bool Object::hasGravity()
{
	return gravity;
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

float Object::getDist(Vector3 playerpos)
{
	float x = pow(pos.x - playerpos.x, 2.0);
	float z = pow(pos.z - playerpos.z, 2.0);
	return sqrt(x + z);
}

float Object::getAngle(Vector3 A, Vector3 B)
{
	//gets angle between two vectors
	float ptoMagnitude = sqrt(pow(A.x, 2.0) + pow(A.y, 2.0) + pow(A.z, 2.0));
	float pttMagnitude = sqrt(pow(B.x, 2.0) + pow(B.y, 2.0) + pow(B.z, 2.0));
	return acos(A.Dot(B) / (ptoMagnitude * pttMagnitude));
}

float Object::checkDist(Vector3 playerpos)
{
	float x = pow(pos.x - playerpos.x, 2.0);
	float z = pow(pos.z - playerpos.z, 2.0);
	return sqrt(x + z);
}