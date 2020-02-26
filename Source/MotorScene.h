#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "ScoreSystem.h"
#include "Object.h"
#include "Vehicle.h"


class MotorScene final: public Scene{
	enum class MESH {
		HITBOXWHITE, HITBOXRED, BULLET, LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, UFO_BASE, UFO_PURPLE, UFO_RED, UFO_BLUE, UFO_PINK, GY_CAR, EH_CAR, LF_CAR, YW_CAR, PLATFORM, ROBOT_BODY, ROBOT_ARM, ROBOT_FOREARM, ROBOT_UPPERLEG, ROBOT_LOWERLEG, TEXTBOX , SMOKE, ARM,FOREARM,UPPER_LEG,LOWER_LEG,BODY, NUM_GEOMETRY,
	};
	enum OBJECT_INSTANCES{
		PLATFORM1,
		PLATFORM2, 
		PLATFORM3, 
		PLATFORM4, 
		PLATFORM5,
		PLATFORM6,
		PLATFORM7,
		PLATFORM8, 
		PLATFORM9,

		UFO_BASE1,
		UFO_PURPLE1,
		UFO_RED1, 
		UFO_BLUE1, 
		UFO_PINK1,

		GY_CAR1,
		EH_CAR1,
		LF_CAR1,
		YW_CAR1,

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
	bool animateDir, showDebugInfo, showLightSphere, state,splitScreen;
	bool inRange[NUM_INSTANCES], interacted[NUM_INSTANCES];
	char keys[7] = {'1', '2', '3', '4', '8', '9', '0'};
	double smokeBounceTime, debugBounceTime, interactBounceTime, lightBounceTime, swingBounceTime, timePressed,splitBounceTime;
	double CalcFrameRate() const;
	float pAngleXZ, pAngle, mainCharAngle, leftUpperAngle, leftLowerAngle, rightUpperAngle, rightLowerAngle, leftArmAngle, leftForearmAngle, rightArmAngle, rightForearmAngle;
	Object object[NUM_INSTANCES];
	Light light[7]{
		Light('d', 0.f, 192.f, 0.f, 1.f, 1.f, 1.f, Vector3(0, 1, 0)), //ceilling light
		Light('s', 13.f, 6.f, -8.f, 1.f, 1.f, 0.f, Vector3(0, 0, 1)), //eh car
		Light('s', 7.f, 6.f, -8.f, 1.f, 1.f, 0.f, Vector3(0, 0, 1)),//eh car
		Light('s', -48.f, 6.f, 72.f, 1.f, 0.6f, 0.f, Vector3(1, 0, 0)), //lf car
		Light('s', -48.f, 6.f, 68.f, 1.f, 0.6f, 0.f, Vector3(1, 0, 0)), //lf car
		Light('s', -84.f, 6.f, -11.f, 1.f, 0.f, 0.f, Vector3(0, 0, 1)), //yw car 
		Light('s', -76.f, 6.f, -11.f, 1.f, 0.f, 0.f, Vector3(0, 0, 1)), //yw car 
	}; 


	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter smokeGenerator;
	ScoreManager* scoreMan;
	unsigned m_vertexArrayID;
	void InitMeshes(), CreateInstances(), RenderLight(), RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void InitLight() const, RenderParticle(Mesh*, GLfloat) const, RenderMesh(Mesh*, bool, GLfloat = 1.f) const, RenderAnimation(Mesh*, int) const,RenderAnimationOnScreen(Mesh*,int,float,float,float,int,int), RenderText(Mesh*, std::string, Color) const, renderObject(Object* obj);
	void createPlatforms(), createUFOs(), createRobot1(), createVehicles(), createRobot2(), createRobot3(),UpdateMainChar(double),UpdateMainTranslateXZ(double),UpdateMainRotateY(double),UpdateMainTranslateY(double), RenderMainChar(), GetNameScoreData(bool) const, RenderAnimation(Mesh*, std::string, Color) const;;
	void npcCheck(int instance, const char* audioFileName);
	void carCheck(int instance, const char* audioFileName);

public:
	~MotorScene() override{}
	void Init() override, Update(double, float) override, Render(double, int, int) override, Exit(Scene*) override;
	void RenderScreen1(double, int, int), RenderScreen2(double, int, int);
};