#include <iostream>
#include <iomanip>
#include <sstream>
#include "MotorScene.h"
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
	glUniform1i(glGetUniformLocation(shMan->getProgID(), "numLights"), 1);
}

void MotorScene::InitMeshes(){
	meshList[unsigned int(MESH::HITBOXWHITE)] = MeshBuilder::GenerateCuboid(Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);
	meshList[unsigned int(MESH::HITBOXRED)] = MeshBuilder::GenerateCuboid(Color(1, 0, 0), 1.1f, 1.1f, 1.1f);
	meshList[unsigned int(MESH::HITSPHERE)] = MeshBuilder::GenerateSphere(Color(1.f, 1.f, 1.f),16,16,1);
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

	//meshList[unsigned int(MESH::UFO_BASE)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	//meshList[unsigned int(MESH::UFO_BASE)]->textureID = LoadTGA("Resources/TGAs/ufo_base.tga");
	//meshList[unsigned int(MESH::UFO_PURPLE)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	//meshList[unsigned int(MESH::UFO_PURPLE)]->textureID = LoadTGA("Resources/TGAs/ufo_1.tga");
	//meshList[unsigned int(MESH::UFO_RED)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	//meshList[unsigned int(MESH::UFO_RED)]->textureID = LoadTGA("Resources/TGAs/ufo_2.tga");
	//meshList[unsigned int(MESH::UFO_BLUE)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	//meshList[unsigned int(MESH::UFO_BLUE)]->textureID = LoadTGA("Resources/TGAs/ufo_6.tga");
	//meshList[unsigned int(MESH::UFO_PINK)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	//meshList[unsigned int(MESH::UFO_PINK)]->textureID = LoadTGA("Resources/TGAs/ufo_7.tga");

	////base mesh
	//meshList[unsigned int(MESH::PLATFORM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/platform.obj");
	//meshList[unsigned int(MESH::PLATFORM)]->textureID = LoadTGA("Resources/TGAs/platform.tga");

	////base mesh
	//meshList[unsigned int(MESH::ROBOT_BODY)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_body.obj");
	//meshList[unsigned int(MESH::ROBOT_BODY)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
	//meshList[unsigned int(MESH::ROBOT_ARM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_arm.obj");
	//meshList[unsigned int(MESH::ROBOT_ARM)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
	//meshList[unsigned int(MESH::ROBOT_FOREARM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_forearm.obj");
	//meshList[unsigned int(MESH::ROBOT_FOREARM)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
	//meshList[unsigned int(MESH::ROBOT_UPPERLEG)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_upperleg.obj");
	//meshList[unsigned int(MESH::ROBOT_UPPERLEG)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
	//meshList[unsigned int(MESH::ROBOT_LOWERLEG)] = MeshBuilder::GenerateOBJ("Resources/OBJs/robot_lowerleg.obj");
	//meshList[unsigned int(MESH::ROBOT_LOWERLEG)]->textureID = LoadTGA("Resources/TGAs/robot.tga");
}

void MotorScene::CreateInstances()
{
	object[TESTBOX].setMesh(meshList[unsigned int(MESH::HITBOXRED)]);
	object[TESTBOX].setScale(10, 10, 10);
	object[TESTBOX].setDimension(10, 10, 10);
	object[TESTBOX].setTranslation(0,35,0);

	object[TESTBOX2].setMesh(meshList[unsigned int(MESH::HITBOXWHITE)]);
	/*object[TESTBOX2].setRotation(90, 'y');*/
	object[TESTBOX2].setDimension(100, 10, 10);
	object[TESTBOX2].setTranslation(0, 35, 40);

	//object[TESTBOX3].setMesh(meshList[unsigned int(MESH::HITBOXWHITE)]);
	//object[TESTBOX3].setScale(10, 10, 10);
	//object[TESTBOX3].setDimension(10, 10, 10);
	//object[TESTBOX3].setTranslation(-5, 35, 20);

	//object[TESTBOX4].setMesh(meshList[unsigned int(MESH::HITBOXWHITE)]);
	//object[TESTBOX4].setScale(10, 10, 10);
	//object[TESTBOX4].setDimension(10, 10, 10);
	//object[TESTBOX4].setTranslation(5, 35, 20);
	
	testVehicle.setObject(&object[TESTBOX]);

	////create instances for platforms
	//createPlatforms();

	////create instances for ufos
	//createUFOs();

	//createRobot1();

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
	//bulletBounceTime = debugBounceTime = lightBounceTime = interactBounceTime = 0.0;
	//inRange[ROBOT_BODY1] = 0;
	//interacted[ROBOT_BODY1] = 0;

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

void MotorScene::Update(double dt, float FOV){ //Update scene
	for(int i = 0; i < 7; ++i){
		if(Application::IsKeyPressed(keys[i])){
			switch(keys[i]){
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
	if(Application::IsKeyPressed('P') && lightBounceTime <= elapsedTime){ //Show/Hide light sphere
		showLightSphere = !showLightSphere;
		lightBounceTime = elapsedTime + 0.4;
	}
	if (Application::IsKeyPressed('R') ) { //Testing only, delete after debugging
		object[TESTBOX].setTranslation(0, 35, 0);
		object[TESTBOX].setRotation(0, 'y');
		object[TESTBOX].setVelocity(0, 0, 0);
	}
	if (Application::IsKeyPressed(VK_SHIFT) && debugBounceTime <= elapsedTime) { //Show/Hide debug info
		showDebugInfo = !showDebugInfo;
		debugBounceTime = elapsedTime + 0.5;
	}

	if(bulletBounceTime <= elapsedTime && bulletGenerator.currAmt < bulletGenerator.maxAmt){
		Particle* p = bulletGenerator.particlePool[bulletGenerator.GetIndex()];
		p->color = Color(1.f, 0.f, 0.f);
		p->dir = Vector3(0, 1, 0);
		p->life = 1.f;
		p->pos = Vector3(0, 0, 0) + p->dir * 2.5f + Vector3(0.f, 7.5f, 0.f);
		++bulletGenerator.currAmt;
		bulletBounceTime = elapsedTime + 0.2;
	}
	bulletGenerator.UpdateParticles(dt);



	for (int i = 0; i < 5; i++)
	{
		object[i].addRotation(1, 'y');
	}
	
	
	std::cout << "\n";
	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		object[i].resetCollision();
	}

	object[TESTBOX2].addRotation(10 * dt, 'y');

	testVehicle.update(dt);

	for (int j = 0; j < NUM_INSTANCES; ++j)//update all collisions of objects in scene
	{
		for (int i = 0; i < NUM_INSTANCES; ++i)
		{
			if (i < j)
				i = j+1;
			object[j].updateCollision(&object[i],dt);
		}
	}



	//!testing! if w is pressed, sound effects will be played
	//if (Application::IsKeyPressed('W'))
	//	engine->play2D("Resources/Sound/bell.wav");


	if (object[ROBOT_BODY1].checkDist(Camera::getCam().target) < 15.f)
	{
		inRange[ROBOT_BODY1] = true;
		if (Application::IsKeyPressed('E') && interactBounceTime <= elapsedTime)
		{
			interacted[ROBOT_BODY1] = !interacted[ROBOT_BODY1];
			interactBounceTime = elapsedTime + 0.4;
			if (interacted[ROBOT_BODY1])
				engine->play2D("Resources/Sound/robot1.wav");
		}
	}
	else
	{
		inRange[ROBOT_BODY1] = 0;
		interacted[ROBOT_BODY1] = 0;
	}

	Mtx44 projection;
	projection.SetToPerspective(FOV, 4.f / 3.f, 0.1f, 1000.f); //FOV value affects cam zoom
	projectionStack.LoadMatrix(projection);
}

void MotorScene::Render(double dt, int winWidth, int winHeight){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	if(showDebugInfo){
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
		ss << "PosX: " << object[TESTBOX].collisionAt[0] << std::endl;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f ,28, winWidth, winHeight);
		ss.str("");
		ss << "NegX: " << object[TESTBOX].collisionAt[1] << std::endl;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f,27, winWidth, winHeight);
		ss.str("");
		ss << "PosY: " << object[TESTBOX].collisionAt[2] << std::endl;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 26, winWidth, winHeight);
		ss.str("");
		ss << "NegY: " << object[TESTBOX].collisionAt[3] << std::endl;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 25, winWidth, winHeight);
		ss.str("");
		ss << "PosZ: " << object[TESTBOX].collisionAt[4] << std::endl;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 24, winWidth, winHeight);
		ss.str("");
		ss << "NegZ: " << object[TESTBOX].collisionAt[5] << std::endl;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 23, winWidth, winHeight);
		ss.str("");
		ss << "VEHICLE POS: [" << object[TESTBOX].getPos().x << "] ["<<object[TESTBOX].getPos().y << "] ["<<object[TESTBOX].getPos().z << "]";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 22, winWidth, winHeight);
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
}

void MotorScene::RenderLight(){
	if(light[0].type == Light::LIGHT_TYPE::DIRECTIONAL){
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[0].position_cameraspace"), 1, &lightDirection_cameraspace.x);
	} else if(light[0].type == Light::LIGHT_TYPE::SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[0].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[0].spotDirection"), 1, &spotDirection_cameraspace.x);
	} else{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(glGetUniformLocation(shMan->getProgID(), "lights[0].position_cameraspace"), 1, &lightPosition_cameraspace.x);
	}
	if(showLightSphere){
		modelStack.PushMatrix();
			modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
			modelStack.Scale(2.f, 2.f, 2.f);
			RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
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

	//modelStack.PushMatrix();
	//	modelStack.Translate(49.8f, 0.f, 0.f);
	//	modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
	//	modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
	//	modelStack.Scale(100.f, 100.f, 100.f);
	//	RenderMesh(meshList[unsigned int(MESH::RIGHT)], lightSwitch);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//	modelStack.Translate(0.f, 0.f, -49.8f);
	//	modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
	//	modelStack.Scale(100.f, 100.f, 100.f);
	//	RenderMesh(meshList[unsigned int(MESH::FRONT)], lightSwitch);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//	modelStack.Translate(0.f, 0.f, 49.8f);
	//	modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
	//	modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
	//	modelStack.Scale(100.f, 100.f, 100.f);
	//	RenderMesh(meshList[unsigned int(MESH::BACK)], lightSwitch);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//	modelStack.Translate(0.f, 49.8f, 0.f);
	//	modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
	//	modelStack.Rotate(270.f, 0.f, 0.f, 1.f);
	//	modelStack.Scale(100.f, 100.f, 100.f);
	//	RenderMesh(meshList[unsigned int(MESH::TOP)], lightSwitch);
	//modelStack.PopMatrix();

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

//void MotorScene::createPlatforms()
//{
//	//5 copies of platform
//	object[PLATFORM1].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
//	object[PLATFORM1].setTranslation(0, 0.5, 0);
//	object[PLATFORM1].setScale(4);
//	object[PLATFORM1].setDimension(40, 40, 40);
//
//	object[PLATFORM2].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
//	object[PLATFORM2].setTranslation(70, 0.5, 70);
//	object[PLATFORM2].setScale(4);
//	object[PLATFORM2].setDimension(40, 40, 40);
//
//	object[PLATFORM3].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
//	object[PLATFORM3].setTranslation(-70, 0.5, 70);
//	object[PLATFORM3].setScale(4);
//	object[PLATFORM3].setDimension(40, 40, 40);
//
//	object[PLATFORM4].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
//	object[PLATFORM4].setTranslation(70, 0.5, -70);
//	object[PLATFORM4].setScale(4);
//	object[PLATFORM4].setDimension(40, 40, 40);
//
//	object[PLATFORM5].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
//	object[PLATFORM5].setTranslation(-70, 0.5, -70);
//	object[PLATFORM5].setScale(4);
//	object[PLATFORM5].setDimension(40, 40, 40);
//}
//
//void MotorScene::createUFOs()
//{
//	//5 copies of ufo in ref to individual platform
//	object[UFO_BASE1].setMesh(meshList[unsigned int(MESH::UFO_BASE)]);
//	object[UFO_BASE1].setTranslation(0.f, 0.6f, 0.f);
//	//ufo in ref to platform
//	Object::bind(&object[PLATFORM1], &object[UFO_BASE1], true, true);
//
//	object[UFO_PURPLE1].setMesh(meshList[unsigned int(MESH::UFO_PURPLE)]);
//	object[UFO_PURPLE1].setTranslation(0.f, 0.6f, 0.f);
//	//ufo in ref to platform
//	Object::bind(&object[PLATFORM2], &object[UFO_PURPLE1], true, true);
//
//	object[UFO_RED1].setMesh(meshList[unsigned int(MESH::UFO_RED)]);
//	object[UFO_RED1].setTranslation(0.f, 0.6f, 0.f);
//	//ufo in ref to platform
//	Object::bind(&object[PLATFORM3], &object[UFO_RED1], true, true);
//
//	object[UFO_BLUE1].setMesh(meshList[unsigned int(MESH::UFO_BLUE)]);
//	object[UFO_BLUE1].setTranslation(0.f, 0.6f, 0.f);
//	//ufo in ref to platform
//	Object::bind(&object[PLATFORM4], &object[UFO_BLUE1], true, true);
//
//	object[UFO_PINK1].setMesh(meshList[unsigned int(MESH::UFO_PINK)]);
//	object[UFO_PINK1].setTranslation(0.f, 0.6f, 0.f);
//	//ufo in ref to platform
//	Object::bind(&object[PLATFORM5], &object[UFO_PINK1], true, true);
//}
//
//void MotorScene::createRobot1()
//{
//	//robot parts for 1 robot
//	object[ROBOT_BODY1].setMesh(meshList[unsigned int(MESH::ROBOT_BODY)]);
//	object[ROBOT_BODY1].setTranslation(50.f, 5.2f, 50.f);
//	object[ROBOT_BODY1].setScale(2);
//	object[ROBOT_BODY1].setDimension(6.f, 15.f, 6.f);
//	/*object[ROBOT_BODY1].setRotation(45,'y');*/
//
//	object[ROBOT_ARM1].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
//	object[ROBOT_ARM1].setTranslation(-1.f, 2.f, 0.f);
//	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_ARM1], true, true);
//
//	object[ROBOT_ARM2].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
//	object[ROBOT_ARM2].setTranslation(1.f, 2.f, 0.f);
//	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_ARM2], true, true);
//
//	object[ROBOT_FOREARM1].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
//	object[ROBOT_FOREARM1].setTranslation(0.f, -1.f, 0.f);
//	Object::bind(&object[ROBOT_ARM1], &object[ROBOT_FOREARM1], true, true);
//
//	object[ROBOT_FOREARM2].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
//	object[ROBOT_FOREARM2].setRotation(190, 'y');
//	object[ROBOT_FOREARM2].setTranslation(0.f, -1.f, 0.f);
//	Object::bind(&object[ROBOT_ARM2], &object[ROBOT_FOREARM2], true, true);
//
//	object[ROBOT_UPPERLEG1].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
//	object[ROBOT_UPPERLEG1].setTranslation(-0.45f, -0.05f, 0.f);
//	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_UPPERLEG1], true, true);
//
//	object[ROBOT_UPPERLEG2].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
//	object[ROBOT_UPPERLEG2].setTranslation(0.45f, -0.05f, 0.f);
//	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_UPPERLEG2], true, true);
//
//	object[ROBOT_LOWERLEG1].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
//	object[ROBOT_LOWERLEG1].setTranslation(0.f, -1.15f, 0.f);
//	Object::bind(&object[ROBOT_UPPERLEG1], &object[ROBOT_LOWERLEG1], true, true);
//
//	object[ROBOT_LOWERLEG2].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
//	object[ROBOT_LOWERLEG2].setTranslation(0.f, -1.15f, 0.f);
//	Object::bind(&object[ROBOT_UPPERLEG2], &object[ROBOT_LOWERLEG2], true, true);
//}

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