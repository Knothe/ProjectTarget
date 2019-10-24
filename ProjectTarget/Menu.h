#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>
using std::vector;
class Menu : public GameState
{
private:
	Platform* platform;
	GameStateManager* manager;

	vector<Mesh*>meshList;
	vector<Shader> shaderList;
	const char* vShader = "shader.vert";
	const char* fShader = "shader.frag";
	Camera camera;

public:
	Menu();
	~Menu();
	void Init() override;
	void Draw() override;
	bool Input(map<int, bool> keys) override;
	bool MouseInput(int x, int y);
	bool Update() override;
	void Close() override;
	void LoadShaders();
	void LoadModels();
};

