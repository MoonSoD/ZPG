#pragma once
#include "Model.h"
#include "./definitions/skycube.h"
#include "../lib/soil/include/SOIL/SOIL.h"

GLuint loadCubemap(const std::string& basePath) {
    std::string faces[] = {
        "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg"
    };

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < 6; i++) {
        std::string fullPath = basePath + faces[i];
        GLuint faceTexture = SOIL_load_OGL_texture(fullPath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

        if (faceTexture == 0) {
            std::cerr << "Error loading cubemap face: " << faces[i] << ", SOIL error: " << SOIL_last_result() << std::endl;
            exit(EXIT_FAILURE);
        }

        int width, height;
        unsigned char* image = SOIL_load_image(fullPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

class Skybox : public Model
{
public:
	Skybox() : Model() {
		glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), skycube, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);

		auto skybox = loadCubemap("/Users/stefanmelicher/Documents/School/ZPG/zpg_project/src/textures/cubemap/");

		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
	}

	void draw() override {
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};

