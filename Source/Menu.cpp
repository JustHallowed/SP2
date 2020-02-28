#include <iostream>
#include "Menu.h"
#include "Application.h"
extern double elapsedTime;
double interactBounceTime;

Menu::Menu()
{
	CurrentSelection = 2;
	interactBounceTime = 0.0;
}
Menu::~Menu()
{
}

void Menu::Init()
{
	for (int i = 0; i < 7; ++i)
	{
		menuR[i] = 0.2f;
		menuG[i] = 0.8f;
		menuWordSize[i] = 6.f;
	}
	menuX[0] = 1.f;
	menuX[1] = -11.f;
	menuActive = true;
	menuBounceTime = 0.0;
}

void Menu::Update(double dt)
{
	if (menuActive)
	{
		MenuInput();
		switch (menuState)
		{
		case (MENU_1):
			menu1();
			break;
		case(MENU_2):
			menu2();
			break;
		case(PAUSE):
			pause();
			break;
		case(CONTROLS):
			controls();
			break;
		default:
			break;
		}
	}
}

void Menu::menu1()
{
	if (menuX[1] != -11)
		--menuX[1];
	if (menuX[0] != 1)
		++menuX[0];
	POINT p;
	if (GetCursorPos(&p))
	{
		system("cls");
		std::cout << p.x << std::endl << p.y << std::endl;
		HWND hwnd = ::GetActiveWindow();
		if (ScreenToClient(hwnd, &p))
		{
			std::cout << p.x << std::endl << p.y << std::endl;
			//PLAY
			if (p.x > 65 && p.x < 265 && p.y > 730 && p.y < 766 || (CurrentSelection == 2))
			{
				if (menuR[0] <= 1.f)
				{
					menuR[0] += 0.4f;
					menuG[0] += 0.1f;
					menuWordSize[0] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					menuActive = false;
					menuState = CLOSED;
					menuBounceTime = elapsedTime + 0.4;
				}
			}
			else
			{
				if (menuR[0] >= 0.2f)
				{
					menuR[0] -= 0.4f;
					menuG[0] -= 0.1f;
					menuWordSize[0] -= 0.1f;
				}
			}
			//OPTIONS
			if (p.x > 67 && p.x < 447 && p.y > 789 && p.y < 826 || (CurrentSelection == 1))
			{
				if (menuR[1] <= 1.f)
				{
					menuR[1] += 0.4f;
					menuG[1] += 0.1f;
					menuWordSize[1] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					menuState = MENU_2;
					menuBounceTime = elapsedTime + 0.4;
					
				}
			}
			else
			{
				if (menuR[1] >= 0.2f)
				{
					menuR[1] -= 0.4f;
					menuG[1] -= 0.1f;
					menuWordSize[1] -= 0.1f;
				}
			}
			//QUIT
			if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884 || (CurrentSelection == 0))
			{
				if (menuR[2] <= 1.f)
				{
					menuR[2] += 0.4f;
					menuG[2] += 0.1f;
					menuWordSize[2] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					exit(0);
				}
			}
			else
			{
				if (menuR[2] >= 0.2f)
				{
					menuR[2] -= 0.4f;
					menuG[2] -= 0.1f;
					menuWordSize[2] -= 0.1f;
				}
			}
		}
	}
}

void Menu::menu2()
{
	if (menuX[0] != -11)
		--menuX[0];
	if (menuX[1] != 1)
		++menuX[1];
	POINT p;
	if (GetCursorPos(&p))
	{
		system("cls");
		std::cout << p.x << std::endl << p.y << std::endl;
		HWND hwnd = ::GetActiveWindow();
		if (ScreenToClient(hwnd, &p))
		{
			std::cout << p.x << std::endl << p.y << std::endl;
			//CONTROLS
			if (p.x > 65 && p.x < 500 && p.y > 730 && p.y < 766 || (CurrentSelection == 2))
			{
				if (menuR[0] <= 1.f)
				{
					menuR[0] += 0.4f;
					menuG[0] += 0.1f;
					menuWordSize[0] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					//code for controls
					menuBounceTime = elapsedTime + 0.4;
				}
			}
			else
			{
				if (menuR[0] >= 0.2f)
				{
					menuR[0] -= 0.4f;
					menuG[0] -= 0.1f;
					menuWordSize[0] -= 0.1f;
				}
			}
			//FULLSCREEN
			if (p.x > 67 && p.x < 622 && p.y > 789 && p.y < 826 || (CurrentSelection == 1))
			{
				if (menuR[1] <= 1.f)
				{
					menuR[1] += 0.4f;
					menuG[1] += 0.1f;
					menuWordSize[1] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					//fullscreen toggle
					menuBounceTime = elapsedTime + 0.4;
				}
			}
			else
			{
				if (menuR[1] >= 0.2f)
				{
					menuR[1] -= 0.4f;
					menuG[1] -= 0.1f;
					menuWordSize[1] -= 0.1f;
				}
			}
			//BACK
			if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884 || (CurrentSelection == 0))
			{
				if (menuR[2] <= 1.f)
				{
					menuR[2] += 0.4f;
					menuG[2] += 0.1f;
					menuWordSize[2] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					menuState = MENU_1;
					menuBounceTime = elapsedTime + 0.4;
				}
			}
			else
			{
				if (menuR[2] >= 0.2f)
				{
					menuR[2] -= 0.4f;
					menuG[2] -= 0.1f;
					menuWordSize[2] -= 0.1f;
				}
			}
		}
	}
}

void Menu::pause()
{
	POINT p;
	if (GetCursorPos(&p))
	{
		system("cls");
		std::cout << p.x << std::endl << p.y << std::endl;
		HWND hwnd = ::GetActiveWindow();
		if (ScreenToClient(hwnd, &p))
		{
			std::cout << p.x << std::endl << p.y << std::endl;
			//RESUME
			if (p.x > 65 && p.x < 392 && p.y > 670 && p.y < 708 || (CurrentSelection == 2))
			{
				if (menuR[3] <= 1.f)
				{
					menuR[3] += 0.4f;
					menuG[3] += 0.1f;
					menuWordSize[3] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					menuActive = false;
					menuState = CLOSED;
				}
			}
			else
			{
				if (menuR[3] >= 0.2f)
				{
					menuR[3] -= 0.4f;
					menuG[3] -= 0.1f;
					menuWordSize[3] -= 0.1f;
				}

			}
			//CONTROLS
			if (p.x > 65 && p.x < 500 && p.y > 730 && p.y < 766 || (CurrentSelection == 1))
			{
				if (menuR[4] <= 1.f)
				{
					menuR[4] += 0.4f;
					menuG[4] += 0.1f;
					menuWordSize[4] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					//code for controls
					menuBounceTime = elapsedTime + 0.4;
				}
			}
			else
			{
				if (menuR[4] >= 0.2f)
				{
					menuR[4] -= 0.4f;
					menuG[4] -= 0.1f;
					menuWordSize[4] -= 0.1f;
				}
			}
			//MAIN MENU
			if (p.x > 67 && p.x < 622 && p.y > 789 && p.y < 826 || (CurrentSelection == 0))
			{
				if (menuR[5] <= 1.f)
				{
					menuR[5] += 0.4f;
					menuG[5] += 0.1f;
					menuWordSize[5] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					menuState = MENU_1;
					menuBounceTime = elapsedTime + 0.4;
				}
			}
			else
			{
				if (menuR[5] >= 0.2f)
				{
					menuR[5] -= 0.4f;
					menuG[5] -= 0.1f;
					menuWordSize[5] -= 0.1f;
				}
			}
			//QUIT
			if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884 || (CurrentSelection == -1))
			{
				if (menuR[6] <= 1.f)
				{
					menuR[6] += 0.4f;
					menuG[6] += 0.1f;
					menuWordSize[6] += 0.1f;
				}
				if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime)
				{
					exit(0);
				}
			}
			else
			{
				if (menuR[6] >= 0.2f)
				{
					menuR[6] -= 0.4f;
					menuG[6] -= 0.1f;
					menuWordSize[6] -= 0.1f;
				}
			}
		}
	}
}

void Menu::MenuInput()
{
	bool cSomethingHappened = false;
	if (interactBounceTime > elapsedTime)
		return;

	if ((Application::IsKeyPressed(VK_UP) && CurrentSelection < 2))
	{
		CurrentSelection += 1;
		cSomethingHappened = true;
	}
	else if ((Application::IsKeyPressed(VK_DOWN) && CurrentSelection > -1))
	{
		CurrentSelection -= 1;
		cSomethingHappened = true;
	}

	if ((GetKeyState(VK_RETURN) & 0x100) && menuActive && menuBounceTime <= elapsedTime)
	{
		menuState = menuState; //to check value of MenuState.
		switch (CurrentSelection)
		{
		case -1:
			exit(0);
			break;
		case 0:
			//Quit game
			if (menuState == PAUSE || menuState == MENU_2)
			{
				menuState = MENU_1;
			}
			else 
			{
				exit(0);
			}
			break;
		case 1:
			//Enter options
			menuState = MENU_2;
			break;
		case 2:
			//Start game
			menuActive = false;
			menuState = CLOSED;
			break;
		}
	}

	if (cSomethingHappened)
	{
		interactBounceTime = elapsedTime + 0.140;
	}
}


void Menu::controls()
{
}
