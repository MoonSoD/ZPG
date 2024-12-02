#pragma once
#include <GLFW/glfw3.h>
#include <stdio.h>


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	//glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}


class CallbackListener {
private:
	GLFWwindow* window;
public:
	CallbackListener(GLFWwindow* window) : window(window) {}

	void listen() {
		glfwSetKeyCallback(window, key_callback);

		glfwSetCursorPosCallback(window, cursor_callback);

		glfwSetMouseButtonCallback(window, button_callback);

		glfwSetWindowFocusCallback(window, window_focus_callback);

		glfwSetWindowIconifyCallback(window, window_iconify_callback);

		glfwSetWindowSizeCallback(window, window_size_callback);
	}
};

