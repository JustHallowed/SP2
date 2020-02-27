#include "GhostScene.h"
#include "SceneManager.h"
#include "irrKlang.h"
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

extern Camera camera;
extern double elapsedTime;
extern std::vector<std::pair<bool, double>>* jump;
extern std::vector<std::pair<const char*, double>> *upDown, *leftRight;
using namespace irrklang;
extern ISoundEngine* engine;

double GhostScene::CalcFrameRate() const{
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

void GhostScene::InitLight() const{
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

void GhostScene::InitMeshes(){
	meshList[unsigned int(MESH::HITBOX)] = MeshBuilder::GenerateCuboid(Color(1.f, 1.f, 1.f), 1.f, 1.f, 1.f);
	meshList[unsigned int(MESH::HITSPHERE)] = MeshBuilder::GenerateSphere(Color(1.f, 1.f, 1.f), 16, 16, 1);
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
	meshList[unsigned int(MESH::SMOKE)] = MeshBuilder::GenerateQuad(Color(1.f, 0.f, 0.f), 5.f, 5.f);
	meshList[unsigned int(MESH::SMOKE)]->textureID = LoadTGA("Resources/TGAs/Smoke.tga");
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)]->textureID = LoadTGA("Resources/TGAs/FontOnScreen.tga");

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

	//Base mesh
	meshList[unsigned int(MESH::PLATFORM)] = MeshBuilder::GenerateOBJ("Resources/OBJs/platform.obj");
	meshList[unsigned int(MESH::PLATFORM)]->textureID = LoadTGA("Resources/TGAs/platform.tga");
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

void GhostScene::CreateInstances(){
	createPlatforms(); //create instances for platforms
	createUFOs(); //create instances for ufos
	createRobot1();
}

void GhostScene::Init(){ //Init scene
	glGenVertexArrays(1, &m_vertexArrayID); //Generate a default VAO
	glBindVertexArray(m_vertexArrayID);
	camera.Init(Vector3(0.f, 5.f, 30.f), Vector3(0.f, 5.f, 0.f), Vector3(0.f, 1.f, 0.f));
	InitLight();
	InitMeshes();
	jump->push_back(std::pair<bool, double>(0, 0.0));
	upDown->push_back(std::pair<const char*, double>("none", 0.0));
	leftRight->push_back(std::pair<const char*, double>("none", 0.0));
	smokeGenerator.InitParticles();
	CreateInstances();
	animateDir = showDebugInfo = 1;
	state = showLightSphere = indexUpDown = indexLeftRight = indexJump = 0;
	smokeBounceTime = debugBounceTime = interactBounceTime = lightBounceTime = swingBounceTime = timePressed = timeInScene = 0.0;
	pAngleXZ = pAngle = mainCharAngle = leftUpperAngle = leftLowerAngle = rightUpperAngle = rightLowerAngle = leftArmAngle = leftForearmAngle = rightArmAngle = rightForearmAngle = 0.f;
	inRange[ROBOT_BODY1] = 0;
	interacted[ROBOT_BODY1] = 0;
}

void GhostScene::Exit(Scene* newScene){ //Exit scene
	for(int i = 0; i < int(MESH::NUM_GEOMETRY); ++i){
		if(meshList[i] != 0){
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	if(dynamic_cast<GhostScene*>(newScene) != this){
		newScene->Init();
	} else{
		if(jump != 0){
			delete jump;
		}
		if(upDown != 0){
			delete upDown;
		}
		if(leftRight != 0){
			delete leftRight;
		}
		engine->drop();
	}
}

void GhostScene::Update(double dt, float FOV){ //Update scene
	for(int i = 0; i < 7; ++i){
		if(Application::IsKeyPressed(keys[i])){
			switch(keys[i]){
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
				case '0': {
					SceneManager::getScMan()->SetNextScene(); //Change scene
					printf("\n\n");
					for(auto itr = upDown->begin(); itr != upDown->end(); ++itr){
						std::cout << itr->first << '\t' << itr->second << '\n';
					}
					std::cout << std::endl;
					for(auto itr = leftRight->begin(); itr != leftRight->end(); ++itr){
						std::cout << itr->first << '\t' << itr->second << '\n';
					}
					std::cout << std::endl;
					for(auto itr = jump->begin(); itr != jump->end(); ++itr){
						std::cout << itr->first << '\t' << itr->second << '\n';
					}
				}
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
	if(smokeBounceTime <= elapsedTime && smokeGenerator.currAmt < smokeGenerator.maxAmt){
		Particle* p = smokeGenerator.particlePool[smokeGenerator.GetIndex()];
		p->color = Color(1.f, 0.f, 0.f);
		p->dir = Vector3(0, 1, 0);
		p->life = 1.f;
		p->pos = Vector3(0, 0, 0) + p->dir * 2.5f + Vector3(0.f, 7.5f, 0.f);
		++smokeGenerator.currAmt;
		smokeBounceTime = elapsedTime + 0.2;
	}
	smokeGenerator.UpdateParticles(dt);


	//for(int i = 0; i < NUM_INSTANCES; ++i){										//REMEMBER TO CHECK
	//	if(object[i].getDimension().y == 0) continue;
	//	camera.updateCollision(object[i]);
	//}
	for(int i = 0; i < 5; ++i){
		object[i].addRotation(1, 'y');
	}

	//!testing! if w is pressed, sound effects will be played
	//if (Application::IsKeyPressed('W'))
	//	engine->play2D("Resources/Sound/bell.wav");

	//if (!object[A].isClockwise)
	//{
	//	//do animation
	//	if (condition to turn clockwise)
	//		object[A].setIsClockwise(true);
	//}
	//else if (object[A].isClockwise)
	//{
	//	//do animation
	//	if (condition to turn anti-clockwise)
	//		object[A].setIsClockwise(false);
	//}

	if(object[ROBOT_BODY1].checkDist(camera.target) < 15.f)
	{
		inRange[ROBOT_BODY1] = true;
		if(Application::IsKeyPressed('F') && interactBounceTime <= elapsedTime)
		{
			interacted[ROBOT_BODY1] = !interacted[ROBOT_BODY1];
			interactBounceTime = elapsedTime + 0.4;
			if(interacted[ROBOT_BODY1])
				engine->play2D("Resources/Sound/robot1.wav");
		}
	} else
	{
		inRange[ROBOT_BODY1] = 0;
		interacted[ROBOT_BODY1] = 0;
	}

	//Billboarding for particles
	Vector3 pFrontXZ = Vector3(camera.pos.x, 0.f, camera.pos.z);
	pAngleXZ = Math::RadianToDegree(acos(pFrontXZ.Dot(Vector3(camera.defaultPos.x, 0.f, camera.defaultPos.z)) /
		(pFrontXZ.Length() * Vector3(camera.defaultPos.x, 0.f, camera.defaultPos.z).Length())));
	Vector3 pFront = Vector3(camera.pos.x, camera.pos.y, camera.pos.z);
	pAngle = Math::RadianToDegree(acos(pFront.Dot(Vector3(camera.pos.x, 0.f, camera.pos.z)) /
		(pFront.Length() * Vector3(camera.pos.x, 0.f, camera.pos.z).Length())));
	if(camera.pos.x < 0.f){
		pAngleXZ = 360.f - pAngleXZ;
	}

	UpdateMainChar(dt);

	Mtx44 projection;
	projection.SetToPerspective(FOV, 4.f / 3.f, 0.1f, 1000.f); //FOV value affects cam zoom
	projectionStack.LoadMatrix(projection);
}

void GhostScene::UpdateMainChar(double dt){
	timeInScene += dt;
	UpdateMainTranslateXZ(dt);
	UpdateMainRotateY(dt);
	UpdateMainTranslateY(dt);
}

void GhostScene::UpdateMainTranslateXZ(double dt){ //Move towards or away from target
	if((*upDown)[indexUpDown].first != "none" && timeInScene >= (*upDown)[indexUpDown].second){
		float moveVelocity = ((*upDown)[indexUpDown].first == "up" ? 1.f : -1.f) * 10.f * float(dt);
		Vector3 front = (MainChar::getMainChar().getTarget() - MainChar::getMainChar().getPos()).Normalized();
		MainChar::getMainChar().setPos(MainChar::getMainChar().getPos() + moveVelocity * front);
		MainChar::getMainChar().setTarget(MainChar::getMainChar().getTarget() + moveVelocity * front);
		if(timePressed == 0.0){
			timePressed = elapsedTime;
		}
		if(swingBounceTime <= timePressed){
			if(state){
				leftArmAngle += (animateDir ? 1.25f : -1.25f);
				rightArmAngle += (animateDir ? -1.25f : 1.25f);
				leftUpperAngle = rightArmAngle;
				rightUpperAngle = leftArmAngle;
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
	if(unsigned(indexUpDown) < upDown->size() - 1 && timeInScene >= (*upDown)[indexUpDown + 1].second){
		++indexUpDown;
	}
}

void GhostScene::UpdateMainRotateY(double dt){ //Rotate body, changing facing and hence target
	if((*leftRight)[indexLeftRight].first != "none" && timeInScene >= (*leftRight)[indexLeftRight].second){
		float turnVelocity = ((*leftRight)[indexLeftRight].first == "left" ? 1.f : -1.f) * 100.f * float(dt);
		Vector3 front = (MainChar::getMainChar().getTarget() - MainChar::getMainChar().getPos()).Normalized();
		Mtx44 r;
		r.SetToRotation(turnVelocity, 0.f, 1.f, 0.f);
		front = r * front;
		MainChar::getMainChar().setTarget(MainChar::getMainChar().getPos() + front);
		mainCharAngle += turnVelocity;
	}
	if(unsigned(indexLeftRight) < leftRight->size() - 1 && timeInScene >= (*leftRight)[indexLeftRight + 1].second){
		++indexLeftRight;
	}
}

void GhostScene::UpdateMainTranslateY(double dt){ //Jump, mini jump, double jump
	if((*jump)[indexJump].first == 1 && timeInScene >= (*jump)[indexJump].second && MainChar::getMainChar().getMaxJump() && MainChar::getMainChar().isKeyReleased()){
		MainChar::getMainChar().setGrav(5.f * float(dt));
		MainChar::getMainChar().setJumpHeight(80.f * float(dt));
		MainChar::getMainChar().setJumping(1);
		MainChar::getMainChar().setKeyReleased(0);
		MainChar::getMainChar().reduceMaxJump();
	}
	if((*jump)[indexJump].first == 0 && timeInScene >= (*jump)[indexJump].second){
		MainChar::getMainChar().setKeyReleased(1);
		if(MainChar::getMainChar().isJumping() && MainChar::getMainChar().getJumpHeight() > 0.0f){
			MainChar::getMainChar().setJumpHeight(0.f);
		}
	}
	if(unsigned(indexJump) < jump->size() - 1 && timeInScene >= (*jump)[indexJump + 1].second){
		++indexJump;
	}
	if(MainChar::getMainChar().isJumping()){
		MainChar::getMainChar().setPos(MainChar::getMainChar().getPos() + Vector3(0.f, MainChar::getMainChar().getJumpHeight(), 0.f));
		MainChar::getMainChar().setTarget(MainChar::getMainChar().getTarget() + Vector3(0.f, MainChar::getMainChar().getJumpHeight(), 0.f));
		MainChar::getMainChar().setJumpHeight(MainChar::getMainChar().getJumpHeight() - MainChar::getMainChar().getGrav());
	}
	if(MainChar::getMainChar().getPos().y < 0.0f){
		MainChar::getMainChar().setPos(Vector3(MainChar::getMainChar().getPos().x, 0.f, MainChar::getMainChar().getPos().z));
		MainChar::getMainChar().setTarget(Vector3(MainChar::getMainChar().getTarget().x, 0.f, MainChar::getMainChar().getTarget().z));
		MainChar::getMainChar().setJumpHeight(0.f);
		MainChar::getMainChar().setJumping(0);
		MainChar::getMainChar().setMaxJump(2);
	}
}

void GhostScene::Render(double dt, int winWidth, int winHeight){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.pos.x, camera.pos.y, camera.pos.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	RenderMainChar();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	RenderLight();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 100.f, 0.f);
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderSkybox(!light[0].power);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 100.f, 0.f);
	modelStack.Scale(2.f, 2.f, 2.f);
	RenderSkybox(!light[0].power);
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
	//RenderMesh(meshList[unsigned int(MESH::HITSPHERE)], false);
	//modelStack.PopMatrix();

	//displays hitboxes
	/*for (int i = 0; i < NUM_INSTANCES; ++i)
	{
		if (object[i].getDimension().y > 0)
		{
		modelStack.PushMatrix();
		modelStack.Translate(object[i].getPos().x, object[i].getPos().y, object[i].getPos().z);
		modelStack.Scale(object[i].getDimension().x, object[i].getDimension().y, object[i].getDimension().z);
		RenderMesh(meshList[unsigned int(MESH::HITBOX)], false);
		modelStack.PopMatrix();
		}
	}*/
	//render all objects
	for(int i = 0; i < NUM_INSTANCES; ++i)
	{
		if(object[i].getParent() == nullptr)
		{
			modelStack.PushMatrix();
			renderObject(&object[i]);
			modelStack.PopMatrix();
		}
	}

	for(Particle* p: smokeGenerator.particlePool){
		if(p->life > 0.0f){
			modelStack.PushMatrix();
			modelStack.Translate(p->pos.x, p->pos.y, p->pos.z);
			modelStack.Rotate(pAngleXZ, 0.f, 1.f, 0.f);
			modelStack.Rotate(-pAngle, 1.f, 0.f, 0.f);
			RenderMesh(meshList[unsigned int(MESH::SMOKE)], 0, p->life);
			modelStack.PopMatrix();
		}
	}

	std::ostringstream ss;
	if(showDebugInfo){
		ss << std::fixed << std::setprecision(5);
		ss << "Replay time: " << timeInScene;
		RenderTextOnScreen(getTextMesh(), ss.str(), Color(1.f, .5f, .6f), 3.2f, .2f, 0.f, winWidth, winHeight);
	}
	if(inRange[ROBOT_BODY1] && !interacted[ROBOT_BODY1])
		RenderTextOnScreen(getTextMesh(), "Press [F] to talk", Color(0.5f, 0.5, 1.f), 4.f, 8.f, 8.f, winWidth, winHeight);
	if(inRange[ROBOT_BODY1] && interacted[ROBOT_BODY1]){
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RenderMeshOnScreen(getTextMesh(), 60.f, 20.f, 80.f, 20.f, winWidth, winHeight);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ss << "Wow! These cars! ";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 6.f, winWidth, winHeight);
		ss.str("");
		ss << "They're awesome!";
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.2f, 0.8f, 1.f), 4.f, 7.f, 5.f, winWidth, winHeight);
		ss.str("");
	}
}

void GhostScene::RenderMainChar(){
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

void GhostScene::RenderLight(){
	if(light[0].type == Light::LIGHT_TYPE::DIRECTIONAL){
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].position_cameraspace"), 1, &lightDirection_cameraspace.x);
	} else if(light[0].type == Light::LIGHT_TYPE::SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].position_cameraspace"), 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].spotDirection"), 1, &spotDirection_cameraspace.x);
	} else{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lights[0].position_cameraspace"), 1, &lightPosition_cameraspace.x);
	}
	if(showLightSphere){
		modelStack.PushMatrix();
		modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
		modelStack.Scale(2.f, 2.f, 2.f);
		RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
	}
}

void GhostScene::RenderMesh(Mesh* mesh, bool enableLight, GLfloat alpha) const{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MVP"), 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MV"), 1, GL_FALSE, &modelView.a[0]);
	if(enableLight){
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "MV_inverse_transpose"), 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "material.kAmbient"), 1, &mesh->material.kAmbient.r);
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "material.kDiffuse"), 1, &mesh->material.kDiffuse.r);
		glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "material.kSpecular"), 1, &mesh->material.kSpecular.r);
		glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "material.kShininess"), mesh->material.kShininess);
	} else{
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 0);
	}
	if(mesh->textureID > 0){
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTexture"), 0);
	} else{
		glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 0);
	}
	glUniform1f(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "alpha"), alpha);
	mesh->Render(); //Shld only be called once in the whole function
}

void GhostScene::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY, int winWidth, int winHeight){
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

void GhostScene::RenderSkybox(bool lightSwitch){
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

void GhostScene::RenderAnimation(Mesh* mesh, std::string text, Color color) const{
	if(!mesh || mesh->textureID < 0){
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

void GhostScene::RenderText(Mesh* mesh, std::string text, Color color) const{
	if(!mesh || mesh->textureID < 0){
		return;
	}
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textEnabled"), 1);
	glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textColor"), 1, &color.R);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTexture"), 0);
	for(unsigned i = 0; i < text.length(); ++i){
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

void GhostScene::createPlatforms(){
	//5 copies of platform
	object[PLATFORM1].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM1].setTranslation(0, 0.5, 0);
	object[PLATFORM1].setScale(4);
	object[PLATFORM1].setDimension(40, 40, 40);

	object[PLATFORM2].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM2].setTranslation(70, 0.5, 70);
	object[PLATFORM2].setScale(4);
	object[PLATFORM2].setDimension(40, 40, 40);

	object[PLATFORM3].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM3].setTranslation(-70, 0.5, 70);
	object[PLATFORM3].setScale(4);
	object[PLATFORM3].setDimension(40, 40, 40);

	object[PLATFORM4].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM4].setTranslation(70, 0.5, -70);
	object[PLATFORM4].setScale(4);
	object[PLATFORM4].setDimension(40, 40, 40);

	object[PLATFORM5].setMesh(meshList[unsigned int(MESH::PLATFORM)]);
	object[PLATFORM5].setTranslation(-70, 0.5, -70);
	object[PLATFORM5].setScale(4);
	object[PLATFORM5].setDimension(40, 40, 40);
}

void GhostScene::createUFOs(){
	//5 copies of ufo in ref to individual platform
	object[UFO_BASE1].setMesh(meshList[unsigned int(MESH::UFO_BASE)]);
	object[UFO_BASE1].setTranslation(0.f, 0.6f, 0.f);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM1], &object[UFO_BASE1], true, true);

	object[UFO_PURPLE1].setMesh(meshList[unsigned int(MESH::UFO_PURPLE)]);
	object[UFO_PURPLE1].setTranslation(0.f, 0.6f, 0.f);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM2], &object[UFO_PURPLE1], true, true);

	object[UFO_RED1].setMesh(meshList[unsigned int(MESH::UFO_RED)]);
	object[UFO_RED1].setTranslation(0.f, 0.6f, 0.f);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM3], &object[UFO_RED1], true, true);

	object[UFO_BLUE1].setMesh(meshList[unsigned int(MESH::UFO_BLUE)]);
	object[UFO_BLUE1].setTranslation(0.f, 0.6f, 0.f);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM4], &object[UFO_BLUE1], true, true);

	object[UFO_PINK1].setMesh(meshList[unsigned int(MESH::UFO_PINK)]);
	object[UFO_PINK1].setTranslation(0.f, 0.6f, 0.f);
	//ufo in ref to platform
	Object::bind(&object[PLATFORM5], &object[UFO_PINK1], true, true);
}

void GhostScene::createRobot1(){
	//robot parts for 1 robot
	object[ROBOT_BODY1].setMesh(meshList[unsigned int(MESH::ROBOT_BODY)]);
	object[ROBOT_BODY1].setTranslation(50.f, 5.2f, 50.f);
	object[ROBOT_BODY1].setScale(2);
	object[ROBOT_BODY1].setDimension(6, 15, 6);

	object[ROBOT_ARM1].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
	object[ROBOT_ARM1].setTranslation(-1.f, 2.f, 0.f);
	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_ARM1], true, true);

	object[ROBOT_ARM2].setMesh(meshList[unsigned int(MESH::ROBOT_ARM)]);
	object[ROBOT_ARM2].setTranslation(1.f, 2.f, 0.f);
	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_ARM2], true, true);

	object[ROBOT_FOREARM1].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
	object[ROBOT_FOREARM1].setTranslation(0.f, -1.f, 0.f);
	Object::bind(&object[ROBOT_ARM1], &object[ROBOT_FOREARM1], true, true);

	object[ROBOT_FOREARM2].setMesh(meshList[unsigned int(MESH::ROBOT_FOREARM)]);
	object[ROBOT_FOREARM2].setRotation(190, 'y');
	object[ROBOT_FOREARM2].setTranslation(0.f, -1.f, 0.f);
	Object::bind(&object[ROBOT_ARM2], &object[ROBOT_FOREARM2], true, true);

	object[ROBOT_UPPERLEG1].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
	object[ROBOT_UPPERLEG1].setTranslation(-0.45f, -0.05f, 0.f);
	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_UPPERLEG1], true, true);

	object[ROBOT_UPPERLEG2].setMesh(meshList[unsigned int(MESH::ROBOT_UPPERLEG)]);
	object[ROBOT_UPPERLEG2].setTranslation(0.45f, -0.05f, 0.f);
	Object::bind(&object[ROBOT_BODY1], &object[ROBOT_UPPERLEG2], true, true);

	object[ROBOT_LOWERLEG1].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
	object[ROBOT_LOWERLEG1].setTranslation(0.f, -1.15f, 0.f);
	Object::bind(&object[ROBOT_UPPERLEG1], &object[ROBOT_LOWERLEG1], true, true);

	object[ROBOT_LOWERLEG2].setMesh(meshList[unsigned int(MESH::ROBOT_LOWERLEG)]);
	object[ROBOT_LOWERLEG2].setTranslation(0.f, -1.15f, 0.f);
	Object::bind(&object[ROBOT_UPPERLEG2], &object[ROBOT_LOWERLEG2], true, true);
}

void GhostScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, int winWidth, int winHeight){
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
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textEnabled"), 1);
	glUniform3fv(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "textColor"), 1, &color.R);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "lightEnabled"), 0);
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTextureEnabled"), 1);
	glActiveTexture(GL_TEXTURE0);
	if(mesh != 0){
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	}
	glUniform1i(glGetUniformLocation(ShaderManager::getShaderMan().getProgID(), "colorTexture"), 0);
	for(unsigned i = 0; i < text.length(); ++i){
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

void GhostScene::renderObject(Object* obj){
	if(obj->isRender() && obj->getMesh() != nullptr)
	{
		modelStack.Translate(obj->getTranslation().x, obj->getTranslation().y, obj->getTranslation().z);
		if(obj->getChild().size() != 0)
		{
			for(unsigned int i = 0; i < obj->getChild().size(); ++i)
			{
				modelStack.PushMatrix();
				if(obj->getChild()[i]->followParentRotation())//if obj follows parent's rotation (for joints etc)
				{
					if(obj->getAngle().x != 0)
						modelStack.Rotate(obj->getAngle().x, 1, 0, 0);
					if(obj->getAngle().y != 0)
						modelStack.Rotate(obj->getAngle().y, 0, 1, 0);
					if(obj->getAngle().z != 0)
						modelStack.Rotate(obj->getAngle().z, 0, 0, 1);
				}
				if(obj->getChild()[i]->followParentScale())
					modelStack.Scale(obj->getScale().x, obj->getScale().y, obj->getScale().z);
				renderObject(obj->getChild()[i]);
				modelStack.PopMatrix();
			}
		}
		if(obj->getAngle().x != 0)
			modelStack.Rotate(obj->getAngle().x, 1, 0, 0);
		if(obj->getAngle().y != 0)
			modelStack.Rotate(obj->getAngle().y, 0, 1, 0);
		if(obj->getAngle().z != 0)
			modelStack.Rotate(obj->getAngle().z, 0, 0, 1);

		modelStack.Scale(obj->getScale().x, obj->getScale().y, obj->getScale().z);
		RenderMesh(obj->getMesh(), true);
	}
}