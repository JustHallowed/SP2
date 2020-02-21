#pragma once
#include "Camera.h"

class Scene{
public:
	virtual	~Scene(){}
	virtual void Init() = 0, Update(double, float) = 0, Render(double, int, int) = 0, Exit(Scene*) = 0;
};