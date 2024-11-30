#pragma once
#include "Model.h"
#include "definitions/sphere.h"
class SphereModel : public Model
{
public:
	SphereModel() : Model() {
		glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	}

	void draw() override {
		glDrawArrays(GL_TRIANGLES, 0, 2880);
	}
};

