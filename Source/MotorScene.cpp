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
#include "MainChar.h"

extern Camera camera;
extern double elapsedTime;

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

void MotorScene::GetNameScoreData(bool showType) const{
	scoreMan->addNameScore(std::make_pair("Sabin", 0));
	scoreMan->sortNameScoreData();
	scoreMan->showNameScoreData(showType);
}

void MotorScene::InitLight() const{
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "lights[0].type"), GLint(light[0].type));
	glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "lights[0].color"), 1, &light[0].color.R);
	glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].power"), light[0].power);
	glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].kC"), light[0].kC);
	glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].kL"), light[0].kL);
	glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].kQ"), light[0].kQ);
	glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "lights[0].spotDirection"), 1, &light[0].spotDirection.x);
	glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].cosCutoff"), light[0].cosCutoff);
	glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].cosInner"), light[0].cosInner);
	glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].exponent"), light[0].exponent);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "numLights"), 1);
}

void MotorScene::InitMeshes(){
	meshList[unsigned int(MESH::BULLET)] = MeshBuilder::GenerateQuad(Color(1.f, 0.f, 0.f), 5.f, 5.f);
	meshList[unsigned int(MESH::LEFT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::LEFT)]->textureID = LoadTGA("Resources/TGAs/Wood.tga");
	meshList[unsigned int(MESH::RIGHT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::RIGHT)]->textureID = LoadTGA("Resources/TGAs/Wood.tga");
	meshList[unsigned int(MESH::FRONT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::FRONT)]->textureID = LoadTGA("Resources/TGAs/Wood.tga");
	meshList[unsigned int(MESH::BACK)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::BACK)]->textureID = LoadTGA("Resources/TGAs/Wood.tga");
	meshList[unsigned int(MESH::TOP)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::TOP)]->textureID = LoadTGA("Resources/TGAs/Wood.tga");
	meshList[unsigned int(MESH::BOTTOM)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::BOTTOM)]->textureID = LoadTGA("Resources/TGAs/Wood.tga");
	meshList[unsigned int(MESH::LIGHT_SPHERE)] = MeshBuilder::GenerateSphere(Color(1.f, 1.f, 1.f), 20, 20, 1.f);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)] = MeshBuilder::GenerateText(16, 16);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)]->textureID = LoadTGA("Resources/TGAs/FontOnScreen.tga");

	meshList[unsigned int(MESH::ARM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/MainCharArm.obj");
	meshList[unsigned int(MESH::ARM)]->textureID = LoadTGA("Resources/TGAs/MainChar.tga");
	meshList[unsigned int(MESH::FOREARM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/MainCharForearm.obj");
	meshList[unsigned int(MESH::FOREARM)]->textureID = LoadTGA("Resources/TGAs/MainChar.tga");
	meshList[unsigned int(MESH::BODY)] = MeshBuilder::GenerateOBJ("Resources/OBJs/MainCharBody.obj");
	meshList[unsigned int(MESH::BODY)]->textureID = LoadTGA("Resources/TGAs/MainChar.tga");
	meshList[unsigned int(MESH::LOWER_LEG)] = MeshBuilder::GenerateOBJ("Resources/OBJs/MainCharLowerLeg.obj");
	meshList[unsigned int(MESH::LOWER_LEG)]->textureID = LoadTGA("Resources/TGAs/MainChar.tga");
	meshList[unsigned int(MESH::UPPER_LEG)] = MeshBuilder::GenerateOBJ("Resources/OBJs/MainCharUpperLeg.obj");
	meshList[unsigned int(MESH::UPPER_LEG)]->textureID = LoadTGA("Resources/TGAs/MainChar.tga");
}

void MotorScene::Init(){ //Init scene
	glGenVertexArrays(1, &m_vertexArrayID); //Generate a default VAO
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_CULL_FACE); //Enable back-face culling
	glEnable(GL_BLEND); //Enable blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST); //Enable depth test
	shaderMan = new ShaderManager;
	scoreMan = new ScoreManager;
	GetNameScoreData(0);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	camera.Init(Vector3(0.f, 5.f, 30.f), Vector3(0.f, 5.f, 0.f), Vector3(0.f, 1.f, 0.f));
	InitLight();
	InitMeshes();
	bulletGenerator.InitParticles();
	animateDir = showDebugInfo = 1;
	state = showLightSphere = 0;
	bulletBounceTime = debugBounceTime = lightBounceTime = swingBounceTime = timePressed = 0.0;
	particleAngle = mainCharAngle = leftUpperAngle = leftLowerAngle = rightUpperAngle = rightLowerAngle = leftArmAngle = leftForearmAngle = rightArmAngle = rightForearmAngle = 0.f;
}

void MotorScene::Exit(Scene* newScene){ //Exit scene
	for(int i = 0; i < int(MESH::NUM_GEOMETRY); ++i){
		if(meshList[i] != 0){
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	delete shaderMan;
	delete scoreMan;
	if(dynamic_cast<MotorScene*>(newScene) != this){
		newScene->Init();
	}
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
					glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].power"), light[0].power);
					break;
				}
				case '9': { //On the light
					light[0].power = 1.f;
					glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "lights[0].power"), light[0].power);
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
	if(Application::IsKeyPressed(VK_SHIFT) && debugBounceTime <= elapsedTime){ //Show/Hide debug info
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

	//Billboarding for particles
	Vector3 particleFront = Vector3(camera.pos.x, 0.f, camera.pos.z);
	particleAngle = Math::RadianToDegree(acos(particleFront.Dot(Vector3(0.f, 0.f, 30.f)) / (particleFront.Length() * Vector3(0.f, 0.f, 30.f).Length())));
	if(camera.pos.x < 0.f){
		particleAngle = 360.f - particleAngle;
	}

	UpdateMainChar(dt);

	Mtx44 projection;
	projection.SetToPerspective(FOV, 4.f / 3.f, 0.1f, 1000.f); //FOV value affects cam zoom
	projectionStack.LoadMatrix(projection);
}

void MotorScene::UpdateMainChar(double dt){
	if(Application::IsKeyPressed(VK_UP) ^ Application::IsKeyPressed(VK_DOWN)){
		if(timePressed == 0.0){
			timePressed = elapsedTime;
		}
		if(swingBounceTime <= timePressed){
			if(state){
				leftArmAngle += (animateDir ? 1.25f : -1.25f);
				rightArmAngle += (animateDir ? -1.25f : 1.25f);
				leftUpperAngle = rightArmAngle;
				rightUpperAngle = leftArmAngle;
				//if(!animateDir){
				//	if(leftUpperAngle < 0.f){
				//		leftLowerAngle -= 2.f;
				//	} else if(leftUpperAngle > 0.f){
				//		leftLowerAngle += 2.f;
				//	}
				//} else{
				//	if(rightUpperAngle < 0.f){
				//		rightLowerAngle -= 2.f;
				//	} else if(rightUpperAngle > 0.f){
				//		rightLowerAngle += 2.f;
				//	}
				//}
				if((animateDir && leftArmAngle == 20.f) || (!animateDir && leftArmAngle == -30.f)){
					animateDir = !animateDir;
				}
			} else{
				leftArmAngle += (animateDir ? -1.5f : 1.f);
				rightArmAngle += (animateDir ? 1.f : -1.5f);
				leftUpperAngle = rightArmAngle;
				rightUpperAngle = leftArmAngle;
				if(leftArmAngle == -30.f){
					state = 1;
					timePressed = elapsedTime;
				}
			}
			swingBounceTime = timePressed + 0.015;
		}
		timePressed += dt;
	} else{
		timePressed = 0.0;
		if(leftArmAngle){ //Go back to standing pos
			leftArmAngle += (leftArmAngle < 0.f ? 1.25f : -1.25f);
			rightArmAngle += (rightArmAngle > 0.f ? -1.25f : 1.25f);
			leftUpperAngle = rightArmAngle;
			rightUpperAngle = leftArmAngle;
		}
	}

	//Move forward or backward
	if(Application::IsKeyPressed(VK_UP) ^ Application::IsKeyPressed(VK_DOWN)){
		float moveVelocity = float(Application::IsKeyPressed(VK_UP) - Application::IsKeyPressed(VK_DOWN)) * 10.f * float(dt);
		Vector3 front = (MainChar::getMainChar().getTarget() - MainChar::getMainChar().getPos()).Normalized();
		MainChar::getMainChar().setPos(MainChar::getMainChar().getPos() + moveVelocity * front);
		MainChar::getMainChar().setTarget(MainChar::getMainChar().getTarget() + moveVelocity * front);
	}

	//Move left or right
	if(Application::IsKeyPressed(VK_LEFT) ^ Application::IsKeyPressed(VK_RIGHT)){
		float turnVelocity = float(Application::IsKeyPressed(VK_LEFT) - Application::IsKeyPressed(VK_RIGHT)) * 100.f * float(dt);
		Vector3 front = (MainChar::getMainChar().getTarget() - MainChar::getMainChar().getPos()).Normalized();
		mainCharAngle += turnVelocity;
		Mtx44 r;
		r.SetToRotation(turnVelocity, 0.f, 1.f, 0.f);
		front = r * front;
		MainChar::getMainChar().setTarget(MainChar::getMainChar().getPos() + front);
	}

	//Jump, mini jump, double jump
	if(Application::IsKeyPressed(VK_SPACE) && MainChar::getMainChar().getMaxJump() && MainChar::getMainChar().isKeyReleased()){
		MainChar::getMainChar().setJumpHeight(1.3f);
		MainChar::getMainChar().setJumping(1);
		MainChar::getMainChar().setKeyReleased(0);
		MainChar::getMainChar().reduceMaxJump();
	}
	if(!Application::IsKeyPressed(VK_SPACE)){
		MainChar::getMainChar().setKeyReleased(1);
		if(MainChar::getMainChar().isJumping() && MainChar::getMainChar().getJumpHeight() > 0.0f){
			MainChar::getMainChar().setJumpHeight(0.f);
		}
	}
	if(MainChar::getMainChar().isJumping()){
		MainChar::getMainChar().setPos(MainChar::getMainChar().getPos() + Vector3(0.f, MainChar::getMainChar().getJumpHeight(), 0.f));
		MainChar::getMainChar().setTarget(MainChar::getMainChar().getTarget() + Vector3(0.f, MainChar::getMainChar().getJumpHeight(), 0.f));
		MainChar::getMainChar().setJumpHeight(MainChar::getMainChar().getJumpHeight() - MainChar::getMainChar().getGrav());
	}
	if(MainChar::getMainChar().getPos().y < 0.0f){
		MainChar::getMainChar().setPos(Vector3(MainChar::getMainChar().getPos().x, 0.f, MainChar::getMainChar().getPos().z));
		MainChar::getMainChar().setJumpHeight(0.f);
		MainChar::getMainChar().setJumping(0);
		MainChar::getMainChar().setMaxJump(2);
	}
}

void MotorScene::Render(double dt, int winWidth, int winHeight){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.pos.x, camera.pos.y, camera.pos.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	RenderMainChar();
	RenderLight();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 100.f, 0.f);
		modelStack.Scale(2.f, 2.f, 2.f);
		RenderSkybox(!light[0].power);
	modelStack.PopMatrix();

	shaderMan->UseNewShaders(0, 1);
	for(Particle* p: bulletGenerator.particlePool){
		if(p->life > 0.0f){
			delete meshList[unsigned int(MESH::BULLET)];
			meshList[unsigned int(MESH::BULLET)] = MeshBuilder::GenerateQuad(p->color, 5.f, 5.f);
			modelStack.PushMatrix();
				modelStack.Translate(p->pos.x, p->pos.y, p->pos.z);
				modelStack.Rotate(particleAngle, 0.f, 1.f, 0.f);
				RenderParticle(meshList[unsigned int(MESH::BULLET)], p->life);
			modelStack.PopMatrix();
		}
	}

	shaderMan->UseNewShaders(1, 0);
	InitLight();
	std::ostringstream ss;
	if(showDebugInfo){
		ss << std::fixed << std::setprecision(2);
		ss << "MainChar's target: " << MainChar::getMainChar().getTarget().x << ", " << MainChar::getMainChar().getTarget().y << ", " << MainChar::getMainChar().getTarget().z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 29.f, winWidth, winHeight);
		ss.str("");
		ss << "MainChar's pos: " << MainChar::getMainChar().getPos().x << ", " << MainChar::getMainChar().getPos().y << ", " << MainChar::getMainChar().getPos().z;
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
}

void MotorScene::RenderMainChar(){
	modelStack.PushMatrix();
		modelStack.Translate(MainChar::getMainChar().getPos().x, MainChar::getMainChar().getPos().y + 5.15f, MainChar::getMainChar().getPos().z);
		modelStack.Rotate(mainCharAngle, 0.f, 1.f, 0.f);
		modelStack.Scale(2.f, 2.f, 2.f);
		RenderMesh(meshList[unsigned int(MESH::BODY)], 1);

		modelStack.PushMatrix();
			modelStack.Translate(1.f, 2.f, 0.f);
			modelStack.Rotate(leftArmAngle, 1.f, 0.f, 0.f);
			RenderMesh(meshList[unsigned int(MESH::ARM)], 1);
			modelStack.PushMatrix();
				modelStack.Translate(0.f, -1.f, 0.f);
				modelStack.Rotate(leftForearmAngle, 1.f, 0.f, 0.f);
				modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
				RenderMesh(meshList[unsigned int(MESH::FOREARM)], 1);
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(-1.f, 2.f, 0.f);
			modelStack.Rotate(rightArmAngle, 1.f, 0.f, 0.f);
			RenderMesh(meshList[unsigned int(MESH::ARM)], 1);
			modelStack.PushMatrix();
				modelStack.Translate(0.f, -1.f, 0.f);
				modelStack.Rotate(rightForearmAngle, 1.f, 0.f, 0.f);
				RenderMesh(meshList[unsigned int(MESH::FOREARM)], 1);
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0.45f, -0.05f, 0.f);
			modelStack.Rotate(leftUpperAngle, 1.f, 0.f, 0.f);
			modelStack.PushMatrix();
				modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
				RenderMesh(meshList[unsigned int(MESH::UPPER_LEG)], 1);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
				modelStack.Translate(0.f, -1.15f, 0.f);
				modelStack.Rotate(leftLowerAngle, 1.f, 0.f, 0.f);
				RenderMesh(meshList[unsigned int(MESH::LOWER_LEG)], 1);
			modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(-0.45f, -0.05f, 0.f);
			modelStack.Rotate(rightUpperAngle, 1.f, 0.f, 0.f);
			modelStack.PushMatrix();
				RenderMesh(meshList[unsigned int(MESH::UPPER_LEG)], 1);
			modelStack.PopMatrix();
			modelStack.PushMatrix();
				modelStack.Translate(0.f, -1.15f, 0.f);
				modelStack.Rotate(rightLowerAngle, 1.f, 0.f, 0.f);
				RenderMesh(meshList[unsigned int(MESH::LOWER_LEG)], 1);
			modelStack.PopMatrix();
		modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void MotorScene::RenderLight(){
	if(light[0].type == Light::LIGHT_TYPE::DIRECTIONAL){
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "lights[0].position_cameraspace"), 1, &lightDirection_cameraspace.x);
	} else if(light[0].type == Light::LIGHT_TYPE::SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "lights[0].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "lights[0].spotDirection"), 1, &spotDirection_cameraspace.x);
	} else{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "lights[0].position_cameraspace"), 1, &lightPosition_cameraspace.x);
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
	glUniformMatrix4fv(glGetUniformLocation(shaderMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "particleLife"), pLife);
	mesh->Render();
}

void MotorScene::RenderMesh(Mesh* mesh, bool enableLight) const{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(shaderMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(shaderMan->getProgID(), "MV"), 1, GL_FALSE, &modelView.a[0]);
	if(enableLight){
		glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "lightEnabled"), 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(glGetUniformLocation(shaderMan->getProgID(), "MV_inverse_transpose"), 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "material.kAmbient"), 1, &mesh->material.kAmbient.r);
		glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "material.kDiffuse"), 1, &mesh->material.kDiffuse.r);
		glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "material.kSpecular"), 1, &mesh->material.kSpecular.r);
		glUniform1f(glGetUniformLocation(shaderMan->getProgID(), "material.kShininess"), mesh->material.kShininess);
	} else{
		glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "lightEnabled"), 0);
	}
	if(mesh->textureID > 0){
		glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTextureEnabled"), 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTexture"), 0);
	} else{
		glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTextureEnabled"), 0);
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
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "textEnabled"), 1);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTexture"), 0);

	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(shaderMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	mesh->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "textEnabled"), 0);
	glEnable(GL_DEPTH_TEST);
}

void MotorScene::RenderText(Mesh* mesh, std::string text, Color color) const{
	if(!mesh || mesh->textureID < 0){
		return;
	}
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "textEnabled"), 1);
	glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "textColor"), 1, &color.R);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTexture"), 0);
	for(unsigned i = 0; i < text.length(); ++i){
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.f is spacing
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(glGetUniformLocation(shaderMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "textEnabled"), 0);
	glEnable(GL_DEPTH_TEST);
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
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "textEnabled"), 1);
	glUniform3fv(glGetUniformLocation(shaderMan->getProgID(), "textColor"), 1, &color.R);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	if(mesh != 0){
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	}
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "colorTexture"), 0);
	for(unsigned i = 0; i < text.length(); ++i){
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.f is spacing
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(glGetUniformLocation(shaderMan->getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(glGetUniformLocation(shaderMan->getProgID(), "textEnabled"), 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}