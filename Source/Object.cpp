#include "Object.h"

Object::Object()
{
	meshType = nullptr;
	parent = nullptr;
	pos.SetZero();
	translation.SetZero();
	angle.SetZero();
	scale.Set(1, 1, 1);
	dimension.SetZero();
	render = true;
	clockwise = false;
	parentRotation = false;
	parentScale = false;
	interactable = false;
}

Object::~Object()
{
}

void Object::setPos(float x, float y, float z)
{
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
void Object::setRotation(float angle, char axis)
{
	if (axis == 'x')
		this->angle.x = angle;
	else
	if (axis == 'y')
		this->angle.y = angle;
	else
	if (axis == 'z')
		this->angle.z = angle;
}
void Object::addRotation(float angle, char axis)
{
	if (axis == 'x')
		this->angle += angle;
	if (axis == 'y')
		this->angle.y += angle;
	if (axis == 'z')
		this->angle.z += angle;
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
	dimension.x = x;
	dimension.y = y;
	dimension.z = z;
}
void Object::setIsClockwise(bool boolean)
{
	clockwise = boolean;
}

void Object::setRender(bool render)//set if is object rendered in the scene
{
	this->render = render;
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
bool Object::isRender()
{
	return render;
}
void Object::setInteractable(bool canInteract)
{
	interactable = canInteract;
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

float Object::getDist(Vector3 playerpos)
{
	float x = pow(pos.x - playerpos.x, 2.0);
	float z = pow(pos.z - playerpos.z, 2.0);
	return sqrt(x + z);
}

float Object::getAngle(Vector3 A, Vector3 B)
{
	float dot = A.x * B.x + A.y * B.y + A.z * B.z;
	float ptoMagnitude = sqrt(pow(A.x, 2.0) + pow(A.y, 2.0) + pow(A.z, 2.0));
	float pttMagnitude = sqrt(pow(B.x, 2.0) + pow(B.y, 2.0) + pow(B.z, 2.0));
	return acos(dot / (ptoMagnitude * pttMagnitude));
}
