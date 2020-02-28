#include <iostream>
#include <iomanip>
#include <sstream>
#include "GameScene2.h"
#include "GL\glew.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.hpp"
#include "SceneManager.h"

extern Camera camera;
extern double elapsedTime;

double GameScene2::CalcFrameRate() const {
	static double FPS, FramesPerSecond = 0.0, lastTime = 0.0;
	double valueFPS, currTime = GetTickCount64() * 0.001;
	++FramesPerSecond;
	valueFPS = FPS;
	if (currTime - lastTime > 1.0) {
		lastTime = currTime;
		FPS = double(FramesPerSecond);
		FramesPerSecond = 0.0;
	}
	return valueFPS;
}

void GameScene2::InitLight() const {
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].type"), GLint(light[0].type));
	glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].color"), 1, &light[0].color.R);
	glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].power"), light[0].power);
	glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].kC"), light[0].kC);
	glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].kL"), light[0].kL);
	glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].kQ"), light[0].kQ);
	glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].spotDirection"), 1, &light[0].spotDirection.x);
	glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].cosCutoff"), light[0].cosCutoff);
	glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].cosInner"), light[0].cosInner);
	glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].exponent"), light[0].exponent);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "numLights"), 1);
}

void GameScene2::InitMeshes() {
	meshList[unsigned int(MESH::REDHITBOX)] = MeshBuilder::GenerateCuboid(Color(1, 0, 0), 1, 1, 1);
	meshList[unsigned int(MESH::REDHITBOX)]->textureID = LoadTGA("Resources/TGAs/ufo_2.tga");
	meshList[unsigned int(MESH::WHITEHITBOX)] = MeshBuilder::GenerateCuboid(Color(1, 1, 1), 1, 1, 1);
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
	meshList[unsigned int(MESH::BOTTOM)]->textureID = LoadTGA("Resources/TGAs/bottom.tga");
	meshList[unsigned int(MESH::LIGHT_SPHERE)] = MeshBuilder::GenerateSphere(Color(1.f, 1.f, 1.f), 9, 36, 1.f);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)] = MeshBuilder::GenerateText(16, 16);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)]->textureID = LoadTGA("Resources/TGAs/FontOnScreen.tga");

	meshList[unsigned int(MESH::UFO_BASE)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	meshList[unsigned int(MESH::UFO_BASE)]->textureID = LoadTGA("Resources/TGAs/ufo_base.tga");

	meshList[unsigned int(MESH::UFO_RED)] = MeshBuilder::GenerateOBJ("Resources/OBJs/ufo.obj");
	meshList[unsigned int(MESH::UFO_RED)]->textureID = LoadTGA("Resources/TGAs/ufo_2.tga");
}
void GameScene2::CreateInstances()
{
	object[UFO_BASE1].setMesh(meshList[unsigned int(MESH::UFO_BASE)]);
	object[UFO_BASE1].setTranslation(150, 0,0);
	object[UFO_BASE1].setScale(4);
	object[UFO_BASE1].setDimension(25, 20, 20);
	object[UFO_BASE1].setHasGravity(true);
	player1.setObject(&object[UFO_BASE1], false);
	player1.disableAnimation(true);

	object[UFO_RED1].setMesh(meshList[unsigned int(MESH::UFO_RED)]);
	object[UFO_RED1].setTranslation(-150, 0,0);
	object[UFO_RED1].setScale(4);
	object[UFO_RED1].setDimension(25, 20, 20);
	object[UFO_RED1].setHasGravity(true);
	player2.setObject(&object[UFO_RED1], false);
	player2.disableAnimation(true);

	object[GROUND].setMesh(meshList[unsigned int(MESH::WHITEHITBOX)]);
	object[GROUND].setTranslation(0, -30, 0);
	object[GROUND].setDimension(400, 10, 400);

	object[PLAYER1SCORE].setMesh(meshList[unsigned int(MESH::WHITEHITBOX)]);
	object[PLAYER1SCORE].setTranslation(-201, 75, 0);
	object[PLAYER1SCORE].setDimension(1, 200, 400);

	object[PLAYER2SCORE].setMesh(meshList[unsigned int(MESH::WHITEHITBOX)]);
	object[PLAYER2SCORE].setTranslation(201, 75, 0);
	object[PLAYER2SCORE].setDimension(1, 200, 400);

	for (int i = 0; i < 20; ++i)
	{
		inactiveObstacleQueue.push_back(new Object);
	}
	for (int i = 0; i < inactiveObstacleQueue.size(); ++i)
	{
		inactiveObstacleQueue.at(i)->setMesh(meshList[unsigned int(MESH::REDHITBOX)]);
		inactiveObstacleQueue.at(i)->setDimension(35, 10, 10);
		inactiveObstacleQueue.at(i)->setScale(35, 10, 10);
		inactiveObstacleQueue.at(i)->setTranslation(0, 5, 1500);
	}
}

void GameScene2::Init() { //Init scene
	glGenVertexArrays(1, &m_vertexArrayID); //Generate a default VAO
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_CULL_FACE); //Enable back-face cullingyg
	glEnable(GL_BLEND); //Enable blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST); //Enable depth test
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	camera.Init(Vector3(0.f, 330.f, -500.f), Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, 1.f));
	InitLight();
	InitMeshes();
	CreateInstances();
	bulletGenerator.InitParticles();
	showDebugInfo = 1;
	showLightSphere = 0;
	bulletBounceTime = debugBounceTime = lightBounceTime = timeSinceLastObstacle = 0.0;
	survivalTime = 0;
	hitPoints = 3;
	srand(time(NULL));
	player1.disableKey(5);//disable fly
	player2.disableKey(5);
}

void GameScene2::Exit(Scene* newScene) { //Exit scene
	for (int i = 0; i < int(MESH::NUM_GEOMETRY); ++i) {
		if (meshList[i] != 0) {
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	if (dynamic_cast<GameScene2*>(newScene) != this) {
		newScene->Init();
	}
	for (int i = 0; i < activeObstacleQueue.size(); ++i)
	{
		delete activeObstacleQueue.at(i);
	}
	for (int i = 0; i < inactiveObstacleQueue.size(); ++i)
	{
		delete inactiveObstacleQueue.at(i);
	}
}

void GameScene2::Update(double dt, float FOV) { //Update scene
	for (int i = 0; i < 7; ++i) {
		if (Application::IsKeyPressed(keys[i])) {
			switch (keys[i]) {
			case '1': glDisable(GL_CULL_FACE); break; //Disable back-face culling
			case '2': glEnable(GL_CULL_FACE); break; //Enable back-face culling
			case '3': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break; //Set polygon mode to GL_FILL (default mode)
			case '4': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break; //Set polygon mode to GL_LINE (wireframe mode)
			case '8': { //Off the light
				light[0].power = 0.f;
				glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].power"), light[0].power);
				break;
			}
			case '9': { //On the light
				light[0].power = 1.f;
				glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].power"), light[0].power);
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
	if (Application::IsKeyPressed('R')) { //Show/Hide light sphere
		resetGame();
	}
	if (Application::IsKeyPressed(VK_SHIFT) && debugBounceTime <= elapsedTime) { //Show/Hide debug info
		showDebugInfo = !showDebugInfo;
		debugBounceTime = elapsedTime + 0.5;
	}


	player1.update(dt);
	player2.update(dt);

	updateGame(dt);

	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		object[i].resetCollision();
	}

	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		if (&object[i] == player1.getObject() || &object[i] == player2.getObject() || object[i].getDimension().y == 0)
			continue;
		object[UFO_BASE1].updateCollision(&object[i], dt);
		object[UFO_RED1].updateCollision(&object[i], dt);
	}


	





	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		object[i].updatePosition(dt);
	}

	Mtx44 projection;
	projection.SetToPerspective(FOV, 4.f / 3.f, 0.1f, 1000.f); //FOV value affects cam zoom
	projectionStack.LoadMatrix(projection);
}


void GameScene2::updateGame(double dt)
{
	survivalTime += dt;

	updateObstacleState(dt);

	//if (camera.pos.x< object[UFO_BASE1].getPos().x || camera.pos.x > object[UFO_BASE1].getPos().x)//camera follow player
	//{
	//	float cameraXDisplacement = camera.pos.x - object[UFO_BASE1].getPos().x;
	//	camera.pos.x -= cameraXDisplacement * 5 * dt;
	//	camera.target.Set(object[UFO_BASE1].getPos().x / 2, object[UFO_BASE1].getPos().y, object[UFO_BASE1].getPos().z);
	//}

	for (int i = 0; i < activeObstacleQueue.size(); ++i)//check if obstacle hit player
	{
		if (object[UFO_BASE1].updateCollision(activeObstacleQueue.at(i), dt) && activeObstacleQueue.at(i) != nullptr)
		{
			inactiveObstacleQueue.push_back(activeObstacleQueue.at(i));
			activeObstacleQueue.erase(activeObstacleQueue.begin() + i);
			--hitPoints;
			if (hitPoints <= 0)
			{
				resetGame();
			}
		}
	}


	for (int i = 0; i < activeObstacleQueue.size(); ++i)
	{


	}

}

void GameScene2::resetGame()
{
	hitPoints = 3;
	survivalTime = 0;
	object[UFO_BASE1].setTranslation(150,0 ,0 );
	object[UFO_BASE1].setVelocity(0, 0.0, 0);
	
	object[UFO_RED1].setTranslation(-150, 0, 0);
	object[UFO_RED1].setVelocity(0, 0.0, 0);
	for (int i = 0; i < activeObstacleQueue.size(); ++i)
	{
		inactiveObstacleQueue.push_back(activeObstacleQueue.at(i));
		activeObstacleQueue.erase(activeObstacleQueue.begin() + i);
	}
	
	camera.pos.Set(0.f, 330.f, -500.f), camera.target.Set(0.f, 1.f, 0.f), camera.up.Set(0.f, 0.f, 1.f);
}
void GameScene2::updateObstacleState(double dt)
{
	float spawnInterval = 5 - survivalTime / 15; //increases rate of obstacle spawn as time passes
	if (spawnInterval < 1)
		spawnInterval = 0.7;
	if (timeSinceLastObstacle < spawnInterval) //checks for whether to spawn new obstacle
	{
		timeSinceLastObstacle += dt;
		return;
	}
	timeSinceLastObstacle = 0;
	bool slotTaken[3] = { 0, };
	for (int i = 0; i < 2; ++i)
	{
		if (inactiveObstacleQueue.size() > 0)
		{
			activeObstacleQueue.push_back(inactiveObstacleQueue.back());
			inactiveObstacleQueue.pop_back();
		}
		else break;

		bool retry = true;
		while (retry)//randomises obstacle slot placement
		{
			switch (rand() % 3)
			{
			case 0:
				if (!slotTaken[0])
				{
					slotTaken[0] = true;
					activeObstacleQueue.back()->setTranslation(0, 5, 1500);
					retry = false;
				}
				break;
			case 1:
				if (!slotTaken[0])
				{
					slotTaken[0] = true;
					activeObstacleQueue.back()->setTranslation(-40.1f, 5, 1500);
					retry = false;
				}
				break;
			case 2:
				if (!slotTaken[2])
				{
					slotTaken[2] = true;
					activeObstacleQueue.back()->setTranslation(40.1f, 5, 1500);
					retry = false;
				}
				break;
			default: std::cout << "random number at void GameScene2::updateObstacleState(double dt) out of range" << std::endl; //error:random number out of range
				break;
			}
		}
	}
}

void GameScene2::Render(double dt, int winWidth, int winHeight) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.pos.x, camera.pos.y, camera.pos.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	RenderLight();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 50.f, 380.f);
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderSkybox(!light[0].power);
	modelStack.PopMatrix();

	//for (int i = 0; i < activeObstacleQueue.size(); ++i) //Display obstacle hitboxes
	//{
	//	if (activeObstacleQueue.at(i) != nullptr)
	//	{
	//		modelStack.PushMatrix();
	//		modelStack.Translate(activeObstacleQueue.at(i)->getPos().x, activeObstacleQueue.at(i)->getPos().y, activeObstacleQueue.at(i)->getPos().z);
	//		modelStack.Scale(activeObstacleQueue.at(i)->getScale().x, activeObstacleQueue.at(i)->getScale().y, activeObstacleQueue.at(i)->getScale().z);
	//		RenderMesh(meshList[unsigned int(MESH::REDHITBOX)], false);
	//		modelStack.PopMatrix();
	//	}
	//}

	for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		if (object[i].getDimension().y > 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(object[i].getPos().x, object[i].getPos().y, object[i].getPos().z);
			modelStack.Scale(object[i].getDimension().x, object[i].getDimension().y, object[i].getDimension().z);
			RenderMesh(meshList[unsigned int(MESH::REDHITBOX)],false);
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
		ss << "Cam target: " << camera.target.x << ", " << camera.target.y << ", " << camera.target.z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 29.f, winWidth, winHeight);
		ss.str("");
		ss << "Cam pos: " << camera.pos.x << ", " << camera.pos.y << ", " << camera.pos.z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 28.f, winWidth, winHeight);
		ss.str("");
		ss << "velocity: " << object->getVelocity().x << ", " << object->getVelocity().y << ", " << object->getVelocity().z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 27.f, winWidth, winHeight);
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
}

void GameScene2::RenderLight() {
	if (light[0].type == Light::LIGHT_TYPE::DIRECTIONAL) {
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].position_cameraspace"), 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_TYPE::SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].spotDirection"), 1, &spotDirection_cameraspace.x);
	}
	else {
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].position_cameraspace"), 1, &lightPosition_cameraspace.x);
	}
	if (showLightSphere) {
		modelStack.PushMatrix();
		modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
		modelStack.Scale(2.f, 2.f, 2.f);
		RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
	}
}

void GameScene2::RenderMesh(Mesh* mesh, bool enableLight) const {
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MV"), 1, GL_FALSE, &modelView.a[0]);
	if (enableLight) {
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MV_inverse_transpose"), 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "material.kAmbient"), 1, &mesh->material.kAmbient.r);
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "material.kDiffuse"), 1, &mesh->material.kDiffuse.r);
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "material.kSpecular"), 1, &mesh->material.kSpecular.r);
		glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "material.kShininess"), mesh->material.kShininess);
	}
	else {
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 0);
	}
	if (mesh->textureID > 0) {
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTexture"), 0);
	}
	else {
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 0);
	}
	mesh->Render(); //Shld only be called once in the whole function
}

void GameScene2::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY, int winWidth, int winHeight) {
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

void GameScene2::RenderSkybox(bool lightSwitch) {
	lightSwitch = 1;
	/*modelStack.PushMatrix();
	modelStack.Translate(-24.8f, 0.f, 0.f);
	modelStack.Scale(50.f, 50.f, 400.f);
	modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
	modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
	RenderMesh(meshList[unsigned int(MESH::LEFT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(24.8f, 0.f, 0.f);
	modelStack.Scale(50.f, 50.f, 400.f);
	modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
	modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
	RenderMesh(meshList[unsigned int(MESH::RIGHT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, -199.8f);
	modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
	modelStack.Scale(50.f, 50.f, 50.f);
	RenderMesh(meshList[unsigned int(MESH::FRONT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, 199.8f);
	modelStack.Scale(50.f, 50.f, 50.f);
	modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
	modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
	RenderMesh(meshList[unsigned int(MESH::BACK)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 24.8f, 0.f);
	modelStack.Scale(50.f, 50.f, 400.f);
	modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
	modelStack.Rotate(270.f, 0.f, 0.f, 1.f);
	RenderMesh(meshList[unsigned int(MESH::TOP)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, -24.8f, 0.f);
	modelStack.Scale(50.f, 50.f, 400.f);
	modelStack.Rotate(-90.f, 1.f, 0.f, 0.f);
	modelStack.PushMatrix();
	modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
	RenderMesh(meshList[unsigned int(MESH::BOTTOM)], lightSwitch);
	modelStack.PopMatrix();
	modelStack.PopMatrix();*/
}

void GameScene2::RenderAnimation(Mesh* mesh, std::string text, Color color) const {
	if (!mesh || mesh->textureID < 0) {
		return;
	}
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textEnabled"), 1);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTexture"), 0);

	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	mesh->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textEnabled"), 0);
	glEnable(GL_DEPTH_TEST);
}

void GameScene2::RenderText(Mesh* mesh, std::string text, Color color) const {
	if (!mesh || mesh->textureID < 0) {
		return;
	}
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textEnabled"), 1);
	glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textColor"), 1, &color.R);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTexture"), 0);
	for (unsigned i = 0; i < text.length(); ++i) {
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.f is spacing
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textEnabled"), 0);
	glEnable(GL_DEPTH_TEST);
}

void GameScene2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int winWidth, int winHeight) {
	if (!mesh || mesh->textureID <= 0) { //Proper error check return
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
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textEnabled"), 1);
	glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textColor"), 1, &color.R);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	if (mesh != 0) {
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	}
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTexture"), 0);
	for (unsigned i = 0; i < text.length(); ++i) {
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.f is spacing
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textEnabled"), 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void GameScene2::renderObject(Object* obj)
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