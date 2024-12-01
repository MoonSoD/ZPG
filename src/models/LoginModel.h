#pragma once
#include "Model.h"

class LoginModel : public Model
{
public:
	LoginModel() : Model() {
		loadModel("./src/models/definitions/login/login.obj");
	}

	void draw() override {
		glDrawElements(GL_TRIANGLES, getIndicesCount(), GL_UNSIGNED_INT, NULL);
	}
};

 