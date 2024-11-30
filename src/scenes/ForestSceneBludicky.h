#pragma once

#include "Scene.h"

class ForestSceneBludicky : public Scene
{
private:
	float rotation = 0;
public:
	ForestSceneBludicky(GLFWwindow* window, Camera* camera, Controller* controller);

	void render();
};

