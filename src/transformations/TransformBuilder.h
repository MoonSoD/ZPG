#pragma once
#include <vector>
#include "Transformation.h"
#include <unordered_map>

class TransformBuilder
{
private:
	std::unordered_map<std::string, std::unique_ptr<Transformation>> transforms;
public:
	TransformBuilder& rotate(float xAngle, float yAngle, float zAngle) {
		transforms["r0"] = Transformation::rotate(xAngle, yAngle, zAngle);
		return *this;
	}

	TransformBuilder& translate(float x, float y, float z) {
		transforms["t0"] = Transformation::translate(x, y, z);
		return *this;
	}

	TransformBuilder& scale(float scale) {
		transforms["s0"] = Transformation::scale(scale);
		return *this;
	}

	std::unordered_map<std::string, std::unique_ptr<Transformation>> build() {
		return std::move(transforms);
	}
};

