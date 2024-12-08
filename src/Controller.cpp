#include "Controller.h"
#include "./scenes/ForestScene.h"

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
        if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS) {
            return;
        }

        Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));

        int frameWidth, frameHeight;
        glfwGetFramebufferSize(window, &frameWidth, &frameHeight);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        float scaleX = static_cast<float>(frameWidth) / static_cast<float>(windowWidth);
        float scaleY = static_cast<float>(frameHeight) / static_cast<float>(windowHeight);

        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        float scaledX = x * scaleX;
        float scaledY = y * scaleY;

        int newy = frameHeight - static_cast<int>(scaledY) - 1;

        glReadPixels(static_cast<int>(scaledX), newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(static_cast<int>(scaledX), newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(static_cast<int>(scaledX), newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        // printf("Clicked on pixel %.2f, %.2f, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

        glm::vec4 viewport = glm::vec4(0, 0, frameWidth, frameHeight);
        glm::vec3 windowCoords = glm::vec3(scaledX, newy, depth);

        glm::vec3 p = glm::unProject(windowCoords, controller->camera->getViewMatrix(), controller->camera->getProjectMatrix(), viewport);

        controller->getScene()->growTree(p.x, p.y, p.z);

        printf("Local coords: %.2f, %.2f, d:%f - ", x, newy, depth);
        printf("Global coords: %.2f, %.2f, %.2f\n", p.x, p.y, p.z);
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

Scene* Controller::getScene() {
    return this->scene;
}

void Controller::setScene(Scene* scene) {
    this->scene = scene;
}