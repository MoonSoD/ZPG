#pragma once
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include <memory> 

class Transformation
{
private:
	glm::mat4 matrix;

public:
	Transformation(const glm::mat4& matrix) : matrix(matrix) {}

	glm::mat4 getMatrix() {
		return this->matrix;
	}

	static std::unique_ptr<Transformation> rotateX(float angle) {
		glm::mat4 matrix = glm::mat4(1);
		matrix = glm::rotate(matrix, angle, glm::vec3(1.0f, 0.0f, 0.0f));

		return std::make_unique<Transformation>(matrix);
	}

	static std::unique_ptr<Transformation> rotateY(float angle) {
		glm::mat4 matrix = glm::mat4(1);
		matrix = glm::rotate(matrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));

		return std::make_unique<Transformation>(matrix);
	}

	static std::unique_ptr<Transformation> rotateZ(float angle) {
		glm::mat4 matrix = glm::mat4(1);
		matrix = glm::rotate(matrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));

		return std::make_unique<Transformation>(matrix);
	}

	static std::unique_ptr<Transformation> rotate(float xAnngle, float yAngle, float zAngle) {
		glm::mat4 matrix = glm::mat4(1);
		matrix = glm::rotate(matrix, xAnngle, glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, yAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, zAngle, glm::vec3(0.0f, 0.0f, 1.0f));

		return std::make_unique<Transformation>(matrix);
	}

	static std::unique_ptr<Transformation> scale(float scale) {
		glm::mat4 matrix = glm::mat4(1);
		matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));

		return std::make_unique<Transformation>(matrix);
	}

	static std::unique_ptr<Transformation> translate(float x, float y, float z) {
		glm::mat4 matrix = glm::mat4(1);
		matrix = glm::translate(matrix, glm::vec3(x, y, z));

		return std::make_unique<Transformation>(matrix);
	}
};
