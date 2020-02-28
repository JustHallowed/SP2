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
	enum DIRECTION {
		POSX, POSY, POSZ, NEGX, NEGY, NEGZ,
	};
	//////////////////////////////////////////////DONT'T//TOUCH//////////////////////////////////////////////////////////
	void unbindChild(Object* child);//removes child from child vector
	void findCollisionDirection(Object* b, Vector3* uniqueAxisA, Vector3* uniqueAxisB);
	bool hasFaceIntersection(Object* b, float* greatestFaceIntersectionA, Vector3* collidingFaceAxisA,
		float* greatestFaceIntersectionB, Vector3* collidingFaceAxisB, Vector3* penetration);
	bool hasEdgeIntersection(Object* b);
	//////////////////////////////////////////////DONT'T//TOUCH//////////////////////////////////////////////////////////
public:
	bool collisionAt[6];//which axis the object can be displaced
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
	void resetCollision();

	//getters
	Mesh* getMesh(); //returns meshtype from meshlist
	Vector3 getPos();
	Vector3 getTranslation();
	Vector3 getAngle();
	Vector3 getScale();
	Vector3 getDimension();
	Vector3 getVelocity();
	Vector3 getAcceleration();
	Object* getParent();
	std::vector<Object*> getChild();
	bool isClockwise();
	bool followParentRotation();
	bool followParentScale();
	bool isInteractable();
	bool isRender();
	bool isMovable();

	Vector3 projPlane(Vector3 vector, Vector3 planeNormal);
	bool updateCollision(Object* b,double dt);	//check for collision (run resetCollision() before running this in aloop)
	static void bind(Object* parent, Object* child, bool followParentRotation, bool followParentScale);//binds two objects
	//unbinds child from parent
	static void unbind(Object* child);
	float checkDist(Vector3 playerpos);
	float getAngle(Vector3 A, Vector3 B);
};

