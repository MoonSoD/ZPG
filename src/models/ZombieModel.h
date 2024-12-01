#pragma once
#include "Model.h"

class ZombieModel : public Model
{
public:
	ZombieModel() : Model() {
		loadModel("./src/models/definitions/zombie/zombie.obj");
		loadTexture("./src/models/definitions/zombie/zombie.png");
	}

	void draw() override {
		bindTexture();
		glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, NULL);
	}
};

 