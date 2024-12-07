#pragma once
#include "Model.h"

class ZombieModel : public Model
{
public:
	ZombieModel() : Model() {
		loadModel("./src/models/definitions/zombie/zombie.obj");
	}

	void draw() override {
		glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, NULL);
	}
};

 