#include "Controller.h"

Controller::Controller(GLFWwindow* window, Camera* camera) : window(window), camera(camera), lastX(400.0f), lastY(300.0f), isFirstMovement(true) {
    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y) {
        Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(w));
        controller->onMouseMove(x, y);
     });

    glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mod) {
        Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(w));
        
        int sceneId = key - 49;

        if (sceneId > 4 || sceneId < 0) {
            return;
        }

        fprintf(stderr, "SceneId %d\n", sceneId);
        controller->setSceneId(sceneId);
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int width, int height) {
        Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(w));
        
        controller->camera->recalculateProjectMatrix(width, height);
    });

    glfwSetWindowUserPointer(window, this);
}

void Controller::processInput() {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveForward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveBackward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveRight();
}

void Controller::onMouseMove(float x, float y) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (this->isFirstMovement) {  
        lastX = x;
        lastY = y;
        isFirstMovement = false;
    }

    float xoffset = x - lastX;
    float yoffset = y - lastY; 
    lastX = x;
    lastY = y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera->rotateLeft(xoffset);
    camera->rotateUp(yoffset);
}

int Controller::getSceneId() {
    return this->sceneId;
}

void Controller::setSceneId(int sceneId) {
    this->sceneId = sceneId;
}