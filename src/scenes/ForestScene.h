#pragma once

#include "Scene.h"

class ForestScene : public Scene
{
private:
	float rotation = 0;
public:
	ForestScene(GLFWwindow* window, Camera* camera, Controller* controller);

	void render();
};

