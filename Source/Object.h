#pragma once
#include "vertex.h"
#include <vector>
#include "Mesh.h"
#include <Mtx44.h>
class Object
{
protected:
	Mesh* meshType;//Stores meshtype

	Vector3 pos; //Object's position relative to map
	Vector3 translation;//translation relative to parent 
	Vector3 angle; //angle of rotation for each axis
	Vector3 scale;//scale of object
	Vector3 dimension; //dimensions of the object
	Vector3 velocity;
	Vector3 acceleration;
	Object* parent; // parent of object
	std::vector<Object*> child;//list of children
	bool clockwise;//controls rotation
	bool parentRotation;//whether object rotates with parent
	bool parentScale; //whether object scale with parent
	bool interactable; //whether object can be interacted
	bool render; //where object is rendered
	bool movable;//if object can be displaced by other objects
	bool hasMoved;//if object moved this frame
	bool grounded; //if object is on the ground
	bool gravity;
	//////////////////////////////////////////////DONT'T//TOUCH//////////////////////////////////////////////////////////
	void unbindChild(Object* child);//removes child from child vector
	void findCollisionDirection(Object* b, Vector3* uniqueAxisA, Vector3* uniqueAxisB);
	bool hasFaceIntersection(Object* b, float* greatestFaceIntersectionA, Vector3* collidingFaceAxisA,
	float* greatestFaceIntersectionB, Vector3* collidingFaceAxisB, Vector3* penetration, Vector3* rotationAxis);
	bool hasEdgeIntersection(Object* b);
	//////////////////////////////////////////////DONT'T//TOUCH//////////////////////////////////////////////////////////
public:
	Object();
	~Object();
	//setters
	void setPos(float x, float y, float z);
	void setTranslation(float x, float y, float z);
	void moveBy(float x, float y, float z);
	void setRotation(float angle, char axis);
	void setScale(float x, float y, float z);
	void setScale(float scale);
	void setDimension(float x, float y, float z);
	void setVelocity(Vector3 velocity);
	void setAcceleration(Vector3 acceleration);
	void setVelocity(float x, float y, float z);
	void setAcceleration(float x, float y, float z);
	void setMesh(Mesh* mesh);
	void setMesh(Mesh* mesh, Object parent, Vector3 translation);
	void setMesh(Mesh* mesh, Object* parent);
	void setMesh(Mesh* mesh, Vector3 translation);
	void setParent(Object* parent);
	void setChild(Object* child);
	void addRotation(float angle, char axis);//increments angle
	void setIsClockwise(bool boolean);//set rotation direction
	void setInteractable(bool canInteract);
	void setRender(bool render);
	void setMovable(bool movable);
	void resetCollision();//run this before looping update()
	void updatePosition(double dt);//updates translation and gravity
	void setHasGravity(bool hasGravity);

	//getters
	Mesh* getMesh()const; //returns meshtype from meshlist
	Vector3 getPos()const;
	Vector3 getTranslation()const;
	Vector3 getAngle()const;
	Vector3 getScale()const;
	Vector3 getDimension()const;
	Vector3 getVelocity()const;
	Vector3 getAcceleration()const;
	Object* getParent()const;
	std::vector<Object*> getChild()const;
	bool isClockwise()const;
	bool followParentRotation()const;
	bool followParentScale()const;
	bool isInteractable()const;
	bool isRender()const;
	bool isMovable()const;
	bool isGrounded()const;
	bool hasGravity()const;

	Vector3 projPlane(Vector3 vector, Vector3 planeNormal)const;
	bool updateCollision(Object* b,double dt);	//check for collision (run resetCollision() before running this in aloop)
	static void bind(Object* parent, Object* child, bool followParentRotation, bool followParentScale);//binds two objects
	//unbinds child from parent
	static void unbind(Object* child);
	float getAngle(Vector3 A, Vector3 B)const;
	float checkDist(Vector3 playerpos)const;
};

