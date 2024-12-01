#pragma once
#include "../ShaderProgram.h"
#include <cstddef>
#include <iostream>
#include "../lib/soil/include/SOIL/SOIL.h"

#include "ModelLoader.h"

class Model
{
protected:
	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint texture = 0;

	std::tuple<GLuint, int> modelLoaderResult;
public:

	Model() {
		glGenVertexArrays(1, &VAO); //generate the VAO
		glBindVertexArray(VAO); //bind the VAO
		glGenBuffers(1, &VBO); // generate the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		//Vertex Array Object (VAO)
		glEnableVertexAttribArray(0); //enable vertex attributes
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
	}

	void loadModel(std::string fileName) {
		modelLoaderResult = ModelLoader::loadModelFromFile(fileName);
	
		VAO = std::get<0>(modelLoaderResult);
	}

	void loadTexture(std::string fileName) {
		texture = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (texture == NULL) {
			std::cout << "An error occurred while loading image." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	void bindTexture() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void bind() {
		glBindVertexArray(VAO);
	}

	virtual void draw() = 0;

	void draw(bool disableDepthMask) {
		if (disableDepthMask) {
			glDepthMask(GL_FALSE);
		}

		draw();

		if (disableDepthMask) {
			glDepthMask(GL_TRUE);
		}
	};

	int getIndicesCount() {
		return std::get<1>(modelLoaderResult);
	}
};

