#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>
#include "../DrawableObject.h"
#include "../Camera.h"
#include "../Controller.h"


class Controller;

class Light;

class Scene
{
protected:
	GLFWwindow* window;
	std::unordered_map<std::string, DrawableObject*> objects;
	Camera* camera;
	Controller* controller;
	std::vector<Light*> lights;
	int frames = 0;
	int updatesFrequency = 60;
	DrawableObject* skybox;
	ShaderProgram* shader;

public:
	Scene(GLFWwindow* window, Camera* camera, Controller* controller);

	GLFWwindow* getWindow();

	Camera* getCamera();

	void setLight(Light* light);
	virtual void onLightUpdated(Light* updatedLight);

	void recalculateCamera();

	virtual void render() = 0;

	void setSkybox(DrawableObject* skybox);

	void renderSkybox();

	virtual void growTree(float translateX, float translateY, float translateZ);

	ShaderProgram* getShader();
	void setShader(ShaderProgram* shader);
};

