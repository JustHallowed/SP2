#include "ChangeControl.h"

ChangeControl::ChangeControl()
{
	currentKey_front = 'W';
	currentKey_back = 'S';
	currentKey_left = 'A';
	currentKey_right = 'D';
	onKeyChange;
	
}

ChangeControl::ChangeControl(char obj_key)
{
	newKey = obj_key;
}

void ChangeControl::setnewKey(unsigned char keyboard_Keys)
{
	if (onKeyChange == true)
	{
		switch (purpose) 
		{
		case PURPOSE::LEFT:
			newKey = keyboard_Keys;
			currentKey_left = newKey;
			onKeyChange = false;
			break;
		case PURPOSE::RIGHT:
			newKey = keyboard_Keys;
			currentKey_right = newKey;
			onKeyChange = false;
			break;
		case PURPOSE::FORWARD:
			newKey = keyboard_Keys;
			currentKey_front = newKey;
			onKeyChange = false;
			break;
		case PURPOSE::BACKWARD:
			newKey = keyboard_Keys;
			currentKey_back = newKey;
			onKeyChange = false;
			break;
		}
	}
	else
	{
		return;
	}

}
