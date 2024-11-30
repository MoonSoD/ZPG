#pragma once
#include "Model.h"
class TriangleModel : public Model
{
private:
	float points[9] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	   -0.5f, -0.5f, 0.0f
	};


public:
	TriangleModel() : Model() {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	}

	void draw() override {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

