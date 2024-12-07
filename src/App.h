#pragma once
#include "scenes/ItemsScene.h"
#include "scenes/ForestScene.h"
#include <cstdio>
#include <cstdlib>
#include "CallbackListener.h"
#include <vector>
#include <unordered_map>
#include "scenes/SpheresScene.h"
#include "scenes/MultipleShaderScene.h"
#include "scenes/BasicScene.h"
#include "scenes/ForestSceneBludicky.h"

static void error_callback(int error, const char* description) { fputs(description, stderr); }

class App
{
private:
	GLFWwindow* window;
	CallbackListener* callbackListener;

	Camera* camera;
	Controller* controller;

	std::vector<Scene*> scenes;

public:
	App() {}

	void init() {
		glfwSetErrorCallback(error_callback);

		if (!glfwInit()) {
			fprintf(stderr, "ERROR: could not start GLFW3\n");
			exit(EXIT_FAILURE);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		glfwSetWindowUserPointer(window, this);

		callbackListener = new CallbackListener(window);
		callbackListener->listen();
		
		glfwSetKeyCallback(window, key_callback);


		glewExperimental = GL_TRUE;
		glewInit();

		printVersionInfo();

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float ratio = width / (float)height;
		glViewport(0, 0, width, height);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	}

	void printVersionInfo() {
		printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
		printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
		printf("Vendor %s\n", glGetString(GL_VENDOR));
		printf("Renderer %s\n", glGetString(GL_RENDERER));
		printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		int major, minor, revision;
		glfwGetVersion(&major, &minor, &revision);
		printf("Using GLFW %i.%i.%i\n", major, minor, revision);
	}

	void createScenes() {
		printf("Creating scenes\n");
		camera = new Camera();
		controller = new Controller(window, camera);

		auto spheresScene = new SpheresScene(window, camera, controller);
		auto forestScene = new ForestScene(window, camera, controller);
		auto multipleShaderScene = new MultipleShaderScene(window, camera, controller);
		auto basicScene = new BasicScene(window, camera, controller);
		auto forestSceneBludicky = new ForestSceneBludicky(window, camera, controller);

		scenes.push_back(spheresScene);
		scenes.push_back(forestScene);
		scenes.push_back(multipleShaderScene);
		scenes.push_back(basicScene);
		scenes.push_back(forestSceneBludicky);
		printf("Scenes created\n");
	}

	void run() {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glStencilOp ( GL_KEEP , GL_KEEP , GL_REPLACE );
		while (!glfwWindowShouldClose(window)) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			auto sceneId = controller->getSceneId();

			scenes[sceneId]->renderSkybox();
			if (!controller->getIsSkyboxLocked()) {
				glClear(GL_DEPTH_BUFFER_BIT);
			} 

			scenes[sceneId]->render();

			glfwPollEvents(); //don't call after clearing the buffer!!
			glfwSwapBuffers(window);
		}

		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}

};
