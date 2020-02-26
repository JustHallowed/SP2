#include "Application.h"
#include <crtdbg.h>
#include <time.h>

int main(){
	srand(unsigned int(time(0)));
	Application::getApp()->Run();
	delete Application::getApp();
	_CrtDumpMemoryLeaks(); //To check for memory leaks
}