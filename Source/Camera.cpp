#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
#include "SceneManager.h"

double modeBounceTime = 0.0;
extern double elapsedTime = 0.0;
extern float FOV;

Camera::Camera() : focusSpd(100.f), freeSpd(50.f) { //Default ctor
	mode = MODE::FOCUS;
	leftMouse = rightMouse = 0;
	canMove = true;
}

void Camera::Init(const Vector3 pos, const Vector3 target, const Vector3 up) { //Init cam
	this->pos = defaultPos = pos;
	this->target = defaultTarget = target;
	this->up = defaultUp = up;
}

void Camera::Update(double dt, const float* axes, const unsigned char* buttons){ //Update cam
	displacement.SetZero();
	if(canMove){
		if((Application::IsKeyPressed('B') || (buttons != 0 && bool(buttons[1]))) && modeBounceTime <= elapsedTime){ //Change cam mode
			mode = MODE(!bool(mode));
			Vector3 dir = target - pos, front = dir.Normalized(), right = front.Cross(up).Normalized();
			right.y = 0;
			if(mode == MODE::FOCUS){
				target = Vector3(0.f, 0.f, 0.f);
				front = target - pos;
				front.y = 0;
				right = front.Cross(up);
				right.y = 0;
				up = right.Cross(front).Normalized();
			}
			modeBounceTime = elapsedTime + 0.2;
		}

		float leftRight = -(axes != 0 && axes[0] == int(axes[0]) ? axes[0] : 0);
		if(!leftRight){
			leftRight = float(Application::IsKeyPressed('A') - Application::IsKeyPressed('D'));
		}
		if(leftRight){ //Move cam left or right
			Vector3 dir = target - pos, front = dir.Normalized();
			if(mode == MODE::FOCUS){
				float yaw = float(leftRight * -focusSpd * dt);
				Mtx44 rotation;
				rotation.SetToRotation(yaw, 0, 1, 0);
				front = rotation * (target - pos);
				pos = target - front;
				up = rotation * up;
			} else if(mode == MODE::FREE){
				Vector3 right = front.Cross(up).Normalized();
				right.y = 0;
				pos += leftRight * float(-freeSpd * dt) * right;
				target += leftRight * float(-freeSpd * dt) * right;
			}
		}

		float upDown = -(axes != 0 && axes[3] == int(axes[3]) ? axes[3] : 0);
		if(!upDown){
			upDown = float(Application::IsKeyPressed('Q') - Application::IsKeyPressed('E'));
		}
		if(upDown){ //Move cam up or down
			Vector3 dir = target - pos, front = dir.Normalized();
			if(mode == MODE::FOCUS){
				Vector3 right = front.Cross(up).Normalized();
				right.y = 0;
				float pitch = -upDown * focusSpd * float(dt);
				Mtx44 rotation;
				rotation.SetToRotation(pitch, right.x, right.y, right.z);
				front = rotation * (target - pos);
				pos = target - front;
				up = rotation * up;
			} else if(mode == MODE::FREE){
				pos += upDown * float(freeSpd * dt) * up;
				target += upDown * float(freeSpd * dt) * up;
			}
		}

		float forward = Application::IsKeyPressed('W') || (axes != 0 && axes[1] == -1), backward = Application::IsKeyPressed('S') || (axes != 0 && axes[1] == 1);
		if(forward || (leftMouse && !rightMouse)){ //Move cam forward or towards the target
			Vector3 dir = target - pos, front = dir.Normalized();
			if(mode == MODE::FOCUS){
				pos += front * float(focusSpd / 2 * dt) * (dir.Length() > 12);
			} else{
				if(forward){
					front.y = 0;
				}
				pos += float(freeSpd * dt) * front;
				target += float(freeSpd * dt) * front;
			}
		}
		if(backward || (rightMouse && !leftMouse)){ //Move cam backward or away from the target
			Vector3 dir = target - pos, front = dir.Normalized();
			if(mode == MODE::FOCUS){
				pos += front * float(-focusSpd / 2 * dt) * (dir.Length() < 200);
			} else{
				if(backward){
					front.y = 0;
				}
				pos += float(-freeSpd * dt) * front;
				target += float(-freeSpd * dt) * front;
			}
		}
		target += displacement;
		pos += displacement;
	}
}

void Camera::UpdateCamVectors(float yaw, float pitch) { //For cam to respond to mouse movement
	if(SceneManager::getScMan()->currSceneID != 1){
		Vector3 front = (target - pos).Normalized(), right = front.Cross(up).Normalized();
		right.y = 0;
		Mtx44 r1, r2;
		r1.SetToRotation(-yaw, 0, 1, 0);
		r2.SetToRotation(-pitch, right.x, right.y, right.z);
		if(mode == MODE::FOCUS){
			front = r1 * r2 * (target - pos);
			pos = target - front;
			up = r1 * r2 * up;
		} else if(mode == MODE::FREE){
			front = r1 * r2 * front;
			target = pos + front;
		}
		up = right.Cross(front).Normalized();
	}
}