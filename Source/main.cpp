

#include "Application.h"
#include <iostream>

int main( void )
{
	Application app;
	app.Init();
	app.Run();
	_CrtDumpMemoryLeaks();
	app.Exit();
}