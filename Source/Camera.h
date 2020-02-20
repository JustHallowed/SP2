#pragma once
#include "ChangeControl.h"
#include "Vector3.h"

class Camera final{ //Singleton
	Camera();
	enum class MODE{
		FOCUS, FREE
	};
	friend class Application;
	friend class MotorScene;
	friend class SceneManager;
	Vector3 pos, target, up, defaultPos, defaultTarget, defaultUp;
	
public:
	Camera(const Camera&) = delete; //Delete copy ctor
	Camera(Camera&&) = delete; //Delete move ctor
	Camera& operator=(const Camera&) = delete; //Delete copy assignment operator
	Camera& operator=(Camera&&) = delete; //Delete move assignment operator
	bool leftMouse, rightMouse;
	const float focusSpd, freeSpd;
	MODE mode;
	static Camera& getCam();
	void Init(const Vector3&, const Vector3&, const Vector3&), Update(double), UpdateCamVectors(float, float);
	ChangeControl keys;
	ChangeControl::PURPOSE behaviour;
};