#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Object.h"
#include "Vehicle.h"

class GhostScene final: public Scene{
	enum class MESH{
		HITBOX, HITSPHERE, LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, SMOKE, ARM, FOREARM, BODY, LOWER_LEG, UPPER_LEG,
		UFO_BASE, UFO_PURPLE, UFO_RED, UFO_BLUE, UFO_PINK, PLATFORM, ROBOT_BODY, ROBOT_ARM, ROBOT_FOREARM, ROBOT_UPPERLEG, ROBOT_LOWERLEG, NUM_GEOMETRY,
	};
	enum OBJECT_INSTANCES{
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

		NUM_INSTANCES,
	};
	bool animateDir, showDebugInfo, showLightSphere, state;
	bool inRange[NUM_INSTANCES], interacted[NUM_INSTANCES];
	char keys[7] = {'1', '2', '3', '4', '8', '9', '0'};
	double smokeBounceTime, debugBounceTime, interactBounceTime, lightBounceTime, swingBounceTime, timePressed, timeInScene;
	double CalcFrameRate() const;
	float pAngleXZ, pAngle, mainCharAngle, leftUpperAngle, leftLowerAngle, rightUpperAngle, rightLowerAngle, leftArmAngle, leftForearmAngle, rightArmAngle, rightForearmAngle;
	int indexUpDown, indexLeftRight, indexJump;
	Object object[NUM_INSTANCES];
	Light light[1]{Light(0.f, 10.f, 0.f)};
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter smokeGenerator;
	unsigned m_vertexArrayID;
	void InitMeshes(), CreateInstances(), RenderLight(), RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void InitLight() const, RenderMesh(Mesh*, bool, GLfloat = 1.f) const, RenderAnimation(Mesh*, std::string, Color) const, RenderText(Mesh*, std::string, Color) const;
	void createPlatforms(), createUFOs(), createRobot1(), UpdateMainChar(double), UpdateMainTranslateXZ(double), UpdateMainRotateY(double), UpdateMainTranslateY(double), RenderMainChar(), renderObject(Object* obj);
public:
	~GhostScene() override{}
	void Init() override, Update(double, float, const unsigned char* = 0) override, Render(double, int, int) override, Exit(Scene*) override;
};