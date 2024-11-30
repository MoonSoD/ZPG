#include "Scene.h"

#pragma once
class MultipleShaderScene : public Scene
{
public:
	MultipleShaderScene(GLFWwindow* window, Camera* camera, Controller* controller);

	void render();
};

