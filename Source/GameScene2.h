#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Object.h"
#include "Vehicle.h"

class GameScene2 final : public Scene {
	enum class MESH {
		REDHITBOX, WHITEHITBOX, BULLET, LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, UFO_BASE, UFO_PURPLE, UFO_RED, UFO_BLUE, UFO_PINK, PLATFORM, NUM_GEOMETRY
	};
	enum OBJECT_INSTANCES
	{
		UFO_BASE1,
		UFO_RED1,
		GROUND,
		DEATHZONE,
		NUM_INSTANCES,
	};
	std::vector<Object*> activeObstacleQueue;
	std::vector<Object*> inactiveObstacleQueue;
	bool showDebugInfo, showLightSphere;
	char keys[7] = { '1', '2', '3', '4', '8', '9', '0' };
	double bulletBounceTime, debugBounceTime, lightBounceTime, timeSinceLastObstacle, spaceBounceTime,enterBounceTime;
	double CalcFrameRate() const;
	float survivalTime;
	int p1BombCharge,p2BombCharge;
	Object object[NUM_INSTANCES];
	Light light[1]{ Light(0.f, 192.f, 0.f) };
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter bulletGenerator;
	Vehicle player1,player2;
	unsigned m_vertexArrayID;
	void InitMeshes(), CreateInstances(), RenderLight(), RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void InitLight() const, RenderMesh(Mesh*, bool) const, RenderAnimation(Mesh*, std::string, Color) const, RenderText(Mesh*, std::string, Color) const, renderObject(Object* obj);
	void updateObstacleState(double dt), resetGame(), updateGame(double dt);
public:
	~GameScene2() override {}
	void Init() override, Update(double, float, const unsigned char* = 0) override, Render(double, int, int) override, Exit(Scene*) override;
};