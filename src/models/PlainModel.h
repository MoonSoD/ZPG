#pragma once
#include "Model.h"
#include "definitions/plain.h"
#include "../lib/soil/include/SOIL/SOIL.h"

class PlainModel : public Model
{
public:
	PlainModel() : Model() {
		glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));

		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		texture = SOIL_load_OGL_texture("./src/textures/grass.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (texture == NULL) {
			std::cout << "An error occurred while loading image." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	void draw() override {
		glBindTexture(GL_TEXTURE_2D, texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};

