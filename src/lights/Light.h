#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include "transformations/Transformation.h"


class Scene;

class Light {
private:
    // glm::vec3 cameraPosition;
    // glm::vec3 lightPosition;
    // glm::vec3 objectColor;

    //pos, attenuation, direction, color

    int type = 0; // 0 = point, 1 = directional

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 cameraPosition;
 
    glm::vec3 color;

    float constantAttenuation = 1.0;
    float linearAttenuation = 0.05;
    float quadraticAttenuation = 0.05;

    float cutoffAngle = 0.0;
    
    std::vector<Scene*> observers;

    void notifyObservers();

    std::unordered_map<std::string, std::unique_ptr<Transformation>> transforms;

public:
    Light(const int type, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color, const glm::vec3& cameraPosition);
    Light(const int type, const glm::vec3& position, const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& color, const glm::vec3& cameraPosition, float cutoffAngle);
    int getType();

    glm::vec3& getAmbient();
    glm::vec3& getDiffuse();
    glm::vec3& getSpecular();
    
    glm::vec3& getPosition();
    glm::vec3& getDirection();

    glm::vec3& getColor();

    float getConstantAttenuation();
    float getLinearAttenuation();
    float getQuadraticAttenuation();

    float getCutoffAngle();

    void setAmbient(const glm::vec3& ambient);
    void setDiffuse(const glm::vec3& diffuse);
    void setSpecular(const glm::vec3& specular);

    void setPosition(const glm::vec3& position);
    void setDirection(const glm::vec3& direction);

    void setColor(const glm::vec3& color);

    void addObserver(Scene* scene);

    void setTransform(std::string key, std::unique_ptr<Transformation>&& transform);

	Transformation* getTransform(std::string key);

};
