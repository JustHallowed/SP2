#include "MainChar.h"

MainChar& MainChar::getMainChar(){ //Static getter for Singleton
	static MainChar mainChar;
	return mainChar;
}

MainChar::MainChar(): pos(Vector3(0.f, 0.f, 0.f)), target(Vector3(0.f, 0.f, 1.f)){
	jumping = keyReleased = 0;
	grav = jumpHeight = 0.f;
	maxJump = 2;
}

void MainChar::Init(Vector3 pos, Vector3 target){
	this->pos = pos;
	this->target = target;
}

bool MainChar::isJumping() const{
	return jumping;
}

bool MainChar::isKeyReleased() const{
	return keyReleased;
}

float MainChar::getGrav() const{
	return grav;
}

float MainChar::getJumpHeight() const{
	return jumpHeight;
}

int MainChar::getMaxJump() const{
	return maxJump;
}

Vector3 MainChar::getPos() const{
	return pos;
}

Vector3 MainChar::getTarget() const{
	return target;
}

void MainChar::reduceMaxJump(){
	--maxJump;
}

void MainChar::setPos(Vector3 newPos){
	pos = newPos;
}

void MainChar::setTarget(Vector3 newTarget){
	target = newTarget;
}

void MainChar::setGrav(float newGrav){
	grav = newGrav;
}

void MainChar::setJumpHeight(float newHeight){
	jumpHeight = newHeight;
}

void MainChar::setJumping(bool newJumpState){
	jumping = newJumpState;
}

void MainChar::setKeyReleased(bool newReleaseState){
	keyReleased = newReleaseState;
}

void MainChar::setMaxJump(int newMaxJump){
	maxJump = newMaxJump;
}