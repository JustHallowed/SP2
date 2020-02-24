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
	Wa = dimension.x / 4;
	Ha = dimension.y / 4;
	Da = dimension.z / 4;

	Wb = b->dimension.x / 4;
	Hb = b->dimension.y / 4;
	Db = b->dimension.z / 4;

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

	float biggestIntersect;
	Vector3 collidingAxis;
	while (1)
	{

		//Checking by A
		float LHS = projPlane(T, Ax).Length(); //Projection of T onto plane with normal Ax
		float RHS = projPlane(Ax * Wa, Ax).Length() + projPlane(Ay * Ha, Ax).Length() + projPlane(Az * Da, Ax).Length() +
			projPlane(Bx * Wb, Ax).Length() + projPlane(By * Hb, Ax).Length() + projPlane(Bz * Db, Ax).Length();
		if (LHS <= RHS)//intersection at X plane
		{
			if (RHS-LHS < 3)	//*Note: RHS-LHS is distance
			{
				if (T.x >= 0)
				{
					if (angle.y < 180.f)
						collisionAt[POSX] = true;
					else
					{
						collisionAt[NEGX] = true;
					}
				}
				else
				{
					if (angle.y < 180.f)
						collisionAt[NEGX] = true;
					else
					{
						collisionAt[POSX] = true;
					}
				}
				penetration.x -= dimension.x / 2;
			}
		}
		else
		{
			break;
		}

		LHS = projPlane(T, Ay).Length(); //Projection of T onto plane with normal Ay
		RHS = projPlane(Ax * Wa, Ay).Length() + projPlane(Ay * Ha, Ay).Length() + projPlane(Az * Da, Ay).Length() +
			projPlane(Bx * Wb, Ay).Length() + projPlane(By * Hb, Ay).Length() + projPlane(Bz * Db, Ay).Length();
		if (LHS <= RHS)//Collision
		{
			if (RHS - LHS < 3)
			{
				if (T.y >= 0)
				{
					if (angle.z < 180.f && angle.x < 180.f)
						collisionAt[POSY] = true;
					else
						collisionAt[NEGY] = true;
				}
				else
				{
					if (angle.z < 180.f && angle.x < 180.f)
						collisionAt[NEGY] = true;
					else
						collisionAt[POSY] = true;
				}
				penetration.y -= dimension.y / 2;
			}
		}
		else
		{
			break;
		}

		LHS = projPlane(T, Az).Length(); //Projection of T onto plane with normal Az
		RHS = projPlane(Ax * Wa, Ay).Length() + projPlane(Ay * Ha, Ay).Length() + projPlane(Az * Da, Ay).Length() +
			projPlane(Bx * Wb, Ay).Length() + projPlane(By * Hb, Ay).Length() + projPlane(Bz * Db, Ay).Length();
		if (LHS <= RHS)//if collision
		{
			if (RHS - LHS < 3)
			{
				if (T.z >= 0)
				{
					if (angle.y < 180.f)
						collisionAt[POSZ] = true;
					else
					{
						collisionAt[NEGZ] = true;
					}
				}
				else
				{
					if (angle.y < 180.f)
						collisionAt[NEGZ] = true;
					else
						collisionAt[POSZ] = true;
				}
				penetration.z -= dimension.z / 2;
			}
		}
		else
		{
			break;
		}

		//Checking by B

		LHS = projPlane(T, Bx).Length(); //Projection of T onto plane with normal Bx
		RHS = projPlane(Ax * Wa, Bx).Length() + projPlane(Ay * Ha, Bx).Length() + projPlane(Az * Da, Bx).Length() +
			projPlane(Bx * Wb, Bx).Length() + projPlane(By * Hb, Bx).Length() + projPlane(Bz * Db, Bx).Length();
		if (LHS <= RHS)//Collision
		{
			if (RHS - LHS < 3)
			{
				if (T.x <= 0)
				{
					if (b->angle.y < 180.f)
						b->collisionAt[POSX] = true;
					else
					{
						b->collisionAt[NEGX] = true;
					}
				}
				else
				{
					if (b->angle.y < 180.f)
						b->collisionAt[NEGX] = true;
					else
					{
						b->collisionAt[POSX] = true;
					}
				}
				penetration.x -= b->dimension.x / 2;
			}
		}
		else
		{
			break;
		}

		LHS = projPlane(T, By).Length(); //Projection of T onto plane with normal By
		RHS = projPlane(Ax * Wa, By).Length() + projPlane(By * Ha, By).Length() + projPlane(Az * Da, By).Length() +
			projPlane(Bx * Wb, By).Length() + projPlane(By * Hb, By).Length() + projPlane(Bz * Db, By).Length();
		if (LHS <= RHS)//Collision
		{
			if (RHS - LHS < 3)
			{
				if (T.y <= 0)
				{
					if (b->angle.y < 180.f)
						b->collisionAt[POSY] = true;
					else
					{
						b->collisionAt[NEGY] = true;
					}
				}
				else
				{
					if (b->angle.y < 180.f)
						b->collisionAt[NEGY] = true;
					else
					{
						b->collisionAt[POSY] = true;
					}
				}
				penetration.y -= b->dimension.y / 2;
			}
		}
		else
		{
			break;
		}

		LHS = projPlane(T, Bz).Length(); //Projection of T onto plane with normal Bz
		RHS = projPlane(Ax * Wa, Ay).Length() + projPlane(Ay * Ha, Ay).Length() + projPlane(Bz * Da, Ay).Length() +
			projPlane(Bx * Wb, Ay).Length() + projPlane(By * Hb, Ay).Length() + projPlane(Bz * Db, Ay).Length();
		if (LHS <= RHS)//Collision
		{
			if (RHS - LHS < 3)
			{
				if (T.z <= 0)
				{
					if (b->angle.y < 180.f)
						b->collisionAt[POSZ] = true;
					else
					{
						b->collisionAt[NEGZ] = true;
					}
				}
				else
				{
					if (b->angle.y < 180.f)
						b->collisionAt[NEGZ] = true;
					else
					{
						b->collisionAt[POSZ] = true;
					}
				}
				penetration.z -= b->dimension.z / 2;
			}
		}
		else
		{
			break;
		}

	{
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
			break;
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
			break;
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
			break;
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
			break;
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
			break;
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
			break;
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
			break;
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
			break;
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
			break;
		}
	}
		
		if (!b->isMovable())
		{
			Vector3 temp;
			Vector3 front, movementDir;	//vehicle fromt, direction of movement
			if (velocity != Vector3(0, 0, 0))
				movementDir = velocity.Normalized();

			if (b->collisionAt[POSX])
			{
				temp += Bx;
			}
			if (b->collisionAt[POSY])
			{
				temp += By;
			}
			if (b->collisionAt[POSZ])
			{
				temp += Bz;
			}
			if (b->collisionAt[NEGX])
			{
				temp -= Bx;
			}
			if (b->collisionAt[NEGY])
			{
				temp -= By;
			}
			if (b->collisionAt[NEGZ])
			{
				temp -= Bz;
			}

			if (temp.x < 0)
			{
				if (velocity.x > 0)
					velocity.x += temp.x * velocity.x;
			}
			else if (temp.x > 0)
			{
				if (velocity.x < 0)
					velocity.x -= temp.x * velocity.x;
			}

			if (temp.y < 0)
			{
				if (velocity.y > 0)
					velocity.y += temp.y * velocity.y;
			}
			else if (temp.y > 0)
			{
				if (velocity.y < 0)
					velocity.y -= temp.y * velocity.y;
			}

			if (temp.z < 0)
			{
				if (velocity.z > 0)
					velocity.z += temp.z * velocity.z;
			}
			else if (temp.z > 0)
			{
				if (velocity.z < 0)
					velocity.z -= temp.z * velocity.z;
			}

			//if (penetration.x < 0)
			//{
			//	translation.x -= penetration.x;
			//}
			//if (penetration.y > 0)
			//{
			//	translation.y -= penetration.y;
			//}
			if (penetration.x < penetration.y)
			{
				if (penetration.y < penetration.z)
				{
					if (penetration.z < 0)
					{
						if (collisionAt[POSZ])
							translation.z += penetration.z;
						else if (collisionAt[NEGZ])
							translation.z -= penetration.z;
					}
				}
				else
				{
					if (penetration.y < 0)
					{
						if (collisionAt[POSY])
							translation.y += penetration.y;
						else if (collisionAt[NEGY])
							translation.y -= penetration.y;
					}
				}
			}
			else if (penetration.x < penetration.z)
			{
				if (penetration.z < 0)
				{
					if (collisionAt[POSZ])
						translation.z += penetration.z;
					else if (collisionAt[NEGZ])
						translation.z -= penetration.z;
				}
			}
			else
			{
				if (collisionAt[POSX])
					translation.x += penetration.x;
				else if (collisionAt[NEGX])
					translation.x -= penetration.x;
			}

			
		}
		std::cout << "COLLISION\n";
		break;
	}
	moveBy(velocity.x, velocity.y, velocity.z);
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
