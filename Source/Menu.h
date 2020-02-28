#pragma once

class Menu {
public:
	enum MENUSTATES {
		MENU_1,
		MENU_2,
		PAUSE,
		CONTROLS,
		CLOSED,
		NUM_STATES
	};

	Menu();
	~Menu();
	void Init();
	void Update(double);
	void menu1();
	void menu2();
	void pause();
	void controls();

	float menuR[7], menuG[7], menuWordSize[7], menuX[2];
	double menuBounceTime;
	MENUSTATES menuState;
	bool menuActive;
	int currentSelection;
};