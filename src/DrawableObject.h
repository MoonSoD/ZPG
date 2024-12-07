#pragma once
#include "models/Model.h"
#include "transformations/Transformation.h"
#include <memory>
#include <vector>


class DrawableObject
{
private:
	Model* model;
	std::unordered_map<std::string, std::unique_ptr<Transformation>> transforms;
	ShaderProgram* program;

public:
	DrawableObject(Model* model, ShaderProgram* program, std::unordered_map<std::string, std::unique_ptr<Transformation>>&& transforms)
		: model(model), program(program), transforms(std::move(transforms)) {
	}

	DrawableObject(Model* model, ShaderProgram* program) 
		: model(model), program(program) {}

	void setTransform(std::string key, std::unique_ptr<Transformation>&& transform) {
		transforms[key] = std::move(transform);
	}

	Transformation* getTransform(std::string key) {
		return transforms[key].get();
	}

	void updateLight(Light* light, int lightIndex) {
		this->program->updateLight(light, lightIndex);
	}

	void draw() {
		draw(false);
	}

	void draw(bool disableDepthMask) {
		glm::mat4 finalTransform = glm::mat4(1.0f);

		for (auto& transform : transforms) {
			finalTransform *= transform.second->getMatrix();
		}

		program->applyTransformation(finalTransform);

		program->useProgram();
		model->bind();
		model->draw(disableDepthMask);
		glUseProgram(0);
	}
};
