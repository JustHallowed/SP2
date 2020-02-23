#pragma once
#include "Vector3.h"

class Camera final{
	enum class MODE{
		FOCUS, FREE
	};
	friend class Application;
	friend class GhostScene;
	friend class MotorScene;
	friend class SceneManager;
	Vector3 pos, target, up, defaultPos, defaultTarget, defaultUp;
public:
	Camera();
	bool leftMouse, rightMouse;
	const float focusSpd, freeSpd;
	MODE mode;
	void Init(const Vector3, const Vector3, const Vector3), Update(double), UpdateCamVectors(float, float);
};