#pragma once
#include "Object.h"
#include "Application.h"
#include "Camera.h"

class Vehicle
{
	Object* object;	//the object that the movement is applied to
	bool keyPress[6];	//key press detection
	bool isRotationMode; //driving mode
	enum KEYPRESS
	{
		W_KEY, A_KEY, S_KEY, D_KEY,SHIFT_KEY,SPACE_KEY,
	};
public:
	Vehicle();
	


	Object* getObject();

	void setObject(Object* object,bool isRotationMode);

	void update(double dt);
};

