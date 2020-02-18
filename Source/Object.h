#pragma once
#include "vertex.h"
#include <vector>
#include "Mesh.h"
#include <Mtx44.h>
class Object
{
	Mesh* meshType;//Stores meshtype

	Vector3 pos; //Object's position relative to map
	Vector3 translation;//translation relative to parent 
	Vector3 angle; //angle of rotation for each axis
	Vector3 scale;//scale of object
	Vector3 dimension; //dimensions of object
	Object* parent; // parent of object
	std::vector<Object*> child;//list of children
	bool clockwise;//controls rotation
	bool parentRotation;//whether object rotates with parent
	bool parentScale; //whether object scale with parent
	bool interactable; //whether object can be interacted
	bool render; //where object is rendered
public:
	Object();
	//setters
	void setPos(float x, float y, float z);
	void setTranslation(float x, float y, float z);
	void setRotation(float angle, char axis);
	void setScale(float x, float y, float z);
	void setScale(float scale);
	void setDimension(float x, float y, float z);
	void setMesh(Mesh* mesh);
	void setMesh(Mesh* mesh, Object parent, Vector3 translation);
	void setMesh(Mesh* mesh, Object* parent);
	void setMesh(Mesh* mesh, Vector3 translation);
	void setParent(Object* parent);
	void setChild(Object* child);
	void addRotation(float angle, char axis);//increments angle
	void setIsClockwise(bool boolean);//set rotation direction
	void setRender(bool render);

	//getters
	bool isClockwise();
	bool followParentRotation();
	bool followParentScale();
	bool isInteractable();
	bool isRender();

	Object* getParent();
	std::vector<Object*> getChild();
	Vector3 getAngle();
	Vector3 getPos();
	Vector3 getTranslation();
	Vector3 getScale();
	Mesh* getMesh(); //returns meshtype from meshlist
	Vector3 getDimension();
	void setInteractable(bool canInteract);
	void unbindChild(Object* child);//removes child from child vector
	//binds two objects
	static void bind(Object* parent, Object* child, bool followParentRotation, bool followParentScale);
	//unbinds child from parent
	static void unbind(Object* child);
};

