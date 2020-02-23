#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ShaderManager.hpp"
#include "ParticleSystem.h"

class GhostScene final: public Scene{
	enum class MESH{
		LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, SMOKE, TEXT_ON_SCREEN, ARM, FOREARM, BODY, LOWER_LEG, UPPER_LEG, NUM_GEOMETRY
	};
	bool animateDir, showDebugInfo, showLightSphere, state;
	char keys[7] = {'1', '2', '3', '4', '8', '9', '0'};
	double bulletBounceTime, debugBounceTime, lightBounceTime, swingBounceTime, timePressed;
	double CalcFrameRate() const;
	float pAngleXZ, pAngle, mainCharAngle, leftUpperAngle, leftLowerAngle, rightUpperAngle, rightLowerAngle, leftArmAngle, leftForearmAngle, rightArmAngle, rightForearmAngle;
	Light light[1]{Light(0.f, 10.f, 0.f)};
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter bulletGenerator;
	ShaderManager* shaderMan;
	unsigned m_vertexArrayID;
	void InitMeshes(), UpdateMainChar(double), RenderMainChar(), RenderLight();
	void RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void InitLight() const, RenderMesh(Mesh*, bool, GLfloat = 1.f) const, RenderAnimation(Mesh*, std::string, Color) const, RenderText(Mesh*, std::string, Color) const;
public:
	~GhostScene() override{}
	void Init() override, Update(double, float) override, Render(double, int, int) override, Exit(Scene*) override;
};