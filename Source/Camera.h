#pragma once
#include "Vector3.h"
#include "Object.h"

class Camera final{ //Singleton
	enum class MODE{
		FOCUS, FREE
	};
	enum DIRECTION{
		POSX,POSZ,NEGX,NEGZ,NUM_AXIS,
	};
	bool canMove[NUM_AXIS];
	friend class Application;
	friend class MotorScene;
	friend class GhostScene;
	friend class GameScene;
	friend class GameScene2;
	friend class SceneManager;
	Vector3 pos, target, up, defaultPos, defaultTarget, defaultUp, displacement;
public:
	Camera();
	bool leftMouse, rightMouse;
	const float focusSpd, freeSpd;
	MODE mode;
	void Init(const Vector3, const Vector3, const Vector3), Update(double, const float*), UpdateCamVectors(float, float);
};