#include <GL/glew.h>
#include "Application.h"
#include "SceneManager.h"
#include "GhostScene.h"
#include "MotorScene.h"

bool firstMouse = 1;
const unsigned char FPS = 90;
extern const unsigned int frameTime = 1000 / FPS; //Time for each frame
extern bool hideCursor = 1;
extern Camera camera;
extern double elapsedTime;
extern float FOV = 45.f;
GLFWwindow* m_window;
GLfloat xLast = 0, yLast = 0;
char* Scene::typed = new char[10];
double typeBounceTime = 0.0;

Application* Application::app = 0;

Application* Application::getApp(){
	if(!app){
		app = new Application;
	}
	return app;
}

bool Application::IsKeyPressed(unsigned short key){
	return (GetAsyncKeyState(key) & 0x8001) != 0;
}

void Application::Run(){
	return getApp()->IRun();
}

static void error_callback(int error, const char* description){ //Define an error callback
	fputs(description, stderr);
	_fgetchar();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){ //Define the key input callback
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if(typeBounceTime <= elapsedTime){
		if(key == GLFW_KEY_BACKSPACE){
			for(short i = 9; i >= 0; --i){
				if(Scene::getTyped()[i] != (char)0){
					Scene::getTyped()[i] = (char)0;
					break;
				}
			}
			typeBounceTime = elapsedTime + 0.1;
		} else{
			for(short i = 0; i < 10; ++i){
				if(Scene::getTyped()[i] == char(0) && char(key) > 64 && char(key) < 90){
					Scene::getTyped()[i] = char(key);
					break;
				}

			}
			typeBounceTime = elapsedTime + 0.2;
		}
	}
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos){ //For mouse movement
	if(firstMouse){
		xLast = GLfloat(xpos);
		yLast = GLfloat(ypos);
		firstMouse = 0;
	}
	float SENS = 0.03f, xOffset = (GLfloat(xpos) - xLast) * SENS, yOffset = (GLfloat(ypos) - yLast) * SENS;
	xLast = GLfloat(xpos);
	yLast = GLfloat(ypos);
	if(hideCursor){
		camera.UpdateCamVectors(xOffset, yOffset);
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){ //For mouse buttons
	if(action == GLFW_PRESS){
		(button == GLFW_MOUSE_BUTTON_LEFT ? camera.leftMouse : camera.rightMouse) = 1;
	} else{
		camera.leftMouse = camera.rightMouse = 0;
	}
}

static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset){ //For mouse scroll wheel
	if((yOffset > 0 && FOV > 15.0f) || (yOffset < 0 && FOV < 80.0f)){
		FOV -= float(yOffset);
	}
}

void resize_callback(GLFWwindow* window, int winWidth, int winHeight){
	glViewport(0, 0, winWidth, winHeight); //Update OpenGL with the new window size
}

Application::Application(){
	system("color 0A"); //Change MF console text color
	glfwSetErrorCallback(error_callback); //Set the error callback
	if(!glfwInit()){ //Init GLFW
		exit(EXIT_FAILURE);
	}

	//Set GLFW window creation hints (optional)
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x anti-aliasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Makes MacOS happy, should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	fullscreen = 0;
	mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	SetWindowPos(GetConsoleWindow(), 0, 0, 0, int(mode->width / 4), int(mode->height * 7 / 8), 0);
	m_window = glfwCreateWindow(int(mode->width * 2 / 3), int(mode->width * 2 / 3) * 3 / 4, "Framework", 0, 0); //Create a window and create its OpenGL context
	glfwSetWindowSizeCallback(m_window, resize_callback);
	glfwSetWindowPos(m_window, int(mode->width / 4), int(mode->height / 30));

	if(!m_window){ //If the window can't be created...
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window); //Makes the context of the specified window current on the calling thread
	glfwSetKeyCallback(m_window, key_callback); //Sets the key callback
	glewExperimental = 1; //For core profile
	GLenum err = glewInit(); //Init GLEW
	if(err != GLEW_OK){ //If GLEW is not initialised...
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Hide window cursor
	glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	if(glfwRawMouseMotionSupported()){
		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE); //Enable raw (unscaled and unaccelerated) mouse motion
	}
	glfwSetCursorPosCallback(m_window, mouse_callback);
	glfwSetMouseButtonCallback(m_window, mouse_button_callback);
	glfwSetScrollCallback(m_window, scroll_callback);

	SceneManager::getScMan()->AddScene(new MotorScene);
	SceneManager::getScMan()->AddScene(new GhostScene);
}

Application::~Application(){
	glfwDestroyWindow(m_window); //Close OpenGL window and terminate GLFW
	glfwTerminate(); //Finalise and clean up GLFW
	delete[] Scene::getTyped();
	delete SceneManager::getScMan();
}

void Application::IRun(){
	int count;
	m_timer.startTimer(); //Start timer to calculate how long it takes to render this frame
	while(!glfwWindowShouldClose(m_window)){ //Main Loop
		system("cls");
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
		for(int i = 0; i < count; ++i){
			std::cout << axes[i] << std::endl;
		}
		SceneManager::getScMan()->Update(*this, m_window, axes); //Update current scene
	}
}