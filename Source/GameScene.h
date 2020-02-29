#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Object.h"
#include "Vehicle.h"

class GameScene final : public Scene {
	enum class MESH {
		REDHITBOX, LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, UFO_BASE, UFO_PURPLE, UFO_RED, UFO_BLUE, UFO_PINK, PLATFORM, HEALTHBAR, NUM_GEOMETRY
	};
	enum OBJECT_INSTANCES
	{
		UFO_BASE1,
		UFO_RED1,
		ENDWALL,
		BOUNDARYLEFT,
		BOUNDARYRIGHT,
		LEFT1, RIGHT1, FRONT1, BACK1, TOP1, BOTTOM1, LEFT2, RIGHT2, FRONT2, BACK2, TOP2, BOTTOM2,
		LEFT3, RIGHT3, FRONT3, BACK3, TOP3, BOTTOM3, LEFT4, RIGHT4, FRONT4, BACK4, TOP4, BOTTOM4,
		NUM_INSTANCES,
	};
	std::vector<Object*> activeObstacleQueue;
	std::vector<Object*> inactiveObstacleQueue;
	bool showDebugInfo, showLightSphere;
	char keys[7] = { '1', '2', '3', '4', '8', '9', '0' };
	double debugBounceTime, lightBounceTime, timeSinceLastObstacle;
	double CalcFrameRate() const;
	float survivalTime;
	int p1HitPoints, p2HitPoints;
	Object object[NUM_INSTANCES];
	Light light[1]{ Light(0.f, 192.f, 0.f) };
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter bulletGenerator;
	Vehicle player1, player2;
	Camera camera2;
	unsigned m_vertexArrayID;
	void InitMeshes(), CreateInstances(), RenderLight(), RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void InitLight() const, RenderMesh(Mesh*, bool) const, RenderAnimation(Mesh*, std::string, Color) const, RenderText(Mesh*, std::string, Color) const, renderObject(Object* obj);
	void updateObstacleState(double dt), resetGame(), updateGame(double dt), RenderAnimationOnScreen(Mesh*, int, float, float, float, float, int, int);
public:
	~GameScene() override {}
	void Init() override, Update(double, float, const unsigned char* = 0) override, Render(double, int, int) override, RenderScreen1(double, int, int), RenderScreen2(double, int, int), Exit(Scene*) override;
};