#include "IdleCamera.h"
#include "Application.h"
#include <Mtx44.h>

IdleCamera::IdleCamera()
{

}

IdleCamera::~IdleCamera()
{

}

void IdleCamera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();;
}

void IdleCamera::Update(double dt)
{
	float yaw = (float)(-20.f * dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	position = rotation * position;
	up = rotation * up;
}

void IdleCamera::Reset()
{

}