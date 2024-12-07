#include "../lib/soil/include/SOIL/SOIL.h"
#include "Texture.h"
#include <iostream>

Texture::Texture(const std::string& fileName) {
    id = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (id == 0) {
        std::cout << "An error occurred while loading texture " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    printf("Texture %s loaded\n", fileName.c_str());
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}