#pragma once
#include "Model.h"

class HouseModel : public Model
{
public:
	HouseModel() : Model() {
		loadModel("./src/models/definitions/house/house.obj");
		loadTexture("./src/models/definitions/house/house.png");
	}

	void draw() override {
		bindTexture();

		glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, NULL);
	}
};

