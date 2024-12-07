#pragma once

#include <glm/glm.hpp>
#include "../textures/Texture.h"

class Material {
private:
    glm::vec3 ambient = glm::vec3(1.0f);
    glm::vec3 diffuse = glm::vec3(1.0f);
    glm::vec3 specular = glm::vec3(1.0f);

    Texture* texture = nullptr;

public:
    Material(Texture* texture);

    Material(Texture* texture, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    glm::vec3 getAmbient();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();

    void bindTexture();
};
