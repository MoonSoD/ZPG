#pragma once

#include "Shader.h"
#include "lights/Light.h"
#include <glm/mat4x4.hpp> 
#include "ShaderLoader.h"
#include "materials/Material.h"

class Camera;

class ShaderProgram
{
private:
	GLuint id;
	GLint linkStatus;

	Camera* camera;
public:
	ShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);
	
	void useProgram();

	void setCamera(Camera* camera);

	void updateCamera();

	void updateLight(Light* light, int lightIndex);

	void updateLight(glm::vec3& eye, glm::vec3& target);

	void applyTransformation(glm::mat4 matrix);

	void applyMaterial(Material* material);
};

 