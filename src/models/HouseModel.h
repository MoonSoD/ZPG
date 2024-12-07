#pragma once
#include "Model.h"

class HouseModel : public Model
{
public:
	HouseModel() : Model() {
		loadModel("./src/models/definitions/house/house.obj");
	}

	void draw() override {
		glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, NULL);
	}
};

