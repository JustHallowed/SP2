#pragma once

class Menu {

	enum MENUSTATES {
		MENU_1,
		MENU_2,
		PAUSE,
		CONTROLS,
		NUM_STATES
	};

public:

	Menu();
	~Menu();
	void Init();
	void Update(double);
	void menu1();
	void menu2();
	void pause();
	void controls();

	float menuR[7], menuG[7], menuWordSize[7], menuX[2];
	MENUSTATES menuState;
	bool menuActive;
};