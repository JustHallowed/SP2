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
	int keyCode[6];
public:
	enum KEYPRESS
	{
		FRONT_KEY, LEFT_KEY, BACK_KEY, RIGHT_KEY,UP_KEY, DOWN_KEY,
	};
	Vehicle();
	
	Object* getObject();

	void setObject(Object* object,bool isRotationMode);
	void setKeys(int FRONT, int LEFT, int BACK, int RIGHT, int UP, int DOWN);
	void disableKey(int keyCode);
	void disableAnimation(bool animation);
	void update(double dt);
};

