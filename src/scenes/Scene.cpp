#include "Scene.h"
#include "../lights/Light.h"

Scene::Scene(GLFWwindow* window, Camera* camera, Controller* controller) : window(window), camera(camera), controller(controller), lights({}) {}

GLFWwindow* Scene::getWindow() {
    return this->window;
}

Camera* Scene::getCamera() {
    return this->camera;
}

void Scene::setLight(Light* light) {
    lights.push_back(light);
    light->addObserver(this); 
}

void Scene::onLightUpdated(Light* updatedLight) {
    for (auto& pair : objects) {
        for (int i = 0; i < lights.size(); i++) {
            pair.second->updateLight(lights[i], i);
        }
    }
}

void Scene::recalculateCamera() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
    this->camera->recalculateProjectMatrix(width, height);
}

void Scene::setSkybox(DrawableObject* skybox) {
    this->skybox = skybox;
}

void Scene::renderSkybox() {
    if (skybox != nullptr) {
        skybox->draw(true);
    }
}