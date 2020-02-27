#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Object.h"

class GameScene final : public Scene {
	enum class MESH {
		HITBOX, HITSPHERE, BULLET, LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, UFO_BASE, UFO_PURPLE, UFO_RED, UFO_BLUE, UFO_PINK, PLATFORM, NUM_GEOMETRY
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

		NUM_INSTANCES,
	};
	bool showDebugInfo, showLightSphere;
	char keys[7] = { '1', '2', '3', '4', '8', '9', '0' };
	double bulletBounceTime, debugBounceTime, lightBounceTime;
	double CalcFrameRate() const;
	Object object[NUM_INSTANCES];
	Light light[1]{ Light(0.f, 192.f, 0.f) };
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter bulletGenerator;
	unsigned m_vertexArrayID;
	void InitMeshes(), CreateInstances(), RenderLight(), RenderMeshOnScreen(Mesh*, float, float, float, float, int, int), RenderSkybox(bool), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float, int, int);
	void InitLight() const, RenderMesh(Mesh*, bool) const, RenderAnimation(Mesh*, std::string, Color) const, RenderText(Mesh*, std::string, Color) const, renderObject(Object* obj);

public:
	~GameScene() override {}
	void Init() override, Update(double, float) override, Render(double, int, int) override, Exit(Scene*) override;
};