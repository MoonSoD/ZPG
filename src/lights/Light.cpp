#include "Light.h"
#include "../scenes/Scene.h"

void Light::notifyObservers() {
     for (Scene* observer : observers) {
        if (observer) {
            observer->onLightUpdated(this);  
        }
    }
}

Light::Light(const int type,const glm::vec3& position, const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color, const glm::vec3& cameraPosition)
    : type(type), position(position), direction(direction), ambient(ambient), diffuse(diffuse), specular(specular), color(color), cameraPosition(cameraPosition) {
    notifyObservers();
}

Light::Light(const int type, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color, const glm::vec3& cameraPosition, float innerConeAngle, float outerConeAngle)
    : type(type), position(position), direction(direction), ambient(ambient), diffuse(diffuse), specular(specular), color(color), cameraPosition(cameraPosition), innerConeAngle(innerConeAngle), outerConeAngle(outerConeAngle) {
    notifyObservers();
}

int Light::getType() {
    return this->type;
}

glm::vec3& Light::getAmbient() {
    return this->ambient;
}

glm::vec3& Light::getDiffuse() {
    return this->diffuse;
}

glm::vec3& Light::getSpecular() {
    return this->specular;
}

glm::vec3& Light::getPosition() {
    return this->position;
}

glm::vec3& Light::getDirection() {
    return this->direction;
}

glm::vec3& Light::getColor() {
    return this->color;
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

float Light::getInnerConeAngle() {
    return this->innerConeAngle;
}

float Light::getOuterConeAngle() {
    return this->outerConeAngle;
}

void Light::setAmbient(const glm::vec3& ambient) {
    this->ambient = ambient;
    notifyObservers();
}

void Light::setDiffuse(const glm::vec3& diffuse) {
    this->diffuse = diffuse;
    notifyObservers();
}

void Light::setSpecular(const glm::vec3& specular) {
    this->specular = specular;
    notifyObservers();
}

void Light::setPosition(const glm::vec3& position) {
    this->position = position;
    notifyObservers();
}

void Light::setDirection(const glm::vec3& direction) {
    this->direction = direction;
    notifyObservers();
}

void Light::setColor(const glm::vec3& color) {
    this->color = color;
    notifyObservers();
}

void Light::addObserver(Scene* scene) {
    observers.push_back(scene);
    notifyObservers();
}
