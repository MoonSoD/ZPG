#pragma once

#include "Scene.h"

class ForestScene : public Scene
{
private:
	float rotation = 0;
public:
	ForestScene(GLFWwindow* window, Camera* camera, Controller* controller);

	void growTree(float translateX, float translateY, float translateZ) override;

	void render() override;
};

