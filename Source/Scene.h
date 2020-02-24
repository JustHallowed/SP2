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
	Mesh* textMesh;
	static char* typed;
public:
	Scene(){
		textMesh = MeshBuilder::GenerateText(16, 16);
		textMesh->textureID = LoadTGA("Resources/TGAs/FontOnScreen.tga");
		memset(Scene::getTyped(), '\0', 10);
	}
	virtual	~Scene(){
		delete textMesh;
	}
	Mesh* getTextMesh() const{
		return textMesh;
	}
	static char* getTyped(){
		return typed;
	}
	virtual void Init() = 0, Update(double, float) = 0, Render(double, int, int) = 0, Exit(Scene*) = 0;
};