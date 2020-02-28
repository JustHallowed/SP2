#pragma once
#include "Object.h"
#include "Application.h"
#include "Camera.h"

class Vehicle
{
	Object* object;	//the object that the movement is applied to
	bool keyPress[6];	//key press detection
	bool disabledKey[6];
	bool keyPressed;//false if no user input
	bool isRotationMode; //driving mode
	bool animation;
public:
	enum KEYPRESS
	{
		W_KEY, A_KEY, S_KEY, D_KEY,SHIFT_KEY, SPACE_KEY,
	};
	Vehicle();
	
	Object* getObject();

	void setObject(Object* object,bool isRotationMode);

	void disableKey(int keyCode);
	void disableAnimation(bool animation);
	void update(double dt);
};

