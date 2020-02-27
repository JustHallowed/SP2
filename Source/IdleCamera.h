#pragma once

#ifndef IDLE_CAMERA_H
#define IDLE_CAMERA_H

#include "Vector3.h"

class IdleCamera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	IdleCamera();
	~IdleCamera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
};

#endif