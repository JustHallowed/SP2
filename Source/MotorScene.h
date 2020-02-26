#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ShaderManager.hpp"
#include "ParticleSystem.h"
#include "Object.h"

class MotorScene final: public Scene{
	enum class MESH {
		HITBOX, HITSPHERE, BULLET, LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, UFO_BASE, UFO_PURPLE, UFO_RED, UFO_BLUE, UFO_PINK, PLATFORM, ROBOT_BODY, ROBOT_ARM, ROBOT_FOREARM, ROBOT_UPPERLEG, ROBOT_LOWERLEG, TEXTBOX, SPRITE1, SPRITE2, NUM_GEOMETRY,
	};
	enum OBJECT_INSTANCES
	{
		PLATFORM1,
		PLATFORM2, 
		PLATFORM3, 
		PLATFORM4, 
		PLATFORM5,

		UFO_BASE1,
		UFO_PURPLE1,
		UFO_RED1, 
		UFO_BLUE1, 
		UFO_PINK1,

		ROBOT_BODY1,
		ROBOT_ARM1,
		ROBOT_ARM2,
		ROBOT_FOREARM1,
		ROBOT_FOREARM2,
		ROBOT_UPPERLEG1,
		ROBOT_UPPERLEG2,
		ROBOT_LOWERLEG1,
		ROBOT_LOWERLEG2,

		ROBOT_BODY2,
		ROBOT_ARM3,
		ROBOT_ARM4,
		ROBOT_FOREARM3,
		ROBOT_FOREARM4,
		ROBOT_UPPERLEG3,
		ROBOT_UPPERLEG4,
		ROBOT_LOWERLEG3,
		ROBOT_LOWERLEG4,

		ROBOT_BODY3,
		ROBOT_ARM5,
		ROBOT_ARM6,
		ROBOT_FOREARM5,
		ROBOT_FOREARM6,
		ROBOT_UPPERLEG5,
		ROBOT_UPPERLEG6,
		ROBOT_LOWERLEG5,
		ROBOT_LOWERLEG6,

		NUM_INSTANCES,
	};
	bool showDebugInfo, showLightSphere, splitScreen, menuActive;
	bool inRange[NUM_INSTANCES], interacted[NUM_INSTANCES];
	char keys[7] = {'1', '2', '3', '4', '8', '9', '0'};
	double bulletBounceTime, debugBounceTime, lightBounceTime, interactBounceTime, splitBounceTime;
	double CalcFrameRate() const;
	int Ani1, Ani2;
	float menuR[3], menuG[3], menuWordSize[3];
	bool menuLimit[3];
	Object object[NUM_INSTANCES];
	Light light[1]{Light(0.f, 192.f, 0.f)};
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter bulletGenerator;
	ShaderManager* shMan;
	unsigned m_vertexArrayID;
	int CurrentSelection = 2;
	void InitMeshes(), CreateInstances(), RenderLight(), RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void InitLight() const, RenderParticle(Mesh*, GLfloat) const, RenderMesh(Mesh*, bool) const, RenderAnimation(Mesh*, int) const,RenderAnimationOnScreen(Mesh*,int, float, float, float, int, int), RenderText(Mesh*, std::string, Color) const, renderObject(Object* obj);
	void createPlatforms(), createUFOs(), createRobot1(), createRobot2(), createRobot3();
	void npcCheck(OBJECT_INSTANCES instance, const char* audioFileName);
	void MenuInput();
public:
	~MotorScene() override{}
	void Init() override, Update(double, float) override, Render(double, int, int) override, Exit(Scene*) override;
	void RenderScreen1(double, int, int), RenderScreen2(double, int, int), RenderMenu(double, int, int);
};