#pragma once
#include "../ShaderProgram.h"
#include <cstddef>
#include <iostream>

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
};

