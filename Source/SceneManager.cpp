#include "SceneManager.h"

extern bool hideCursor;
Camera camera;
extern const unsigned int frameTime;
extern double elapsedTime;
extern float FOV;

SceneManager::SceneManager(): currSceneID(0), nextSceneID(0), screenBounceTime(0.0), switchBounceTime(0.0){}

SceneManager::~SceneManager(){
	sceneStorage[currSceneID]->Exit(sceneStorage[currSceneID]);
	for(size_t i = 0; i < sceneStorage.size(); ++i){
		delete sceneStorage[i];
	}
}

SceneManager* SceneManager::sceneMan = 0;

SceneManager* SceneManager::getScMan(){
	if(!sceneMan){
		sceneMan = new SceneManager;
	}
	return sceneMan;
}

void SceneManager::AddScene(Scene* newScene){
	sceneStorage.emplace_back(newScene);
	if(sceneStorage.size() == 1){
		sceneStorage[currSceneID]->Init();
	} else{
		SceneManager::getScMan()->SetNextSceneID(sceneStorage.size() - 1);
	}
}

void SceneManager::SetNextScene(){
	if(sceneStorage.size() > 1){
		sceneStorage[currSceneID]->Exit(sceneStorage[nextSceneID]);
	}
	currSceneID = nextSceneID;
	if(++nextSceneID == sceneStorage.size()){
		nextSceneID = 0;
	}
}

void SceneManager::SetNextSceneID(int newID){
	nextSceneID = newID;
}

void SceneManager::Update(Application& app, GLFWwindow* m_window, const float* axes, const unsigned char* buttons){ //Update current scene
	double dt = app.m_timer.getElapsedTime();
	elapsedTime += dt;
	if(hideCursor){
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Hide window cursor
	} else{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //Show window cursor
	}
	if(Application::IsKeyPressed('C') && switchBounceTime <= elapsedTime){
		hideCursor = !hideCursor;
		switchBounceTime = elapsedTime + 0.5;
	}
	if((Application::IsKeyPressed(VK_F11) || (buttons != 0 && bool(buttons[6]))) && screenBounceTime <= elapsedTime){ //Toggle fullscreen
		if(app.fullscreen){
			glfwSetWindowMonitor(m_window, 0, int(app.mode->width * 7 / 24), int(app.mode->height / 30), int(app.mode->width * 2 / 3), int(app.mode->width * 2 / 3) * 3 / 4, GLFW_DONT_CARE);
		} else{
			glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, int(app.mode->width), int(app.mode->height), GLFW_DONT_CARE);
		}
		app.fullscreen = !app.fullscreen;
		screenBounceTime = elapsedTime + 0.5;
	}
	camera.Update(dt, axes, buttons);
	sceneStorage[currSceneID]->Update(dt, FOV, buttons);
	sceneStorage[currSceneID]->Render(dt, int(app.mode->width * 2 / 3), int(app.mode->width * 2 / 3) * 3 / 4);
	glfwSwapBuffers(m_window);
	glfwPollEvents(); //Get and organize events like kb and mouse input, window resizing, etc.
	app.m_timer.waitUntil(frameTime); //Limits each frame to a specified time in ms
}