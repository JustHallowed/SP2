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
		pos = parent->getPos()+ translation;
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
		this->angle.x = angle;
	}
	else
		if (axis == 'y')
		{
			this->angle.y = angle;
		}
		else
			if (axis == 'z')
			{
				this->angle.z = angle;
			}
}
void Object::addRotation(float angle, char axis)
{
	Mtx44 rotation;
	if (axis == 'x')
	{
		this->angle.x += angle;
	}
	else
		if (axis == 'y')
		{
			this->angle.y += angle;
		}
		else
			if (axis == 'z')
			{
				this->angle.z += angle;
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
void Object::updateCollision(Object* b,double dt)
{
	Vector3 displacementA,displacementB;//magnitude of displacement the two object will be applied if there is collision 
	Vector3 T = pos - b->pos;//displacement between the two object's centre
	float Wa, Ha, Da;// half dimensions of A (Width, Height, Depth)
	float Wb, Hb, Db;// half dimensions of B (Width, Height, Depth)
	Vector3 Ax, Ay, Az;// unit vector of the axes of A
	Vector3 Bx, By, Bz;// unit vector of the axes of B
	Mtx44 rAx,rAy,rAz,rBx,rBy,rBz;
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

	//Checking by A

	float LHS = projPlane(T,Ax).Length(); //Projection of T onto plane with normal Ax
	float RHS = projPlane(Ax * Wa, Ax).Length() + projPlane(Ay * Ha, Ax).Length() + projPlane(Az * Da, Ax).Length() + 
				projPlane(Bx * Wb, Ax).Length() + projPlane(By * Hb, Ax).Length() + projPlane(Bz * Db, Ax).Length();
	if (LHS <= RHS)//Collision
	{
		if (abs(LHS - RHS) < 1)
		{
			if (T.x >= 0)
			{
				collisionAt[POSX] = true;
			}
			else
			{
				collisionAt[NEGX] = true;
			}
		}
	}
	else
	{
		return;
	}

	 LHS = projPlane(T, Ay).Length(); //Projection of T onto plane with normal Ay
	 RHS = projPlane(Ax * Wa, Ay).Length() + projPlane(Ay * Ha, Ay).Length() + projPlane(Az * Da, Ay).Length() +
		projPlane(Bx * Wb, Ay).Length() + projPlane(By * Hb, Ay).Length() + projPlane(Bz * Db, Ay).Length();
	if (LHS <= RHS)//Collision
	{
		if (abs(LHS - RHS) < 1)
		{
			if (T.y >= 0)
			{
				collisionAt[POSY] = true;
			}
			else
			{
				collisionAt[NEGY] = true;
			}
		}
	}
	else
	{
		return;
	}

	 LHS = projPlane(T, Az).Length(); //Projection of T onto plane with normal Az
	 RHS = projPlane(Ax * Wa, Ay).Length() + projPlane(Ay * Ha, Ay).Length() + projPlane(Az * Da, Ay).Length() +
		projPlane(Bx * Wb, Ay).Length() + projPlane(By * Hb, Ay).Length() + projPlane(Bz * Db, Ay).Length();
	if (LHS <= RHS)//Collision
	{
		if (abs(LHS - RHS) < 1)
		{
			if (T.z >= 0)
			{
				collisionAt[POSZ] = true;
			}
			else
			{
				collisionAt[NEGZ] = true;
			}
		}
	}
	else
	{
		return;
	}

	//Checking by B

	 LHS = projPlane(T, Bx).Length(); //Projection of T onto plane with normal Bx
	 RHS = projPlane(Ax * Wa, Bx).Length() + projPlane(Ay * Ha, Bx).Length() + projPlane(Az * Da, Bx).Length() +
		projPlane(Bx * Wb, Bx).Length() + projPlane(By * Hb, Bx).Length() + projPlane(Bz * Db, Bx).Length();
	if (LHS <= RHS)//Collision
	{
		if (abs(LHS - RHS) < 3)
		{
			if (T.x >= 0)
			{
				b->collisionAt[POSX] = true;
			}
			else
			{
				b->collisionAt[NEGX] = true;
			}
		}
	}
	else
	{
		return;
	}

	 LHS = projPlane(T, By).Length(); //Projection of T onto plane with normal By
	 RHS = projPlane(Ax * Wa, By).Length() + projPlane(By * Ha, By).Length() + projPlane(Az * Da, By).Length() +
		projPlane(Bx * Wb, By).Length() + projPlane(By * Hb, By).Length() + projPlane(Bz * Db, By).Length();
	if (LHS <= RHS)//Collision
	{
		if (T.y >= 0)
		{
			b->collisionAt[POSY] = true;
		}
		else
		{
			b->collisionAt[NEGY] = true;
		}
	}
	else
	{
		return;
	}

	 LHS = projPlane(T, Bz).Length(); //Projection of T onto plane with normal Bz
	 RHS = projPlane(Ax * Wa, Ay).Length() + projPlane(Ay * Ha, Ay).Length() + projPlane(Bz * Da, Ay).Length() +
		projPlane(Bx * Wb, Ay).Length() + projPlane(By * Hb, Ay).Length() + projPlane(Bz * Db, Ay).Length();
	if (LHS <= RHS)//Collision
	{
		if (T.z >= 0)
		{
			b->collisionAt[POSZ] = true;
		}
		else
		{
			b->collisionAt[NEGZ] = true;
		}
	}
	else
	{
		return;
	}

	//Edges

	Vector3 L = Ax.Cross(Bx); //Normal of separating plane
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	L = Ax.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	L = Ax.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	L = Ay.Cross(Bx); //Normal of separating plane
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	L = Ay.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	L = Ay.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	L = Az.Cross(Bx); //Normal of separating plane
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	L = Az.Cross(By);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	L = Az.Cross(Bz);
	LHS = projPlane(T, L).Length();
	RHS = projPlane(Wa * Ax, L).Length() + projPlane(Ha * Ay, L).Length() + projPlane(Da * Az, L).Length() +
		projPlane(Wb * Bx, L).Length() + projPlane(Hb * By, L).Length() + projPlane(Db * Bz, L).Length();
	if (LHS <= RHS)//Collision
	{
	}
	else
	{
		return;
	}

	if (!b->isMovable())
	{
		if (collisionAt[POSX])
		{
			velocity -= Vector3(Ax.x * velocity.x, Ax.y * velocity.y, Ax.z * velocity.z);
		}
		if (collisionAt[POSY])
		{
			velocity -= Vector3(Ay.x * velocity.x, Ay.y * velocity.y, Ay.z * velocity.z);
		}
		if (collisionAt[POSZ])
		{
			velocity -= Vector3(Az.x * velocity.x, Az.y * velocity.y, Az.z * velocity.z);
		}
		if (collisionAt[NEGX])
		{
			velocity -= Vector3(-Ax.x * velocity.x, -Ax.y * velocity.y, -Ax.z * velocity.z);
		}
		if (collisionAt[NEGY])
		{
			velocity -= Vector3(-Ay.x * velocity.x, -Ay.y * velocity.y, -Ay.z * velocity.z);
		}
		if (collisionAt[NEGZ])
		{
			velocity -= Vector3(-Az.x * velocity.x, -Az.y * velocity.y, -Az.z * velocity.z);
		}
	}
	moveBy(velocity.x, velocity.z, velocity.z);
}
void updatePhysics()
{

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
void Object::bind(Object* parent, Object* child,bool followParentRotation,bool followParentScale)
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
