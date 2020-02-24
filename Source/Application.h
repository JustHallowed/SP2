#pragma once
#include <MatrixStack.h>
#include "Mesh.h"
#include <GL/glew.h>
#include "ShaderManager.hpp"
#include <GLFW/glfw3.h>
#include "timer.h"
#include "MeshBuilder.h"
#include "LoadTGA.hpp"

class Application final{ //Singleton
	Application();
	static Application* app;
	void IRun();
public:
	Application(Application const&) = delete; //Delete copy ctor
	Application(Application&&) = delete; //Delete move ctor
	Application& operator=(Application const&) = delete; //Delete copy assignment operator
	Application& operator=(Application&&) = delete; //Delete move assignment operator
	~Application();
	static Application* getApp();
	static bool IsKeyPressed(unsigned short);
	static void Run();
	bool fullscreen;
	const GLFWvidmode* mode;
	StopWatch m_timer;
};