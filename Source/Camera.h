#pragma once
#include "Vector3.h"
#include "Object.h"

class Camera final{
	enum class MODE{
		FOCUS, FREE
	};
	friend class Application;
	friend class MotorScene;
	friend class GhostScene;
	friend class GameScene;
	friend class GameScene2;
	friend class ParticleEmitter;
	friend class SceneManager;
	Vector3 pos, target, up, defaultPos, defaultTarget, defaultUp, displacement;
public:
	Camera();
	bool leftMouse, rightMouse;
	const float focusSpd, freeSpd;
	MODE mode;
	void Init(const Vector3, const Vector3, const Vector3), Update(double, const float*, const unsigned char*), UpdateCamVectors(float, float);
};