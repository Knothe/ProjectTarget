#pragma once
#include <string>
#include "GameState.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <map>
class GameState;
using std::string;
using std::map;
class Platform
{
private:
	int width;
	int height;
	string name;

	GLFWwindow* mainWindow;
	GLint bufferWidth, bufferHeight;
	float deltaTime{ 0 };
	float lastTime{ 0 };
private:
	void init();
	Platform(string name, int window, int hWindow);
	~Platform();
	static Platform* ptr;
public:
	static Platform* GetPtr();
	void RenderClear();
	void RenderPresent();
	void CheckEvent(GameState* obj, bool (GameState::* keyboard)(std::map<int, bool>), bool (GameState::* mouse)(int, int));
	int GetWidth();
	int GetHeight();
	float GetDeltaTime();
public:
	static GameState* obj;
	static bool (GameState::* keyboard)(map<int, bool>);
	static bool(GameState::* mouse)(int, int);
	static map<int, bool>keys;
private:
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};

