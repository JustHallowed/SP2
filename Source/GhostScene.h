#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "ScoreSystem.h"
#include "Object.h"
#include "Vehicle.h"

class GhostScene final: public Scene{
	enum class MESH {
		HITBOXWHITE, HITBOXRED, BULLET, LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE,
		UFO_BASE, UFO_PURPLE, UFO_RED, UFO_BLUE, UFO_PINK, GY_CAR, EH_CAR, LF_CAR, YW_CAR, PLATFORM,
		ROBOT_BODY, ROBOT_ARM, ROBOT_FOREARM, ROBOT_UPPERLEG, ROBOT_LOWERLEG,
		SMOKE, ARM, FOREARM, UPPER_LEG, LOWER_LEG, BODY, SPRITE1, STAGE, STAND, SPEAKER, TEXTBOX, NUM_GEOMETRY
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

		STAGE1,
		STAND1,

		SPEAKER1,
		SPEAKER2,

		NUM_INSTANCES,
	};
	bool animateDir, replay, showDebugInfo, showLightSphere, state, inRange[NUM_INSTANCES], interacted[NUM_INSTANCES];
	double cullBounceTime, debugBounceTime, interactBounceTime, lightBounceTime, polyBounceTime, replayTime, replayBounceTime, smokeBounceTime, swingBounceTime, timePressed;
	double CalcFrameRate() const;
	float pAngleXZ, pAngle, mainCharAngle, leftUpperAngle, leftLowerAngle, rightUpperAngle, rightLowerAngle, leftArmAngle, leftForearmAngle, rightArmAngle, rightForearmAngle;
	int Ani1, Switch, indexUpDown, indexLeftRight, indexJump;
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
	unsigned m_vertexArrayID;
	void InitMeshes(), CreateInstances(), RenderLight(), RenderMeshOnScreen(Mesh*, float, float, float, float, int, int);
	void InitLight() const, RenderMesh(Mesh*, bool, GLfloat = 1.f) const;
	void RenderAnimation(Mesh*, int) const, RenderText(Mesh*, std::string, Color) const;
	void createPlatforms(), createUFOs(), createRobot1(), createVehicles(), createRobot2(), createRobot3(), createStage(), createSpeaker();
	void UpdateMainChar(double, const unsigned char*), UpdateMainTranslateXZ(double, const unsigned char*);
	void UpdateMainRotateY(double, const unsigned char*), UpdateMainTranslateY(double, const unsigned char*);
	void RenderMainChar(), RenderAnimationOnScreen(Mesh*, int, float, float, float, int, int), RenderSkybox(bool);
	void RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int), renderObject(Object* obj);
	void animateNpc(int instance), carCheck(int instance, const char* audioFileName), npcCheck(int instance, const char* audioFileName);
public:
	~GhostScene() override{}
	void Init() override, Update(double, float, const unsigned char* = 0) override, Render(double, int, int) override, Exit(Scene*) override;
};