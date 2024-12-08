#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "./scenes/Scene.h"

class Controller {
private:
    GLFWwindow* window;
    Camera* camera;
    float lastX, lastY;
    bool isFirstMovement;
    int sceneId = 1;
    Scene* scene = nullptr;
public:
    Controller(GLFWwindow* window, Camera* camera);
    void processInput();
    void onMouseMove(float x, float y);

    int getSceneId();
    void setSceneId(int sceneId);

    Scene* getScene();
    void setScene(Scene* scene);

    bool getIsSkyboxLocked() { return this->camera->getIsSkyboxLocked(); }
};
