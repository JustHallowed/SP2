#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ShaderManager.hpp"
#include "ParticleSystem.h"
#include "ScoreSystem.h"

class MotorScene final: public Scene{
	enum class MESH{
		BULLET, LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, ARM, FOREARM, BODY, LOWER_LEG, UPPER_LEG, NUM_GEOMETRY
	};
	bool animateDir, showDebugInfo, showLightSphere, state;
	char keys[7] = {'1', '2', '3', '4', '8', '9', '0'};
	double bulletBounceTime, debugBounceTime, lightBounceTime, swingBounceTime, timePressed;
	double CalcFrameRate() const;
	float particleAngle, mainCharAngle, leftUpperAngle, leftLowerAngle, rightUpperAngle, rightLowerAngle, leftArmAngle, leftForearmAngle, rightArmAngle, rightForearmAngle;
	Light light[1]{Light(0.f, 10.f, 0.f)};
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter bulletGenerator;
	ShaderManager* shaderMan;
	ScoreManager* scoreMan;
	unsigned m_vertexArrayID;
	void InitMeshes(), UpdateMainChar(double), RenderMainChar(), RenderLight();
	void RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void GetNameScoreData(bool) const, InitLight() const;
	void RenderParticle(Mesh*, GLfloat) const, RenderMesh(Mesh*, bool) const, RenderAnimation(Mesh*, std::string, Color) const, RenderText(Mesh*, std::string, Color) const;
public:
	~MotorScene() override{}
	void Init() override, Update(double, float) override, Render(double, int, int) override, Exit(Scene*) override;
};