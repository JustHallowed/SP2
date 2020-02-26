#pragma once
#include "Vector3.h"

class MainChar final{ //Singleton
	MainChar();
	bool jumping, keyReleased;
	float grav, jumpHeight;
	int maxJump;
	Vector3 pos, target;
public:
	bool isJumping() const, isKeyReleased() const;
	float getGrav() const, getJumpHeight() const;
	int getMaxJump() const;
	MainChar(const MainChar&) = delete; //Delete copy ctor
	MainChar(MainChar&&) = delete; //Delete move ctor
	MainChar& operator=(const MainChar&) = delete; //Delete copy assignment operator
	MainChar& operator=(MainChar&&) = delete; //Delete move assignment operator
	static MainChar& getMainChar();
	Vector3 getPos() const, getTarget() const;
	void Init(Vector3, Vector3), reduceMaxJump(), setPos(Vector3), setTarget(Vector3), setGrav(float), setJumpHeight(float), setJumping(bool), setKeyReleased(bool), setMaxJump(int);
};