#include "Platform.h"
#include <iostream>

Platform* Platform::ptr;
GameState* Platform::obj;
bool (GameState::* Platform::keyboard)(map<int, bool>);
bool (GameState::* Platform::mouse)(int, int);
map<int, bool> Platform::keys;

Platform::Platform(string name, int wWindow, int hWindow) {
	width = wWindow;
	height = hWindow;
	this->name = name;
	init();
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

void Platform::init() {
	if (!glfwInit()) {
		std::cout << "Error Initialising GLFW";
		glfwTerminate();
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (!mainWindow) {
		printf("Error creating GLFW window!");
		glfwTerminate();
		return;
	}
	//Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//See the current context
	glfwMakeContextCurrent(mainWindow);

	//Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return;
	}
	glEnable(GL_DEPTH_TEST);

	//Create Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
}
Platform::~Platform() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

void Platform::RenderClear() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Platform::RenderPresent() {
	glfwSwapBuffers(mainWindow);
}

float Platform::GetDeltaTime()
{
	return deltaTime;
}

void Platform::CheckEvent(GameState* obj, bool (GameState::* keyboard)(map<int, bool>), bool (GameState::* mouse)(int, int)) {
	GLfloat now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;
	glfwPollEvents();
	this->obj = obj;
	this->keyboard = keyboard;
	this->mouse = mouse;
	glfwSetKeyCallback(mainWindow, HandleKeys);
	glfwSetCursorPosCallback(mainWindow, HandleMouse);
}

int Platform::GetWidth() {
	return width;
}

int Platform::GetHeight() {
	return height;
}

Platform* Platform::GetPtr() {
	if (ptr == nullptr)
		ptr = new Platform("GAME", 640, 480);
	else
		return ptr;
}

void Platform::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			Platform::keys[key] = true;
		else if (action == GLFW_RELEASE)
			Platform::keys[key] = false;
	}
	(Platform::obj->*Platform::keyboard)(keys);
}

void Platform::HandleMouse(GLFWwindow* window, double xPos, double yPos) {
	(Platform::obj->*Platform::mouse)(xPos, yPos);
}