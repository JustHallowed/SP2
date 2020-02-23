#pragma once
#include "Object.h"
#include "Application.h"
#include "Camera.h"

class Vehicle
{
	Object* object;
	bool keyPress[6];
	enum KEYPRESS
	{
		W_KEY, A_KEY, S_KEY, D_KEY,SHIFT_KEY,SPACE_KEY,
	};
public:
	Vehicle();
	


	Object* getObject();

	void setObject(Object* object);

	void update(double dt);
};

