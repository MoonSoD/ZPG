#pragma once
#include "Model.h"
class SquareModel : public Model
{
private:
	float points[12] = {
		-0.2f, -0.2f, 0.0f, 
		 0.2f, -0.2f, 0.0f,
		 0.2f,  0.2f, 0.0f, 
		-0.2f,  0.2f, 0.0f   
	};


public:
	SquareModel() : Model() {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	}

	void draw() override {
		glDrawArrays(GL_QUADS, 0, 4);
	}
};

