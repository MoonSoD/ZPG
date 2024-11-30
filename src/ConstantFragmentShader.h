#pragma once

#include "Shader.h"

class ConstantFragmentShader : public Shader
{
public:
	ConstantFragmentShader() : Shader() {

	}

	void compile() override {
		const char* shader = this->shader();

		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shaderId, 1, &shader, NULL);
		glCompileShader(shaderId);
	}


	const char* shader() {
		return
			"#version 330\n"
			"in vec3 colour;"
			"out vec4 frag_colour;"
			"void main () {"
			"     frag_colour = vec4 (colour, 1.0);"
			"}";
	}
};

