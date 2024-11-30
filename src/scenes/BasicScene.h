#pragma once

#include "Scene.h"

class BasicScene : public Scene
{
public:
	BasicScene(GLFWwindow* window, Camera* camera, Controller* controller);

	void render();
};

