#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ShaderManager.hpp"
#include "ParticleSystem.h"
#include "Object.h"
#include "vehicle.h"
#include <vector>

class GameScene final : public Scene {
	enum class MESH {
		HITBOX,LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, UFO_BASE, NUM_GEOMETRY
	};
	enum OBJECT_INSTANCES
	{
		UFO_BASE1,
		ENDWALL,

		NUM_INSTANCES,
	};
	bool showDebugInfo, showLightSphere;
	char keys[7] = { '1', '2', '3', '4', '8', '9', '0' };
	double bulletBounceTime, debugBounceTime, lightBounceTime, timeSinceLastObstacle;
	double CalcFrameRate() const;
	Object object[NUM_INSTANCES];
	std::vector<Object*> activeObstacleQueue;
	std::vector<Object*> inactiveObstacleQueue;
	Light light[1]{ Light(0.f, 192.f, 0.f) };
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter bulletGenerator;
	ShaderManager* shMan;
	Vehicle player;
	unsigned m_vertexArrayID;
	void InitMeshes(), CreateInstances(), RenderLight(), RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void InitLight() const, RenderParticle(Mesh*, GLfloat) const, RenderMesh(Mesh*, bool) const, RenderAnimation(Mesh*, std::string, Color) const, RenderText(Mesh*, std::string, Color) const, renderObject(Object* obj);
	void updateObstacleState(double dt);
public:
	~GameScene() override {}
	void Init() override, Update(double, float) override, Render(double, int, int) override, Exit(Scene*) override;
};