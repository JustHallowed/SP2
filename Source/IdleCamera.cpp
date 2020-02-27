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
}

void IdleCamera::Reset()
{

}