#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

class Controller {
private:
    GLFWwindow* window;
    Camera* camera;
    float lastX, lastY;
    bool isFirstMovement;
    int sceneId = 1;
public:
    Controller(GLFWwindow* window, Camera* camera);
    void processInput();
    void onMouseMove(float x, float y);

    int getSceneId();
    void setSceneId(int sceneId);
};
