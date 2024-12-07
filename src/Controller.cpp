#include "Controller.h"

Controller::Controller(GLFWwindow* window, Camera* camera) : window(window), camera(camera), lastX(400.0f), lastY(300.0f), isFirstMovement(true) {
    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y) {
        Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(w));
        controller->onMouseMove(x, y);
     });

    glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mod) {
        Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(w));
        
        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            printf("Locking skybox\n");
            controller->camera->setSkyboxLocked(!controller->camera->getIsSkyboxLocked());
            return;
        }

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
        glViewport(0, 0, width, height);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mode) {
        Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));
     
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        GLbyte color[4];
        GLfloat depth;
        GLuint index; // identifikace tělesa
        //hodnota horneho pruhu
        double x,y;
        glfwGetCursorPos(window, &x, &y);

        int newy = height - static_cast<int>(y) - 10;
        
        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
        printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
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