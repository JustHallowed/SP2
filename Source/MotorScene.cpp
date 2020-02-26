#include <iostream>
#include <iomanip>
#include <sstream>
#include "MotorScene.h"
#include "GameScene.h"
#include "GL\glew.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.hpp"
#include "SceneManager.h"
#include "irrKlang.h"
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

extern double elapsedTime;

using namespace irrklang;
ISoundEngine* engine = createIrrKlangDevice();

double MotorScene::CalcFrameRate() const{
	static double FPS, FramesPerSecond = 0.0, lastTime = 0.0;
	double valueFPS, currTime = GetTickCount64() * 0.001;
	++FramesPerSecond;
	valueFPS = FPS;
	if(currTime - lastTime > 1.0){
		lastTime = currTime;
		FPS = double(FramesPerSecond);
		FramesPerSecond = 0.0;
	}
	return valueFPS;
}

void MotorScene::InitLight() const{
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lights[0].type"), GLint(light[0].type));
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[0].color"), 1, &light[0].color.R);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].power"), light[0].power);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].kC"), light[0].kC);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].kL"), light[0].kL);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].kQ"), light[0].kQ);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[0].spotDirection"), 1, &light[0].spotDirection.x);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].cosCutoff"), light[0].cosCutoff);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].cosInner"), light[0].cosInner);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].exponent"), light[0].exponent);

	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lights[1].type"), GLint(light[1].type));
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[1].color"), 1, &light[1].color.R);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].power"), light[1].power);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].kC"), light[1].kC);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].kL"), light[1].kL);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].kQ"), light[1].kQ);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[1].spotDirection"), 1, &light[1].spotDirection.x);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].cosCutoff"), light[1].cosCutoff);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].cosInner"), light[1].cosInner);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].exponent"), light[1].exponent);

	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lights[2].type"), GLint(light[2].type));
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[2].color"), 1, &light[2].color.R);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].power"), light[2].power);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].kC"), light[2].kC);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].kL"), light[2].kL);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].kQ"), light[2].kQ);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[2].spotDirection"), 1, &light[2].spotDirection.x);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].cosCutoff"), light[2].cosCutoff);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].cosInner"), light[2].cosInner);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].exponent"), light[2].exponent);

	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lights[3].type"), GLint(light[3].type));
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[3].color"), 1, &light[3].color.R);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].power"), light[3].power);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].kC"), light[3].kC);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].kL"), light[3].kL);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].kQ"), light[3].kQ);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[3].spotDirection"), 1, &light[3].spotDirection.x);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].cosCutoff"), light[3].cosCutoff);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].cosInner"), light[3].cosInner);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].exponent"), light[3].exponent);

	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lights[4].type"), GLint(light[4].type));
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[4].color"), 1, &light[4].color.R);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].power"), light[4].power);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].kC"), light[4].kC);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].kL"), light[4].kL);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].kQ"), light[4].kQ);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[4].spotDirection"), 1, &light[4].spotDirection.x);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].cosCutoff"), light[4].cosCutoff);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].cosInner"), light[4].cosInner);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].exponent"), light[4].exponent);

	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lights[5].type"), GLint(light[5].type));
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[5].color"), 1, &light[5].color.R);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].power"), light[5].power);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].kC"), light[5].kC);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].kL"), light[5].kL);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].kQ"), light[5].kQ);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[5].spotDirection"), 1, &light[5].spotDirection.x);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].cosCutoff"), light[5].cosCutoff);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].cosInner"), light[5].cosInner);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].exponent"), light[5].exponent);

	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lights[6].type"), GLint(light[6].type));
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[6].color"), 1, &light[6].color.R);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].power"), light[6].power);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].kC"), light[6].kC);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].kL"), light[6].kL);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].kQ"), light[6].kQ);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[6].spotDirection"), 1, &light[6].spotDirection.x);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].cosCutoff"), light[6].cosCutoff);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].cosInner"), light[6].cosInner);
	glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].exponent"), light[6].exponent);

	glUniform1i(glGetUniformLocation(shMan->getProgID(), "numLights"), 7);
}

void MotorScene::InitMeshes(){
	meshList[unsigned int(MESH::HITBOXWHITE)] = MeshBuilder::GenerateCuboid(Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);
	meshList[unsigned int(MESH::HITBOXRED)] = MeshBuilder::GenerateCuboid(Color(1, 0, 0), 1.1f, 1.1f, 1.1f);
	meshList[unsigned int(MESH::BULLET)] = MeshBuilder::GenerateCuboid(Color(1.f, 0.f, 0.f), .4f, .4f, .4f);
	meshList[unsigned int(MESH::LEFT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::LEFT)]->textureID = LoadTGA("Resources/TGAs/skybox.tga");
	meshList[unsigned int(MESH::RIGHT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::RIGHT)]->textureID = LoadTGA("Resources/TGAs/skybox.tga");
	meshList[unsigned int(MESH::FRONT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::FRONT)]->textureID = LoadTGA("Resources/TGAs/skybox.tga");
	meshList[unsigned int(MESH::BACK)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::BACK)]->textureID = LoadTGA("Resources/TGAs/skybox.tga");
	meshList[unsigned int(MESH::TOP)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::TOP)]->textureID = LoadTGA("Resources/TGAs/skybox.tga");
	meshList[unsigned int(MESH::BOTTOM)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::BOTTOM)]->textureID = LoadTGA("Resources/TGAs/skybox.tga");
	meshList[unsigned int(MESH::LIGHT_SPHERE)] = MeshBuilder::GenerateSphere(Color(1.f, 1.f, 1.f), 9, 36, 1.f);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)] = MeshBuilder::GenerateText(16, 16);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)]->textureID = LoadTGA("Resources/TGAs/FontOnScreen.tga");
	meshList[unsigned int(MESH::TEXTBOX)] = MeshBuilder::GenerateQuad(Color(1.f,1.f,1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::TEXTBOX)]->textureID = LoadTGA("Resources/TGAs/dialogue.tga");

	//5 ufos
	meshList[unsigned int(MESH::UFO_BASE)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	meshList[unsigned int(MESH::UFO_BASE)]->textureID = LoadTGA("Resources/TGAs/ufo_base.tga");
	meshList[unsigned int(MESH::UFO_PURPLE)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	meshList[unsigned int(MESH::UFO_PURPLE)]->textureID = LoadTGA("Resources/TGAs/ufo_1.tga");
	meshList[unsigned int(MESH::UFO_RED)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	meshList[unsigned int(MESH::UFO_RED)]->textureID = LoadTGA("Resources/TGAs/ufo_2.tga");
	meshList[unsigned int(MESH::UFO_BLUE)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	meshList[unsigned int(MESH::UFO_BLUE)]->textureID = LoadTGA("Resources/TGAs/ufo_6.tga");
	meshList[unsigned int(MESH::UFO_PINK)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	meshList[unsigned int(MESH::UFO_PINK)]->textureID = LoadTGA("Resources/TGAs/ufo_7.tga");

	//normal vehicles
	meshList[unsigned int(MESH::GY_CAR)] = MeshBuilder::GenerateOBJ("Resources/OBJs/guanyu_car.obj");
	meshList[unsigned int(MESH::GY_CAR)]->textureID = LoadTGA("Resources/TGAs/guanyu_car.tga");
	meshList[unsigned int(MESH::EH_CAR)] = MeshBuilder::GenerateOBJ("Resources/OBJs/enhui_car.obj");
	meshList[unsigned int(MESH::EH_CAR)]->textureID = LoadTGA("Resources/TGAs/enhui_car.tga");
	meshList[unsigned int(MESH::LF_CAR)] = MeshBuilder::GenerateOBJ("Resources/OBJs/loopy_vehicle.obj");
	meshList[unsigned int(MESH::LF_CAR)]->textureID = LoadTGA("Resources/TGAs/loopy_vehicle.tga");
	meshList[unsigned int(MESH::YW_CAR)] = MeshBuilder::GenerateOBJ("Resources/OBJs/yuwei_car.obj");
	meshList[unsigned int(MESH::YW_CAR)]->textureID = LoadTGA("Resources/TGAs/yuwei_car.tga");

	//base mesh
	meshList[unsigned int(MESH::PLATFORM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/platform.obj");
	meshList[unsigned int(MESH::PLATFORM)]->textureID = LoadTGA("Resources/TGAs/platform.tga");

	//base mesh
	meshList[unsigned int(MESH::ROBOT_BODY)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_body.obj");
	meshList[unsigned int(MESH::ROBOT_BODY)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
	meshList[unsigned int(MESH::ROBOT_ARM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_arm.obj");
	meshList[unsigned int(MESH::ROBOT_ARM)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
	meshList[unsigned int(MESH::ROBOT_FOREARM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_forearm.obj");
	meshList[unsigned int(MESH::ROBOT_FOREARM)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
	meshList[unsigned int(MESH::ROBOT_UPPERLEG)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_upperleg.obj");
	meshList[unsigned int(MESH::ROBOT_UPPERLEG)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
	meshList[unsigned int(MESH::ROBOT_LOWERLEG)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_lowerleg.obj");
	meshList[unsigned int(MESH::ROBOT_LOWERLEG)]->textureID = LoadTGA("Resources/TGAs/robot.tga");

	meshList[unsigned int(MESH::STAGE)] = MeshBuilder::GenerateOBJ("Resources/OBJs/stage.obj");
	meshList[unsigned int(MESH::STAGE)]->textureID = LoadTGA("Resources/TGAs/stage.tga");

	meshList[unsigned int(MESH::SPEAKER)] = MeshBuilder::GenerateOBJ("Resources/OBJs/speaker.obj");
	meshList[unsigned int(MESH::SPEAKER)]->textureID = LoadTGA("Resources/TGAs/speaker.tga");
}

void MotorScene::CreateInstances()
{
	//create instances for platforms
	createPlatforms();

	//create instances for ufos
	createUFOs();

	createRobot1();
	createRobot2();
	createRobot3();

	createVehicles();
	createStage();
	createSpeaker();

}

void MotorScene::Init(){ //Init scene
	glGenVertexArrays(1, &m_vertexArrayID); //Generate a default VAO
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_CULL_FACE); //Enable back-face culling
	glEnable(GL_BLEND); //Enable blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST); //Enable depth test
	shMan = new ShaderManager("Resources/Shaders/Regular.vs", "Resources/Shaders/Regular.fs");
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	Camera::getCam().Init(Vector3(0.f, 40.f, -30.f), Vector3(0.f, 35.f, 0.f), Vector3(0.f, 1.f, 0.f));
	InitLight();
	InitMeshes();
	CreateInstances();
	bulletGenerator.InitParticles();
	showDebugInfo = 1;
	showLightSphere = 0;
	splitScreen = 0;
	bulletBounceTime = debugBounceTime = lightBounceTime = interactBounceTime = splitBounceTime = 0.0;
	inRange[ROBOT_BODY1] = 0;
	interacted[ROBOT_BODY1] = 0;
	light[0].power = 1.f;
	//play thru out the scene and loops
	//engine->play2D("Resources/Sound/bgm.mp3", true);
}

void MotorScene::Exit(Scene* newScene){ //Exit scene
	for(int i = 0; i < int(MESH::NUM_GEOMETRY); ++i){
		if(meshList[i] != 0){
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	delete shMan;
	if(dynamic_cast<MotorScene*>(newScene) != this){
		newScene->Init();
	}
	engine->drop();
}

void MotorScene::Update(double dt, float FOV) { //Update scene
	for (int i = 0; i < 7; ++i) {
		if (Application::IsKeyPressed(keys[i])) {
			switch (keys[i]) {
			case '1': glDisable(GL_CULL_FACE); break; //Disable back-face culling
			case '2': glEnable(GL_CULL_FACE); break; //Enable back-face culling
			case '3': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break; //Set polygon mode to GL_FILL (default mode)
			case '4': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break; //Set polygon mode to GL_LINE (wireframe mode)
			case '8': { //Off the light
				light[0].power = 0.f;
				glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].power"), light[0].power);
				break;
			}
			case '9': { //On the light
				light[0].power = 1.f;
				glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[0].power"), light[0].power);
				break;
			}
			case '0': SceneManager::getScMan()->SetNextScene(); //Change scene
			}
		}
	}
	if (Application::IsKeyPressed('P') && lightBounceTime <= elapsedTime) { //Show/Hide light sphere
		showLightSphere = !showLightSphere;
		lightBounceTime = elapsedTime + 0.4;
	}
	if (Application::IsKeyPressed(VK_SHIFT) && debugBounceTime <= elapsedTime) { //Show/Hide debug info
		showDebugInfo = !showDebugInfo;
		debugBounceTime = elapsedTime + 0.5;
	}

	if (bulletBounceTime <= elapsedTime && bulletGenerator.currAmt < bulletGenerator.maxAmt) {
		Particle* p = bulletGenerator.particlePool[bulletGenerator.GetIndex()];
		p->color = Color(1.f, 0.f, 0.f);
		p->dir = Vector3(0, 1, 0);
		p->life = 1.f;
		p->pos = Vector3(0, 0, 0) + p->dir * 2.5f + Vector3(0.f, 7.5f, 0.f);
		++bulletGenerator.currAmt;
		bulletBounceTime = elapsedTime + 0.2;
	}
	bulletGenerator.UpdateParticles(dt);

	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		object[i].resetCollision();
	}

	//for (int j = 0; j < NUM_INSTANCES; ++j)//update all collisions of objects in scene
	//{
	//	if (object[j].getDimension().y == 0)
	//		continue;
	//	for (int i = 0; i < NUM_INSTANCES; ++i)
	//	{
	//		if (i < j)
	//			i = j + 1;
	//		if (object[i].getDimension().y == 0)
	//			continue;
	//		object[j].updateCollision(&object[i], dt);
	//	}
	//}

	object[PLATFORM1].addRotation(1, 'y');

	if (Application::IsKeyPressed('G') && splitBounceTime <= elapsedTime)
	{
		splitScreen = !splitScreen;
		splitBounceTime = elapsedTime + 0.4;
	}

	if (Application::IsKeyPressed('E'))
	{
		SceneManager::getScMan()->AddScene(new GameScene);
	}



	//!testing! if w is pressed, sound effects will be played
	//if (Application::IsKeyPressed('W'))
	//	engine->play2D("Resources/Sound/bell.wav");

	npcCheck(ROBOT_BODY1, "Resources/Sound/robot1.wav");
	npcCheck(ROBOT_BODY3, "Resources/Sound/robot1.wav");
	npcCheck(ROBOT_BODY2, "Resources/Sound/robot2.wav");
	carCheck(PLATFORM7, "Resources/Sound/engine.mp3");
	carCheck(PLATFORM8, "Resources/Sound/carchime.mp3");
	carCheck(PLATFORM9, "Resources/Sound/carkey.mp3");

	Mtx44 projection;
	projection.SetToPerspective(FOV, 4.f / 3.f, 0.1f, 1000.f); //FOV value affects cam zoom
	projectionStack.LoadMatrix(projection);
}

void MotorScene::Render(double dt, int winWidth, int winHeight) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (splitScreen)
	{
		glViewport(winWidth / 4, winHeight / 2, winWidth / 2, winHeight / 2);
		RenderScreen1(dt, winWidth, winHeight);
		glViewport(winWidth / 4, 0, winWidth / 2, winHeight / 2);
		RenderScreen2(dt, winWidth, winHeight);
	}
	else
	{
		glViewport(0, 0, winWidth, winHeight);
		RenderScreen1(dt, winWidth, winHeight);
	}
}

void MotorScene::RenderScreen1(double dt, int winWidth, int winHeight)
{
	viewStack.LoadIdentity();
	viewStack.LookAt(Camera::getCam().pos.x, Camera::getCam().pos.y, Camera::getCam().pos.z,
		Camera::getCam().target.x, Camera::getCam().target.y, Camera::getCam().target.z,
		Camera::getCam().up.x, Camera::getCam().up.y, Camera::getCam().up.z);
	modelStack.LoadIdentity();

	delete shMan;
	shMan = new ShaderManager("Resources/Shaders/Particle.vs", "Resources/Shaders/Particle.fs");
	/*for(Particle* p: bulletGenerator.particlePool){
		if(p->life > 0.0f){
			delete meshList[unsigned int(MESH::BULLET)];
			meshList[unsigned int(MESH::BULLET)] = MeshBuilder::GenerateCuboid(p->color, .4f, .4f, .4f);
			modelStack.PushMatrix();
				modelStack.Translate(p->pos.x, p->pos.y, p->pos.z);
				RenderParticle(meshList[unsigned int(MESH::BULLET)], p->life);
			modelStack.PopMatrix();
		}
	}*/

	delete shMan;
	shMan = new ShaderManager("Resources/Shaders/Regular.vs", "Resources/Shaders/Regular.fs");
	InitLight();
	RenderLight();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 100.f, 0.f);
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderSkybox(!light[0].power);
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(Camera::getCam().target.x, Camera::getCam().target.y, Camera::getCam().target.z);
	//RenderMesh(meshList[unsigned int(MESH::HITSPHERE)], false);
	//modelStack.PopMatrix();

	//displays hitboxes
	//for (int i = 0; i < NUM_INSTANCES; ++i)
	//{
	//	if (object[i].getDimension().y > 0)
	//	{
	//	modelStack.PushMatrix();
	//	modelStack.Translate(object[i].getPos().x, object[i].getPos().y, object[i].getPos().z);
	//	modelStack.Scale(object[i].getDimension().x, object[i].getDimension().y, object[i].getDimension().z);
	//	RenderMesh(meshList[unsigned int(MESH::HITBOXWHITE)], false);
	//	modelStack.PopMatrix();
	//	}
	//}
	//render all objects
	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		if (object[i].getParent() == nullptr)
		{
			modelStack.PushMatrix();
			renderObject(&object[i]);
			modelStack.PopMatrix();
		}
	}

	std::ostringstream ss;
	if (showDebugInfo) {
		ss << std::fixed << std::setprecision(2);
		ss << "Cam target: " << Camera::getCam().target.x << ", " << Camera::getCam().target.y << ", " << Camera::getCam().target.z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 29.f, winWidth, winHeight);
		ss.str("");
		ss << "Cam pos: " << Camera::getCam().pos.x << ", " << Camera::getCam().pos.y << ", " << Camera::getCam().pos.z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 28.f, winWidth, winHeight);
		ss.str("");
		ss << std::setprecision(3);
		ss << "Elapsed: " << elapsedTime;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 1.f, winWidth, winHeight);
		ss.str("");
		ss << "FPS: " << (1.0 / dt + CalcFrameRate()) / 2.0;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 0.f, winWidth, winHeight);
		ss.str("");
	}
	RenderMeshOnScreen(meshList[unsigned int(MESH::LIGHT_SPHERE)], 15.f, 15.f, 2.f, 2.f, winWidth, winHeight);

	if (inRange[PLATFORM7] && !interacted[PLATFORM7] || inRange[PLATFORM8] && !interacted[PLATFORM8] || inRange[PLATFORM9] && !interacted[PLATFORM9])
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], "Press [E] to interact", Color(0.5f, 0.5, 1.f), 4.f, 6.f, 8.f, winWidth, winHeight);

	if (inRange[ROBOT_BODY1] && !interacted[ROBOT_BODY1] || inRange[ROBOT_BODY2] && !interacted[ROBOT_BODY2] || inRange[ROBOT_BODY3] && !interacted[ROBOT_BODY3])
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], "Press [E] to talk", Color(0.5f, 0.5, 1.f), 4.f, 8.f, 8.f, winWidth, winHeight);

	if (inRange[ROBOT_BODY1] && interacted[ROBOT_BODY1])
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RenderMeshOnScreen(meshList[unsigned int(MESH::TEXTBOX)], 60.f, 20.f, 80.f, 20.f, winWidth, winHeight);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ss << "Wow! These cars! ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 6.f, winWidth, winHeight);
		ss.str("");
		ss << "They're awesome!";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 5.f, winWidth, winHeight);
		ss.str("");
	}
	if (inRange[ROBOT_BODY2] && interacted[ROBOT_BODY2])
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RenderMeshOnScreen(meshList[unsigned int(MESH::TEXTBOX)], 60.f, 20.f, 80.f, 20.f, winWidth, winHeight);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ss << "My son just ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 6.f, winWidth, winHeight);
		ss.str("");
		ss << "LOVES vehicles!";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 5.f, winWidth, winHeight);
		ss.str("");
	}
	if (inRange[ROBOT_BODY3] && interacted[ROBOT_BODY3])
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RenderMeshOnScreen(meshList[unsigned int(MESH::TEXTBOX)], 60.f, 20.f, 80.f, 20.f, winWidth, winHeight);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ss << "I am thorougly ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 6.f, winWidth, winHeight);
		ss.str("");
		ss << "displeased, ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 5.f, winWidth, winHeight);
		ss.str("");
		ss << "Mother.";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 4.f, winWidth, winHeight);
		ss.str("");
	}
}

void MotorScene::RenderScreen2(double dt, int winWidth, int winHeight)
{
	viewStack.LoadIdentity();
	viewStack.LookAt(Camera::getCam().pos.x, Camera::getCam().pos.y, Camera::getCam().pos.z,
		Camera::getCam().target.x, Camera::getCam().target.y, Camera::getCam().target.z,
		Camera::getCam().up.x, Camera::getCam().up.y, Camera::getCam().up.z);
	modelStack.LoadIdentity();

	delete shMan;
	shMan = new ShaderManager("Resources/Shaders/Particle.vs", "Resources/Shaders/Particle.fs");
	/*for(Particle* p: bulletGenerator.particlePool){
		if(p->life > 0.0f){
			delete meshList[unsigned int(MESH::BULLET)];
			meshList[unsigned int(MESH::BULLET)] = MeshBuilder::GenerateCuboid(p->color, .4f, .4f, .4f);
			modelStack.PushMatrix();
				modelStack.Translate(p->pos.x, p->pos.y, p->pos.z);
				RenderParticle(meshList[unsigned int(MESH::BULLET)], p->life);
			modelStack.PopMatrix();
		}
	}*/

	delete shMan;
	shMan = new ShaderManager("Resources/Shaders/Regular.vs", "Resources/Shaders/Regular.fs");
	InitLight();
	RenderLight();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 100.f, 0.f);
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderSkybox(!light[0].power);
	modelStack.PopMatrix();

	//displays hitboxes
	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		if (object[i].getDimension().y > 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(object[i].getPos().x, object[i].getPos().y, object[i].getPos().z);
			modelStack.Rotate(object[i].getAngle().z, 0, 0, 1);
			modelStack.Rotate(object[i].getAngle().y, 0, 1, 0);
			modelStack.Rotate(object[i].getAngle().x, 1, 0, 0);
			modelStack.Scale(object[i].getDimension().x, object[i].getDimension().y, object[i].getDimension().z);
			RenderMesh(meshList[unsigned int(MESH::HITBOXWHITE)], false);
			modelStack.PopMatrix();
		}
	}
	//render all objects
	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		if (object[i].getParent() == nullptr)
		{
			modelStack.PushMatrix();
			renderObject(&object[i]);
			modelStack.PopMatrix();
		}
	}

	std::ostringstream ss;
	if (showDebugInfo) {
		ss << std::fixed << std::setprecision(2);
		ss << "Cam target: " << Camera::getCam().target.x << ", " << Camera::getCam().target.y << ", " << Camera::getCam().target.z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 29.f, winWidth, winHeight);
		ss.str("");
		ss << "Cam pos: " << Camera::getCam().pos.x << ", " << Camera::getCam().pos.y << ", " << Camera::getCam().pos.z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 28.f, winWidth, winHeight);
		ss.str("");
		ss << std::setprecision(3);
		ss << "Elapsed: " << elapsedTime;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 1.f, winWidth, winHeight);
		ss.str("");
		ss << "FPS: " << (1.0 / dt + CalcFrameRate()) / 2.0;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 0.f, winWidth, winHeight);
		ss.str("");
	}
	RenderMeshOnScreen(meshList[unsigned int(MESH::LIGHT_SPHERE)], 15.f, 15.f, 2.f, 2.f, winWidth, winHeight);

	//if (inRange[ROBOT_BODY1] && !interacted[ROBOT_BODY1] || inRange[ROBOT_BODY2] && !interacted[ROBOT_BODY2] || inRange[ROBOT_BODY3] && !interacted[ROBOT_BODY3])
	if (inRange[ROBOT_BODY1] && !interacted[ROBOT_BODY1]);
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], "Press [E] to talk", Color(0.5f, 0.5, 1.f), 4.f, 8.f, 8.f, winWidth, winHeight);
	if (inRange[ROBOT_BODY1] && interacted[ROBOT_BODY1])
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RenderMeshOnScreen(meshList[unsigned int(MESH::TEXTBOX)], 60.f, 20.f, 80.f, 20.f, winWidth, winHeight);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ss << "Wow! These cars! ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 6.f, winWidth, winHeight);
		ss.str("");
	}
	RenderMeshOnScreen(meshList[unsigned int(MESH::LIGHT_SPHERE)], 15.f, 15.f, 2.f, 2.f, winWidth, winHeight);  

	if (inRange[ROBOT_BODY1] && !interacted[ROBOT_BODY1])
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], "Press [E] to talk", Color(0.5f,0.5,1.f), 4.f, 8.f, 8.f, winWidth, winHeight);
	if (inRange[ROBOT_BODY1] && interacted[ROBOT_BODY1])
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RenderMeshOnScreen(meshList[unsigned int(MESH::TEXTBOX)], 60.f, 20.f, 80.f, 20.f, winWidth, winHeight);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ss << "Wow! These cars! ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 6.f, winWidth, winHeight);
		ss.str("");
		ss << "They're awesome!";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 5.f, winWidth, winHeight);
		ss.str("");
	}
	if (inRange[ROBOT_BODY2] && interacted[ROBOT_BODY2])
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RenderMeshOnScreen(meshList[unsigned int(MESH::TEXTBOX)], 60.f, 20.f, 80.f, 20.f, winWidth, winHeight);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ss << "My son just ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 6.f, winWidth, winHeight);
		ss.str("");
		ss << "LOVES vehicles!";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 5.f, winWidth, winHeight);
		ss.str("");
	}
	if (inRange[ROBOT_BODY3] && interacted[ROBOT_BODY3])
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RenderMeshOnScreen(meshList[unsigned int(MESH::TEXTBOX)], 60.f, 20.f, 80.f, 20.f, winWidth, winHeight);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ss << "I am thorougly ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 6.f, winWidth, winHeight);
		ss.str("");
		ss << "displeased, ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 5.f, winWidth, winHeight);
		ss.str("");
		ss << "Mother.";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 4.f, winWidth, winHeight);
		ss.str("");
	}
}
void MotorScene::RenderLight(){

	if(light[0].type == Light::LIGHT_TYPE::DIRECTIONAL){
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[0].position_cameraspace"), 1, &lightDirection_cameraspace.x);
	}
	if (light[1].type == Light::LIGHT_TYPE::SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[1].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[1].spotDirection"), 1, &spotDirection_cameraspace.x);
	}
	if (light[2].type == Light::LIGHT_TYPE::SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[2].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[2].spotDirection"), 1, &spotDirection_cameraspace.x);
	}
	if (light[3].type == Light::LIGHT_TYPE::SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[3].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[3].spotDirection"), 1, &spotDirection_cameraspace.x);
	}
	if (light[4].type == Light::LIGHT_TYPE::SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[4].position;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[4].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[4].spotDirection;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[4].spotDirection"), 1, &spotDirection_cameraspace.x);
	}
	if (light[5].type == Light::LIGHT_TYPE::SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[5].position;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[5].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[5].spotDirection;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[5].spotDirection"), 1, &spotDirection_cameraspace.x);
	}
	if (light[6].type == Light::LIGHT_TYPE::SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[6].position;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[6].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[6].spotDirection;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[6].spotDirection"), 1, &spotDirection_cameraspace.x);
	}

	if(showLightSphere){
		modelStack.PushMatrix();
			modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
			modelStack.Scale(2.f, 2.f, 2.f);
			RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();

	/*	modelStack.PushMatrix();
		modelStack.Translate(light[7].position.x, light[7].position.y, light[7].position.z);
		RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(light[8].position.x, light[8].position.y, light[8].position.z);
		RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();*/
	}
}

void MotorScene::RenderParticle(Mesh* mesh, GLfloat pLife) const{
	Mtx44 MVP, modelView;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(shMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	mesh->Render(pLife);
}

void MotorScene::RenderMesh(Mesh* mesh, bool enableLight) const{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(shMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(shMan->getProgID(), "MV"), 1, GL_FALSE, &modelView.a[0]);
	if(enableLight){
		glUniform1i(glGetUniformLocation(shMan->getProgID(), "lightEnabled"), 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(glGetUniformLocation(shMan->getProgID(), "MV_inverse_transpose"), 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "material.kAmbient"), 1, &mesh->material.kAmbient.r);
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "material.kDiffuse"), 1, &mesh->material.kDiffuse.r);
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "material.kSpecular"), 1, &mesh->material.kSpecular.r);
		glUniform1f(glGetUniformLocation(shMan->getProgID(), "material.kShininess"), mesh->material.kShininess);
	} else{
		glUniform1i(glGetUniformLocation(shMan->getProgID(), "lightEnabled"), 0);
	}
	if(mesh->textureID > 0){
		glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTextureEnabled"), 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTexture"), 0);
	} else{
		glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTextureEnabled"), 0);
	}
	mesh->Render(); //Shld only be called once in the whole function
}

void MotorScene::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY, int winWidth, int winHeight){
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, winWidth / 10, 0, winHeight / 10, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizeX, sizeY, 1);
	RenderMesh(mesh, 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void MotorScene::RenderSkybox(bool lightSwitch){
	lightSwitch = 1;
	modelStack.PushMatrix();
		modelStack.Translate(-49.8f, 0.f, 0.f);
		modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::LEFT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(49.8f, 0.f, 0.f);
		modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::RIGHT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, -49.8f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::FRONT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 49.8f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::BACK)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 49.8f, 0.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Rotate(270.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::TOP)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, -49.8f, 0.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		modelStack.Rotate(-90.f, 1.f, 0.f, 0.f);
		modelStack.PushMatrix();
			modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
			RenderMesh(meshList[unsigned int(MESH::BOTTOM)], lightSwitch);
		modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void MotorScene::RenderAnimation(Mesh* mesh, std::string text, Color color) const{
	if(!mesh || mesh->textureID < 0){
		return;
	}
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "textEnabled"), 1);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTexture"), 0);

	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(shMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	mesh->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "textEnabled"), 0);
	glEnable(GL_DEPTH_TEST);
}

void MotorScene::RenderText(Mesh* mesh, std::string text, Color color) const{
	if(!mesh || mesh->textureID < 0){
		return;
	}
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "textEnabled"), 1);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "textColor"), 1, &color.R);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTexture"), 0);
	for(unsigned i = 0; i < text.length(); ++i){
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.f is spacing
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(glGetUniformLocation(shMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "textEnabled"), 0);
	glEnable(GL_DEPTH_TEST);
}

void MotorScene::createPlatforms()
{
	//5 copies of platform
	object[PLATFORM1].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM1].setTranslation(-35, 0.5, 0);
	object[PLATFORM1].setScale(3);
	object[PLATFORM1].setDimension(30, 30, 30);

	object[PLATFORM2].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM2].setTranslation(10, 0.5, 70);
	object[PLATFORM2].setRotation(45, 'y');
	object[PLATFORM2].setScale(3);
	object[PLATFORM2].setDimension(30, 30, 30);

	object[PLATFORM3].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM3].setTranslation(-80, 0.5, 70);
	object[PLATFORM3].setRotation(-45, 'y');
	object[PLATFORM3].setScale(3);
	object[PLATFORM3].setDimension(30, 30, 30);

	object[PLATFORM4].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM4].setTranslation(10, 0.5, -70);
	object[PLATFORM4].setRotation(-45, 'y');
	object[PLATFORM4].setScale(3);
	object[PLATFORM4].setDimension(30, 30, 30);

	object[PLATFORM5].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM5].setTranslation(-80, 0.5, -70);
	object[PLATFORM5].setRotation(45, 'y');
	object[PLATFORM5].setScale(3);
	object[PLATFORM5].setDimension(30, 30, 30);

	object[PLATFORM6].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM6].setTranslation(-35, 0.5, -70);
	object[PLATFORM6].setScale(3);
	object[PLATFORM6].setDimension(30, 30, 30);

	object[PLATFORM7].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM7].setTranslation(10, 0.5, 0);
	object[PLATFORM7].setRotation(90, 'y');
	object[PLATFORM7].setScale(3);
	object[PLATFORM7].setDimension(30, 30, 30);

	object[PLATFORM8].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM8].setTranslation(-35, 0.5, 70);
	object[PLATFORM8].setScale(3);
	object[PLATFORM8].setDimension(30, 30, 30);

	object[PLATFORM9].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM9].setTranslation(-80, 0.5, 0);
	object[PLATFORM9].setRotation(90, 'y');
	object[PLATFORM9].setScale(3);
	object[PLATFORM9].setDimension(30, 30, 30);
}

void MotorScene::createUFOs()
{
	//5 copies of ufo in ref to individual platform
	object[UFO_BASE1].setMesh(meshList[unsigned int(MESH::UFO_BASE)]);
	object[UFO_BASE1].setTranslation(0, 0.6, 0);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM1], &object[UFO_BASE1], true, true);

	object[UFO_PURPLE1].setMesh(meshList[unsigned int(MESH::UFO_PURPLE)]);
	object[UFO_PURPLE1].setTranslation(0, 0.6, 0);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM2], &object[UFO_PURPLE1], true, true);

	object[UFO_RED1].setMesh(meshList[unsigned int(MESH::UFO_RED)]);
	object[UFO_RED1].setTranslation(0, 0.6, 0);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM3], &object[UFO_RED1], true, true);

	object[UFO_BLUE1].setMesh(meshList[unsigned int(MESH::UFO_BLUE)]);
	object[UFO_BLUE1].setTranslation(0, 0.6, 0);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM4], &object[UFO_BLUE1], true, true);

	object[UFO_PINK1].setMesh(meshList[unsigned int(MESH::UFO_PINK)]);
	object[UFO_PINK1].setTranslation(0, 0.6, 0);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM5], &object[UFO_PINK1], true, true);
}

void MotorScene::createRobot1()
{
	//robot parts for 1 robot
	object[ROBOT_BODY1].setMesh(meshList[unsigned int(MESH::ROBOT_BODY)]);
	object[ROBOT_BODY1].setTranslation(-10, 5.2, 50);
	object[ROBOT_BODY1].setScale(2);
	object[ROBOT_BODY1].setRotation(45, 'y');
	object[ROBOT_BODY1].setDimension(6, 15, 6);

	object[ROBOT_ARM1].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
	object[ROBOT_ARM1].setTranslation(-1, 2, 0);
	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_ARM1], true, true);

	object[ROBOT_ARM2].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
	object[ROBOT_ARM2].setTranslation(1, 2, 0);
	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_ARM2], true, true);

	object[ROBOT_FOREARM1].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
	object[ROBOT_FOREARM1].setTranslation(0, -1, 0);
	Object::bind(&object[ROBOT_ARM1], &object[ROBOT_FOREARM1], true, true);

	object[ROBOT_FOREARM2].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
	object[ROBOT_FOREARM2].setRotation(190, 'y');
	object[ROBOT_FOREARM2].setTranslation(0, -1, 0);
	Object::bind(&object[ROBOT_ARM2], &object[ROBOT_FOREARM2], true, true);

	object[ROBOT_UPPERLEG1].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
	object[ROBOT_UPPERLEG1].setTranslation(-0.45, -0.05, 0);
	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_UPPERLEG1], true, true);

	object[ROBOT_UPPERLEG2].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
	object[ROBOT_UPPERLEG2].setTranslation(0.45, -0.05, 0);
	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_UPPERLEG2], true, true);

	object[ROBOT_LOWERLEG1].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
	object[ROBOT_LOWERLEG1].setTranslation(0, -1.15, 0);
	Object::bind(&object[ROBOT_UPPERLEG1], &object[ROBOT_LOWERLEG1], true, true);

	object[ROBOT_LOWERLEG2].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
	object[ROBOT_LOWERLEG2].setTranslation(0, -1.15, 0);
	Object::bind(&object[ROBOT_UPPERLEG2], &object[ROBOT_LOWERLEG2], true, true);
}

void MotorScene::createVehicles()
{
	//GY CAR
	object[GY_CAR1].setMesh(meshList[unsigned int(MESH::GY_CAR)]);
	object[GY_CAR1].setTranslation(0, 0.6, 0);
	Object::bind(&object[PLATFORM6], &object[GY_CAR1], true, true);

	//EH CAR
	object[EH_CAR1].setMesh(meshList[unsigned int(MESH::EH_CAR)]);
	object[EH_CAR1].setTranslation(0, 0.6, 0);
	Object::bind(&object[PLATFORM7], &object[EH_CAR1], true, true);

	//LF CAR
	object[LF_CAR1].setMesh(meshList[unsigned int(MESH::LF_CAR)]);
	object[LF_CAR1].setTranslation(0, 0.6, 0);
	Object::bind(&object[PLATFORM8], &object[LF_CAR1], true, true);

	//YW CAR
	object[YW_CAR1].setMesh(meshList[unsigned int(MESH::YW_CAR)]);
	object[YW_CAR1].setTranslation(0, 0.6, 0);
	Object::bind(&object[PLATFORM9], &object[YW_CAR1], true, true);
}

void MotorScene::createRobot2()
{
	object[ROBOT_BODY2].setMesh(meshList[unsigned int(MESH::ROBOT_BODY)]);
	object[ROBOT_BODY2].setTranslation(-90, 5.2, 50);
	object[ROBOT_BODY2].setScale(2);
	object[ROBOT_BODY2].setRotation(90, 'y');
	object[ROBOT_BODY2].setDimension(6, 15, 6);

	object[ROBOT_ARM3].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
	object[ROBOT_ARM3].setTranslation(-1, 2, 0);
	Object::bind(&object[ROBOT_BODY2], &object[ROBOT_ARM3], true, true);

	object[ROBOT_ARM4].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
	object[ROBOT_ARM4].setTranslation(1, 2, 0);
	object[ROBOT_ARM4].setRotation(15, 'z');
	Object::bind(&object[ROBOT_BODY2], &object[ROBOT_ARM4], true, true);

	object[ROBOT_FOREARM3].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
	object[ROBOT_FOREARM3].setTranslation(0, -1, 0);
	Object::bind(&object[ROBOT_ARM3], &object[ROBOT_FOREARM3], true, true);

	object[ROBOT_FOREARM4].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
	object[ROBOT_FOREARM4].setRotation(190, 'y');
	object[ROBOT_FOREARM4].setTranslation(0, -1, 0);
	Object::bind(&object[ROBOT_ARM4], &object[ROBOT_FOREARM4], true, true);

	object[ROBOT_UPPERLEG3].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
	object[ROBOT_UPPERLEG3].setTranslation(-0.45, -0.05, 0);
	Object::bind(&object[ROBOT_BODY2], &object[ROBOT_UPPERLEG3], true, true);

	object[ROBOT_UPPERLEG4].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
	object[ROBOT_UPPERLEG4].setTranslation(0.45, -0.05, 0);
	Object::bind(&object[ROBOT_BODY2], &object[ROBOT_UPPERLEG4], true, true);

	object[ROBOT_LOWERLEG3].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
	object[ROBOT_LOWERLEG3].setTranslation(0, -1.15, 0);
	Object::bind(&object[ROBOT_UPPERLEG3], &object[ROBOT_LOWERLEG3], true, true);

	object[ROBOT_LOWERLEG4].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
	object[ROBOT_LOWERLEG4].setTranslation(0, -1.15, 0);
	Object::bind(&object[ROBOT_UPPERLEG4], &object[ROBOT_LOWERLEG4], true, true);
}

void MotorScene::createRobot3()
{
	object[ROBOT_BODY3].setMesh(meshList[unsigned int(MESH::ROBOT_BODY)]);
	object[ROBOT_BODY3].setTranslation(-90, 2.6, 45);
	object[ROBOT_BODY3].setRotation(90, 'y');
	object[ROBOT_BODY3].setDimension(6, 15, 6);

	object[ROBOT_ARM5].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
	object[ROBOT_ARM5].setTranslation(-1, 2, 0);
	object[ROBOT_ARM5].setScale(0.75);
	object[ROBOT_ARM5].setRotation(-150, 'z');
	Object::bind(&object[ROBOT_BODY3], &object[ROBOT_ARM5], true, true);

	object[ROBOT_ARM6].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
	object[ROBOT_ARM6].setTranslation(1, 2, 0);
	object[ROBOT_ARM6].setScale(0.75);
	Object::bind(&object[ROBOT_BODY3], &object[ROBOT_ARM6], true, true);

	object[ROBOT_FOREARM5].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
	object[ROBOT_FOREARM5].setTranslation(0, -1, 0);
	Object::bind(&object[ROBOT_ARM5], &object[ROBOT_FOREARM5], true, true);

	object[ROBOT_FOREARM6].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
	object[ROBOT_FOREARM6].setRotation(190, 'y');
	object[ROBOT_FOREARM6].setTranslation(0, -1, 0);
	Object::bind(&object[ROBOT_ARM6], &object[ROBOT_FOREARM6], true, true);

	object[ROBOT_UPPERLEG5].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
	object[ROBOT_UPPERLEG5].setTranslation(-0.45, -0.05, 0);
	Object::bind(&object[ROBOT_BODY3], &object[ROBOT_UPPERLEG5], true, true);

	object[ROBOT_UPPERLEG6].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
	object[ROBOT_UPPERLEG6].setTranslation(0.45, -0.05, 0);
	Object::bind(&object[ROBOT_BODY3], &object[ROBOT_UPPERLEG6], true, true);

	object[ROBOT_LOWERLEG5].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
	object[ROBOT_LOWERLEG5].setTranslation(0, -1.15, 0);
	Object::bind(&object[ROBOT_UPPERLEG5], &object[ROBOT_LOWERLEG5], true, true);

	object[ROBOT_LOWERLEG6].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
	object[ROBOT_LOWERLEG6].setTranslation(0, -1.15, 0);
	Object::bind(&object[ROBOT_UPPERLEG6], &object[ROBOT_LOWERLEG6], true, true);
}

void MotorScene::createStage()
{
	object[STAGE1].setMesh(meshList[unsigned int(MESH::STAGE)]);
	object[STAGE1].setTranslation(65, 0.5, 0);
	object[STAGE1].setScale(5.5, 8, 8);
	//object[STAGE1].setDimension(55, 80, 80);
}

void MotorScene::createSpeaker()
{
	object[SPEAKER1].setMesh(meshList[unsigned int(MESH::SPEAKER)]);
	object[SPEAKER1].setRotation(-90, 'y');
	object[SPEAKER1].setScale(10);
	object[SPEAKER1].setTranslation(65, 0.5, 70);

	object[SPEAKER2].setMesh(meshList[unsigned int(MESH::SPEAKER)]);
	object[SPEAKER2].setRotation(-90, 'y');
	object[SPEAKER2].setScale(10);
	object[SPEAKER2].setTranslation(65, 0.5, -70);
}

void MotorScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int winWidth, int winHeight){
	if(!mesh || mesh->textureID <= 0){ //Proper error check return
		glDisable(GL_DEPTH_TEST);
	}
	Mtx44 ortho;
	ortho.SetToOrtho(0, winWidth / 10, 0, winHeight / 10, -10, 10); //Size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need cam for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "textEnabled"), 1);
	glUniform3fv(glGetUniformLocation(shMan->getProgID(), "textColor"), 1, &color.R);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	if(mesh != 0){
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	}
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "colorTexture"), 0);
	for(unsigned i = 0; i < text.length(); ++i){
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.f is spacing
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(glGetUniformLocation(shMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "textEnabled"), 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void MotorScene::renderObject(Object* obj)
{
	if (obj->isRender() && obj->getMesh() != nullptr)
	{
		modelStack.Translate(obj->getTranslation().x, obj->getTranslation().y, obj->getTranslation().z);
		if (obj->getChild().size() != 0)
		{
			for (int i = 0; i < obj->getChild().size(); ++i)
			{
				modelStack.PushMatrix();
				if (obj->getChild()[i]->followParentRotation())//if obj follows parent's rotation (for joints etc)
				{
					if (obj->getAngle().x != 0)
						modelStack.Rotate(obj->getAngle().x, 1, 0, 0);
					if (obj->getAngle().y != 0)
						modelStack.Rotate(obj->getAngle().y, 0, 1, 0);
					if (obj->getAngle().z != 0)
						modelStack.Rotate(obj->getAngle().z, 0, 0, 1);
				}
				if (obj->getChild()[i]->followParentScale())
					modelStack.Scale(obj->getScale().x, obj->getScale().y, obj->getScale().z);
				renderObject(obj->getChild()[i]);
				modelStack.PopMatrix();
			}
		}
		if (obj->getAngle().x != 0)
			modelStack.Rotate(obj->getAngle().x, 1, 0, 0);
		if (obj->getAngle().y != 0)
			modelStack.Rotate(obj->getAngle().y, 0, 1, 0);
		if (obj->getAngle().z != 0)
			modelStack.Rotate(obj->getAngle().z, 0, 0, 1);

		modelStack.Scale(obj->getScale().x, obj->getScale().y, obj->getScale().z);
		RenderMesh(obj->getMesh(), true);
	}
}
void MotorScene::npcCheck(int instance, const char* audioFileName)
{	//finds angle in between two vectors
	Vector3 posToObject = object[instance].getPos() - Camera::getCam().pos;
	Vector3 posToTarget = Camera::getCam().target - Camera::getCam().pos;

	if (object[instance].getDist(Camera::getCam().pos) < 20.f)
	{
		if (object[instance].getAngle(posToObject,posToTarget) < 0.25) //30degrees
		{
			inRange[instance] = true;
			if (Application::IsKeyPressed('E') && interactBounceTime <= elapsedTime)
			{
				interacted[instance] = !interacted[instance];
				interactBounceTime = elapsedTime + 0.4;
				if (interacted[instance])
					engine->play2D(audioFileName);
			}
		}
		else
		{
			inRange[instance] = 0;
			interacted[instance] = 0;
		}
	}
	else
	{
		inRange[instance] = 0;
		interacted[instance] = 0;
	}
}

void MotorScene::carCheck(int instance, const char* audioFileName)
{
	//finds angle in between two vectors
	Vector3 posToObject = object[instance].getPos() - Camera::getCam().pos;
	Vector3 posToTarget = Camera::getCam().target - Camera::getCam().pos;

	if (object[instance].getDist(Camera::getCam().pos) < 30.f)
	{
		if (object[instance].getAngle(posToObject, posToTarget) < 0.5)
		{
			inRange[instance] = true;
			if (Application::IsKeyPressed('E') && interactBounceTime <= elapsedTime)
			{
				interacted[instance] = !interacted[instance];
				interactBounceTime = elapsedTime + 0.4;
				//when interact wif car, car light on
				if (instance==6)
				{
					light[1].power = 2.f;
					glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].power"), light[1].power);
					light[2].power = 2.f;
					glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].power"), light[2].power);
					engine->play2D(audioFileName);
				}
				if (instance==7)
				{
					light[3].power = 2.f;
					glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].power"), light[3].power);
					light[4].power = 2.f;
					glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].power"), light[4].power);
					engine->play2D(audioFileName);
				}
				if (instance==8)
				{
					light[5].power = 2.f;
					glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].power"), light[5].power);
					light[6].power = 2.f;
					glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].power"), light[6].power);
					engine->play2D(audioFileName);
				}
			}
		}
		else
		{
			inRange[instance] = 0;
			interacted[instance] = 0;
		}
	}
	else
	{
		//as long as character go out of range, light turns off
		inRange[instance] = 0;
		interacted[instance] = 0;
		if (instance == 6)
		{
			light[1].power = 0.f;
			glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[1].power"), light[1].power);
			light[2].power = 0.f;
			glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[2].power"), light[2].power);
		}
		if (instance == 7)
		{
			light[3].power = 0.f;
			glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[3].power"), light[3].power);
			light[4].power = 0.f;
			glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[4].power"), light[4].power);
		}
		if (instance == 8)
		{
			light[5].power = 0.f;
			glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[5].power"), light[5].power);
			light[6].power = 0.f;
			glUniform1f(glGetUniformLocation(shMan->getProgID(), "lights[6].power"), light[6].power);
		}
	}
}
