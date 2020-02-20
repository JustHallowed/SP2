#pragma once

class ChangeControl
{
	char newKey;
public:
	ChangeControl();
	ChangeControl(char);
	ChangeControl(const ChangeControl&) = delete;
	void setnewKey(unsigned char);
	enum class PURPOSE { FORWARD, BACKWARD, UP, DOWN, LEFT, RIGHT };
	bool onKeyChange;
	bool paused;
	char currentKey_front;
	char currentKey_back;
	char currentKey_left;
	char currentKey_right;
	char currentKey_up;
	char currentKey_dwn;
	PURPOSE purpose;
};

