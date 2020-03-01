#include "Menu.h"
#include "Application.h"

extern bool hideCursor;
extern double elapsedTime;

Menu::Menu()
{

}
Menu::~Menu()
{
}

void Menu::Init()
{
	for (int i = 0; i < 4; ++i)
	{
		menuR[i] = 0.2f;
		menuG[i] = 0.8f;
		menuWordSize[i] = 6.f;
	}
	menuX[0] = 1.f;
	for (int i = 1; i < 5; ++i)
		menuX[i] = -11.f;
	menuActive = true;
	menuBounceTime = 0.0;
	currentSelection = 1;
	prev = 1;
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
		case(HOWTOPLAY):
			howtoplay();
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
	currentPage(0);

	if (Application::IsKeyPressed(VK_DOWN) && menuBounceTime <= elapsedTime && currentSelection < 3)
	{
		++currentSelection;
		menuBounceTime = elapsedTime + 0.1;
	}
	else if (Application::IsKeyPressed(VK_UP) && menuBounceTime <= elapsedTime && currentSelection > 1)
	{
		--currentSelection;
		menuBounceTime = elapsedTime + 0.1;
	}

	POINT p;
	if (GetCursorPos(&p))
	{
		HWND hwnd = ::GetActiveWindow();
		if (ScreenToClient(hwnd, &p))
		{
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
		selected(0);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			menuActive = false;
			hideCursor = 1;
		}
	}
	else if (currentSelection == 2)
	{
		selected(1);
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
		selected(2);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			exit(0);
		}
	}
}

void Menu::menu2()
{
	currentPage(1);

	if (Application::IsKeyPressed(VK_DOWN) && menuBounceTime <= elapsedTime && currentSelection < 3)
	{
		++currentSelection;
		menuBounceTime = elapsedTime + 0.1;
	}
	else if (Application::IsKeyPressed(VK_UP) && menuBounceTime <= elapsedTime && currentSelection > 1)
	{
		--currentSelection;
		menuBounceTime = elapsedTime + 0.1;

	}
	POINT p;
	if (GetCursorPos(&p))
	{
		HWND hwnd = ::GetActiveWindow();
		if (ScreenToClient(hwnd, &p))
		{
			//CONTROLS
			if (p.x > 65 && p.x < 500 && p.y > 730 && p.y < 766)
			{
				currentSelection = 1;
			}
			//HOW TO PLAY
			else if (p.x > 67 && p.x < 672 && p.y > 789 && p.y < 826)
			{
				currentSelection = 2;
			}
			//BACK
			else if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884)
			{
				currentSelection = 3;
			}
		}
	}
	if (currentSelection == 1)
	{
		selected(0);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//CONTROLS
			menuState = CONTROLS;
			currentSelection = 1;
			prev = 1;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 2)
	{
		selected(1);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//HOW TO PLAY
			menuState = HOWTOPLAY;
			currentSelection = 1;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 3)
	{
		selected(2);
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
	currentPage(2);

	if (Application::IsKeyPressed(VK_DOWN) && menuBounceTime <= elapsedTime && currentSelection < 4)
	{
		++currentSelection;
		menuBounceTime = elapsedTime + 0.1;
	}
	else if (Application::IsKeyPressed(VK_UP) && menuBounceTime <= elapsedTime && currentSelection > 1)
	{
		--currentSelection;
		menuBounceTime = elapsedTime + 0.1;


	}
	POINT p;
	if (GetCursorPos(&p))
	{
		HWND hwnd = ::GetActiveWindow();
		if (ScreenToClient(hwnd, &p))
		{
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
		selected(0);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//resume
			menuActive = false;
		}
	}
	else if (currentSelection == 2)
	{
		selected(1);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			//CONTROLS
			menuState = CONTROLS;
			currentSelection = 1;
			prev = 2;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
	else if (currentSelection == 3)
	{
		selected(2);
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
		selected(3);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			exit(0);
		}
	}
}

void Menu::controls()
{
	currentPage(3);
	POINT p;
	if (GetCursorPos(&p))
	{
		HWND hwnd = ::GetActiveWindow();
		if (ScreenToClient(hwnd, &p))
		{
			if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884)
			{
				currentSelection = 1;
			}
		}
	}
	//BACK
	if (currentSelection == 1)
	{
		selected(0);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			if (prev == MENU_2)
				menuState = MENU_2;
			else if (prev == PAUSE)
				menuState = PAUSE;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
}

void Menu::howtoplay()
{
	currentPage(4);
	POINT p;
	if (GetCursorPos(&p))
	{
		HWND hwnd = ::GetActiveWindow();
		if (ScreenToClient(hwnd, &p))
		{
			if (p.x > 67 && p.x < 268 && p.y > 854 && p.y < 884)
			{
				currentSelection = 1;
			}
		}
	}
	if (currentSelection == 1)
	{
		//BACK
		selected(0);
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && menuActive && menuBounceTime <= elapsedTime
			|| Application::IsKeyPressed(VK_RETURN) && menuActive && menuBounceTime <= elapsedTime)
		{
			menuState = MENU_2;
			menuBounceTime = elapsedTime + 0.4;
		}
	}
}

void Menu::selected(int x)
{
	for (int i = 0; i < 4; ++i)
	{
		if (i != x)
		{
			if (menuR[i] >= 0.2f)
			{
				menuR[i] -= 0.4f;
				menuG[i] -= 0.1f;
				menuWordSize[i] -= 0.1f;
			}
		}
	}
	if (menuR[x] <= 1.f)
	{
		menuR[x] += 0.4f;
		menuG[x] += 0.1f;
		menuWordSize[x] += 0.1f;
	}
}

void Menu::currentPage(int x)
{
	for (int i = 0; i < 5; ++i)
	{
		if (i != x)
		{
			if (menuX[i] != -11)
				--menuX[i];
		}
	}
	if (menuX[x] != 1)
		++menuX[x];
}

