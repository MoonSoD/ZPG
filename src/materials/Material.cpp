#include "Material.h"

Material::Material(Texture* texture) : texture(texture) {}

// Material::Material(Texture* texture, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) 
//  : ambient(ambient), diffuse(diffuse), specular(specular), texture(texture) {
// }

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) 
 : ambient(ambient), diffuse(diffuse), specular(specular) {
 }

Material::Material(glm::vec3 color) : color(color) {}

Material::Material(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
 : color(color), ambient(ambient), diffuse(diffuse), specular(specular) {
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

glm::vec3 Material::getColor() {
    return this->color;
}

void Material::bindTexture() {
    if (texture != nullptr) {
       texture->bind();
    }
}