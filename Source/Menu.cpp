#include "Menu.h"
#include "Application.h"

extern double elapsedTime;

Menu::Menu()
{

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
	currentSelection = 1;
}

void Menu::Update(double dt)
{
	if (menuActive)
	{
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
	if (!menuActive)
	{
		if (Application::IsKeyPressed('P'))
		{
			menuState = PAUSE;
			menuActive = true;
			currentSelection = 1;
		}

	}
}

void Menu::menu1()
{
	if (menuX[1] != -11)
		--menuX[1];
	if (menuX[0] != 1)
		++menuX[0];

	if (Application::IsKeyPressed(VK_DOWN) && menuBounceTime <= elapsedTime && currentSelection < 3)
	{
		++currentSelection;
		menuBounceTime = elapsedTime + 0.2;
	}
	else if (Application::IsKeyPressed(VK_UP) && menuBounceTime <= elapsedTime && currentSelection > 1)
	{
		--currentSelection;
		menuBounceTime = elapsedTime + 0.2;
	}
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
			if (p.x > 65 && p.x < 265 && p.y > 730 && p.y < 766)
			{
				currentSelection = 1;
			}
			//OPTIONS
			else if (p.x > 67 && p.x < 447 && p.y > 789 && p.y < 826)
			{
				currentSelection = 2;
			}
			//QUIT
			else if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884)
			{
				currentSelection = 3;
			}
		}
	}

	if (currentSelection == 1)
	{
		if (menuR[0] <= 1.f)
		{
			menuR[0] += 0.4f;
			menuG[0] += 0.1f;
			menuWordSize[0] += 0.1f;
		}
		if (menuR[1] >= 0.2f)
		{
			menuR[1] -= 0.4f;
			menuG[1] -= 0.1f;
			menuWordSize[1] -= 0.1f;
		}
		if (menuR[2] >= 0.2f)
		{
			menuR[2] -= 0.4f;
			menuG[2] -= 0.1f;
			menuWordSize[2] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			menuActive = false;
			menuState = CLOSED;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 2)
	{
		if (menuR[1] <= 1.f)
		{
			menuR[1] += 0.4f;
			menuG[1] += 0.1f;
			menuWordSize[1] += 0.1f;
		}
		if (menuR[0] >= 0.2f)
		{
			menuR[0] -= 0.4f;
			menuG[0] -= 0.1f;
			menuWordSize[0] -= 0.1f;
		}
		if (menuR[2] >= 0.2f)
		{
			menuR[2] -= 0.4f;
			menuG[2] -= 0.1f;
			menuWordSize[2] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			menuState = MENU_2;
			currentSelection = 1;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 3)
	{
		if (menuR[2] <= 1.f)
		{
			menuR[2] += 0.4f;
			menuG[2] += 0.1f;
			menuWordSize[2] += 0.1f;
		}
		if (menuR[0] >= 0.2f)
		{
			menuR[0] -= 0.4f;
			menuG[0] -= 0.1f;
			menuWordSize[0] -= 0.1f;
		}
		if (menuR[1] >= 0.2f)
		{
			menuR[1] -= 0.4f;
			menuG[1] -= 0.1f;
			menuWordSize[1] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			exit(0);
		}
	}
}

void Menu::menu2()
{
	if (menuX[0] != -11)
		--menuX[0];
	if (menuX[1] != 1)
		++menuX[1];

	if (Application::IsKeyPressed(VK_DOWN) && menuBounceTime <= elapsedTime && currentSelection < 3)
	{
		++currentSelection;
		menuBounceTime = elapsedTime + 0.2;
	}
	else if (Application::IsKeyPressed(VK_UP) && menuBounceTime <= elapsedTime && currentSelection > 1)
	{
		--currentSelection;
		menuBounceTime = elapsedTime + 0.2;

	}
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
			if (p.x > 65 && p.x < 500 && p.y > 730 && p.y < 766)
			{
				currentSelection = 1;
			}
			//FULLSCREEN
			else if (p.x > 67 && p.x < 622 && p.y > 789 && p.y < 826)
			{
				currentSelection = 2;
			}
			//QUIT
			else if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884)
			{
				currentSelection = 3;
			}
		}
	}
	if (currentSelection == 1)
	{
		if (menuR[0] <= 1.f)
		{
			menuR[0] += 0.4f;
			menuG[0] += 0.1f;
			menuWordSize[0] += 0.1f;
		}
		if (menuR[1] >= 0.2f)
		{
			menuR[1] -= 0.4f;
			menuG[1] -= 0.1f;
			menuWordSize[1] -= 0.1f;
		}
		if (menuR[2] >= 0.2f)
		{
			menuR[2] -= 0.4f;
			menuG[2] -= 0.1f;
			menuWordSize[2] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//controls
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 2)
	{
		if (menuR[1] <= 1.f)
		{
			menuR[1] += 0.4f;
			menuG[1] += 0.1f;
			menuWordSize[1] += 0.1f;
		}
		if (menuR[0] >= 0.2f)
		{
			menuR[0] -= 0.4f;
			menuG[0] -= 0.1f;
			menuWordSize[0] -= 0.1f;
		}
		if (menuR[2] >= 0.2f)
		{
			menuR[2] -= 0.4f;
			menuG[2] -= 0.1f;
			menuWordSize[2] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//FULLLSCREEN
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 3)
	{
		if (menuR[2] <= 1.f)
		{
			menuR[2] += 0.4f;
			menuG[2] += 0.1f;
			menuWordSize[2] += 0.1f;
		}
		if (menuR[0] >= 0.2f)
		{
			menuR[0] -= 0.4f;
			menuG[0] -= 0.1f;
			menuWordSize[0] -= 0.1f;
		}
		if (menuR[1] >= 0.2f)
		{
			menuR[1] -= 0.4f;
			menuG[1] -= 0.1f;
			menuWordSize[1] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			menuState = MENU_1;
			currentSelection = 1;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
}

void Menu::pause()
{
	if (Application::IsKeyPressed(VK_DOWN) && menuBounceTime <= elapsedTime && currentSelection < 4)
	{
		++currentSelection;
		menuBounceTime = elapsedTime + 0.2;
	}
	else if (Application::IsKeyPressed(VK_UP) && menuBounceTime <= elapsedTime && currentSelection > 1)
	{
		--currentSelection;
		menuBounceTime = elapsedTime + 0.2;


	}
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
			if (p.x > 65 && p.x < 392 && p.y > 670 && p.y < 708)
			{
				currentSelection = 1;
			}
			//CONTROLS
			else if (p.x > 65 && p.x < 500 && p.y > 730 && p.y < 766)
			{
				currentSelection = 2;
			}
			//MAIN MENU
			else if (p.x > 67 && p.x < 622 && p.y > 789 && p.y < 826)
			{
				currentSelection = 3;
			}
			//QUIT
			if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884)
			{
				currentSelection = 4;
			}
		}
	}

	if (currentSelection == 1)
	{
		if (menuR[3] <= 1.f)
		{
			menuR[3] += 0.4f;
			menuG[3] += 0.1f;
			menuWordSize[3] += 0.1f;
		}
		if (menuR[4] >= 0.2f)
		{
			menuR[4] -= 0.4f;
			menuG[4] -= 0.1f;
			menuWordSize[4] -= 0.1f;
		}
		if (menuR[5] >= 0.2f)
		{
			menuR[5] -= 0.4f;
			menuG[5] -= 0.1f;
			menuWordSize[5] -= 0.1f;
		}
		if (menuR[6] >= 0.2f)
		{
			menuR[6] -= 0.4f;
			menuG[6] -= 0.1f;
			menuWordSize[6] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//resume
			menuState = CLOSED;
			menuActive = true;
		}
	}
	else if (currentSelection == 2)
	{
		if (menuR[4] <= 1.f)
		{
			menuR[4] += 0.4f;
			menuG[4] += 0.1f;
			menuWordSize[4] += 0.1f;
		}
		if (menuR[3] >= 0.2f)
		{
			menuR[3] -= 0.4f;
			menuG[3] -= 0.1f;
			menuWordSize[3] -= 0.1f;
		}
		if (menuR[5] >= 0.2f)
		{
			menuR[5] -= 0.4f;
			menuG[5] -= 0.1f;
			menuWordSize[5] -= 0.1f;
		}
		if (menuR[6] >= 0.2f)
		{
			menuR[6] -= 0.4f;
			menuG[6] -= 0.1f;
			menuWordSize[6] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//CONTROLS
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 3)
	{
		if (menuR[5] <= 1.f)
		{
			menuR[5] += 0.4f;
			menuG[5] += 0.1f;
			menuWordSize[5] += 0.1f;
		}
		if (menuR[3] >= 0.2f)
		{
			menuR[3] -= 0.4f;
			menuG[3] -= 0.1f;
			menuWordSize[3] -= 0.1f;
		}
		if (menuR[4] >= 0.2f)
		{
			menuR[4] -= 0.4f;
			menuG[4] -= 0.1f;
			menuWordSize[4] -= 0.1f;
		}
		if (menuR[6] >= 0.2f)
		{
			menuR[6] -= 0.4f;
			menuG[6] -= 0.1f;
			menuWordSize[6] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//MAIN MENU
			menuState = MENU_1;
			currentSelection = 1;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 4)
	{
		if (menuR[6] <= 1.f)
		{
			menuR[6] += 0.4f;
			menuG[6] += 0.1f;
			menuWordSize[6] += 0.1f;
		}
		if (menuR[3] >= 0.2f)
		{
			menuR[3] -= 0.4f;
			menuG[3] -= 0.1f;
			menuWordSize[3] -= 0.1f;
		}
		if (menuR[4] >= 0.2f)
		{
			menuR[4] -= 0.4f;
			menuG[4] -= 0.1f;
			menuWordSize[4] -= 0.1f;
		}
		if (menuR[5] >= 0.2f)
		{
			menuR[5] -= 0.4f;
			menuG[5] -= 0.1f;
			menuWordSize[5] -= 0.1f;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			exit(0);
		}
	}
}

void Menu::controls()
{
}

