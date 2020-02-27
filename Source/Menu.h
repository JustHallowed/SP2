#pragma once

class Menu {

	enum MENUSTATES {
		MENU1,
		MENU2,
		PAUSE,
		CONTROLS,
		NUM_STATES
	};
	Menu();
	~Menu();
	void menu1();
	void menu2();
	void pause();
	void controls();
	void Update(double);

	float menuR[7], menuG[7], menuWordSize[7], menuX[2];
	MENUSTATES menuState;
};