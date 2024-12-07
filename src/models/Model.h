#pragma once
#include "../ShaderProgram.h"
#include <cstddef>
#include <iostream>

#include "ModelLoader.h"
#include "../materials/Material.h"

class Model
{
protected:
	GLuint VBO = 0;
	GLuint VAO = 0;

	std::tuple<GLuint, int, std::vector<Material>> modelLoaderResult;
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
		//materials = std::get<2>(modelLoaderResult);
	}

	void bind() {
		glBindVertexArray(VAO);
	}

	virtual void draw() = 0;

	/* 
	* @deprecated
	*/
	void draw(bool disableDepthMask) {
		draw();
	};

	int getIndicesCount() {
		return std::get<1>(modelLoaderResult);
	}
};

