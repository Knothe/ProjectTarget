#include "Menu.h"
#include <iostream>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

Menu::Menu() {

}

Menu::~Menu() {

}

void Menu::Init() {
	std::cout << "Menu Init" << std::endl;
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::getPtr();
	LoadShaders();
	LoadModels();
	camera = Camera(glm::vec3(-2.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 50.0f, 0.5f);
}

void Menu::LoadModels() {
	/*unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};*/
	unsigned int indices[] = {
		3,2,6,
		6,7,3,
		0,1,5,
		5,4,0,
		4,7,6,
		6,5,4,
		2,3,0,
		0,1,2,
		4,7,8,
		3,8,7,
		3,0,8,
		0,8,4
	};

	GLfloat vertices[] = {
		1.0f, -2.0f, -1.5f, // 0
		-1.0f, -0.8f, -0.8f, // 1
		-1.0f, -0.8f, 0.8f, // 2
		1.0f, -2.0f, 1.5f, // 3
		1.0f, 2.0f, -1.5f, // 4
		-1.0f, 0.8f, -0.8f, // 5
		-1.0f, 0.8f, 0.8f, // 6
		1.0f, 2.0f, 1.5f, // 7
		0.0f, 0.0f, 0.0f // 8
	};
	//GLfloat vertices[] = {
	//	1.0f, -1.0f, 0.0f, // 0
	//	-1.0f, -1.0f, 0.0f, // 1
	//	-1.0f, -1.0f, 1.0f, // 2
	//	1.0f, -1.0f, 1.0f, // 3
	//	1.0f, 1.0f, 0.0f, // 4
	//	-1.0f, 1.0f, 0.0f, // 5
	//	-1.0f, 1.0f, 1.0f, // 6
	//	1.0f, 1.0f, 1.0f, // 7
	//};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 27, 36);
	meshList.push_back(obj1);
}

void Menu::LoadShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void Menu::Draw() {
	platform->RenderClear();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (float)platform->GetWidth() / platform->GetHeight(), 0.1f, 100.0f);
	shaderList[0].UseShader();
	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectLocation();
	uniformView = shaderList[0].GetViewLocation();
	glm::mat4 model(1);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
	meshList[0]->RenderMesh();
	glUseProgram(0);
	platform->RenderPresent();
}

bool Menu::MouseInput(int x, int y) {
	return false;
}

bool Menu::Input(map<int, bool>keys) {
	camera.keyControl(keys, platform->GetDeltaTime());
	return false;
}

bool Menu::Update() {
	return true;
}

void Menu::Close() {
	std::cout << "Close Init" << std::endl;
}