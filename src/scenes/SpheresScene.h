#pragma once

#include "Scene.h"
#include "../models/SphereModel.h"
#include "../transformations/TransformBuilder.h"

class SpheresScene : public Scene
{
public:
	SpheresScene(GLFWwindow* window, Camera* camera, Controller* controller);

    void render();
};


