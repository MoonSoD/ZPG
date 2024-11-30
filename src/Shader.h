#pragma once
#include <GL/glew.h>
#include <cstddef>
#include <cstdio>
class Shader
{
protected:
	GLuint shaderId = 0;
public:
	Shader() {}

	virtual const char* shader() = 0;

	virtual void compile() = 0;

	GLuint getId() {
		return this->shaderId;
	}
};

