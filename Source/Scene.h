#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include "GL\glew.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.hpp"
#include "MainChar.h"
#include "Camera.h"

class Scene{
public:
	virtual	~Scene(){}
	virtual void Init() = 0, Update(double, float) = 0, Render(double, int, int) = 0, Exit(Scene*) = 0;
};