#include "Light.h"
#include "../scenes/Scene.h"

void Light::notifyObservers() {
     for (Scene* observer : observers) {
        if (observer) {
            observer->onLightUpdated(this);  
        }
    }
}

Light::Light(const int type,const glm::vec3& position, const glm::vec3& direction)
    : type(type), position(position), direction(direction) {
    notifyObservers();
}

Light::Light(const int type, const glm::vec3& position, const glm::vec3& direction, float cutoffAngle)
    : type(type), position(position), direction(direction), cutoffAngle(cutoffAngle) {
    notifyObservers();
}

int Light::getType() {
    return this->type;
}

glm::vec3& Light::getPosition() {
    return this->position;
}

glm::vec3& Light::getDirection() {
    return this->direction;
}

float Light::getConstantAttenuation() {
    return this->constantAttenuation;
}

float Light::getLinearAttenuation() {
    return this->linearAttenuation;
}

float Light::getQuadraticAttenuation() {
    return this->quadraticAttenuation;
}

float Light::getCutoffAngle() {
    return this->cutoffAngle;
}

void Light::setPosition(const glm::vec3& position) {
    this->position = position;
    notifyObservers();
}

void Light::setDirection(const glm::vec3& direction) {
    this->direction = direction;
    notifyObservers();
}

void Light::addObserver(Scene* scene) {
    observers.push_back(scene);
    notifyObservers();
}

void Light::setTransform(std::string key, std::unique_ptr<Transformation>&& transform) {
    transforms[key] = std::move(transform);
}

Transformation* Light::getTransform(std::string key) {
    return transforms[key].get();
}