#pragma once

#include "Scene.h"

class ItemsScene : Scene
{
public:
	ItemsScene(GLFWwindow* window, std::unordered_map<std::string, ShaderProgram*> shaders, Camera* camera, Controller* controller);

	void render();
};

