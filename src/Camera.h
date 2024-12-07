#pragma once

#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include <vector>
#include "ShaderProgram.h"

class ShaderProgram;

class Camera
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectMatrix;

	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;

	bool isSkyboxLocked = false;

	float alpha;
	float fi;

	std::vector<ShaderProgram*> observers;

	void notifyObservers();

public:
	Camera();

	void updateTarget();

	void recalculateViewMatrix();
	void recalculateProjectMatrix(float width, float height);

	glm::vec3 getEye();

	glm::mat4& getViewMatrix();
	glm::mat4& getProjectMatrix();

	glm::vec3& getTarget();
	
	glm::mat4 getCamera();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();

	void rotateLeft(float angle);
	void rotateRight(float angle);
	void rotateUp(float angle);
	void rotateDown(float angle);

	void addObserver(ShaderProgram* shader);
	void removeObserver(ShaderProgram* shader);

	void setSkyboxLocked(bool isSkyboxLocked);
	bool getIsSkyboxLocked();
};

