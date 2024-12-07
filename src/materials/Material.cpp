#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) 
 : ambient(ambient), diffuse(diffuse), specular(specular) {
 }

glm::vec3 Material::getAmbient() {
    return this->ambient;
}

glm::vec3 Material::getDiffuse() {
    return this->diffuse;
}

glm::vec3 Material::getSpecular() {
    return this->specular;
}