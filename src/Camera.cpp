#define GLM_ENABLE_EXPERIMENTAL

#include "Camera.h"
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


void Camera::notifyObservers() {
	for (auto shaderProgram : observers) {
		shaderProgram->updateCamera();
	}
}

Camera::Camera() {
	this->observers = {};

	this->eye = glm::vec3(0.0, 0.0, 0.0);
	this->target = glm::vec3(0, 0, 0);
	this->up = glm::vec3(0, 1, 0);

	this->alpha = 90.0f;
	this->fi = 0.0f;

	this->updateTarget();
    this->recalculateProjectMatrix(800, 600);
	this->recalculateViewMatrix();

    notifyObservers();
}

void Camera::updateTarget() {
    target.x = sin(alpha) * cos(fi);
    target.z = sin(alpha) * sin(fi);
    target.y = cos(alpha);

	this->target = glm::normalize(target);
}

void Camera::recalculateViewMatrix() {
    //std::cout << "Eye: " << glm::to_string(this->eye) << std::endl;
    //std::cout << "Target: " << glm::to_string(this->target) << std::endl;
    //std::cout << "Up: " << glm::to_string(this->up) << std::endl;
    //std::cout << "Target + Up: " << glm::to_string(this->target + this->eye) << std::endl;

	this->viewMatrix = glm::lookAt(this->eye, this->target + this->eye, this->up);
	notifyObservers();

    // glm::vec3(0.850904f, 0.525322f, 0)
}

void Camera::recalculateProjectMatrix(float width, float height) {
	this->projectMatrix = glm::perspective(90.f, width / height, 0.01f, 100.f);
	notifyObservers();
}

glm::vec3 Camera::getEye() {
	return this->eye;
}

glm::mat4& Camera::getViewMatrix() {
	return this->viewMatrix;
}

glm::mat4& Camera::getProjectMatrix() {
	return this->projectMatrix;
}

glm::mat4 Camera::getCamera() {
	return glm::lookAt(this->eye, this->eye + this->target, this->up);
}

glm::vec3& Camera::getTarget() {
	return this->target;
}

void Camera::moveForward() {
    this->eye += 0.1f * glm::normalize(this->target);
    this->recalculateViewMatrix();
}

void Camera::moveBackward() {
    this->eye -= 0.1f * glm::normalize(this->target);
    this->recalculateViewMatrix();
}

void Camera::moveLeft() {
    this->eye -= 0.1f * glm::normalize(glm::cross(this->target, this->up));
    this->recalculateViewMatrix();
}

void Camera::moveRight() {
    this->eye += 0.1f * glm::normalize(glm::cross(this->target, this->up));
    this->recalculateViewMatrix();
}

void Camera::rotateLeft(float angle) {
    this->fi += glm::radians(angle);
    updateTarget();
    this->recalculateViewMatrix();
}

void Camera::rotateRight(float angle) {
    this->fi -= glm::radians(angle);
    updateTarget();
    this->recalculateViewMatrix();
}

void Camera::rotateUp(float angle) {
    this->alpha += glm::radians(angle);
    if (this->alpha >= glm::radians(90.0f)) {
        this->alpha = glm::radians(90.0f);
    }
    updateTarget();
    this->recalculateViewMatrix();
}

void Camera::rotateDown(float angle) {
    this->alpha -= glm::radians(angle);
    if (this->alpha <= glm::radians(-90.0f)) {
        this->alpha = glm::radians(-90.0f);
    }
    updateTarget();
    this->recalculateViewMatrix();
}

void Camera::addObserver(ShaderProgram* shader) {
    observers.push_back(shader);
}

void Camera::removeObserver(ShaderProgram* shader) {
    observers.erase(std::remove(observers.begin(), observers.end(), shader), observers.end());
}