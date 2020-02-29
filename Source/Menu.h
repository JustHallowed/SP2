#pragma once

class Menu {
public:
	enum MENUSTATES {
		MENU_1,
		MENU_2,
		PAUSE,
		CONTROLS,
		HOWTOPLAY,
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
	void howtoplay();
	void selected(int);
	void currentPage(int);

	float menuR[4], menuG[4], menuWordSize[4], menuX[5];
	double menuBounceTime;
	MENUSTATES menuState;
	bool menuActive;
	int currentSelection;
	int prev;
};