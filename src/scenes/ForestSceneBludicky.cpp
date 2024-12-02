#include "ForestSceneBludicky.h"
#include "../models/SquareModel.h"
#include "../models/TreeModel.h"
#include "../models/BushModel.h"
#include "../transformations/TransformBuilder.h"

#define _USE_MATH_DEFINES
#include <random>
#include <math.h>

ForestSceneBludicky::ForestSceneBludicky(GLFWwindow* window, Camera* camera, Controller* controller) : Scene(window, camera, controller) {
	auto shader = new ShaderProgram("src/shaders/PhongVertexShader.glsl", "src/shaders/PhongFragmentShaderMultiple.glsl");
	shader->setCamera(this->getCamera());


	// Light* light = new Light(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.385, 0.647, 0.812));
	// this->setLight(light);
    auto light = new Light(
		1,
        glm::vec3(0, 5, 0),
        glm::vec3(1, 1, 1),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(1, 1, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(0.385, 0.647, 0.812),
        glm::vec3(0, 0, 0)
    );

	auto light2 = new Light(
		1,
        glm::vec3(20, 5, 0),
        glm::vec3(1, 1, 1),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(1, 1, 1),
        glm::vec3(1, 1, 1),
        glm::vec3(0.385, 0.647, 0.812),
        glm::vec3(0, 0, 0)
    );


	int numTrees = 50;
	int numBushes = 150;

	std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
	std::uniform_real_distribution<float> xDist(-25.0f, 25.0f);  // X range
	std::uniform_real_distribution<float> zDist(-25.0f, 25.0f);  // Z range
	std::uniform_real_distribution<float> treeScaleDist(0.8f, 1.2f); // Tree scale range
	std::uniform_real_distribution<float> bushScaleDist(0.8f, 2.f); // Bush scale range
	std::uniform_real_distribution<float> rotationDist(0.0f, 2 * M_PI); // Rotation range in radians

	for (int i = 0; i < numTrees; ++i) {
		float x = xDist(rng);
		float z = zDist(rng);
		float y = -1.4f;
		float scale = treeScaleDist(rng);
		float rotationY = rotationDist(rng);

		std::string treeIndex = "tree_" + std::to_string(i);

		objects[treeIndex] = new DrawableObject(
			new TreeModel(),
			shader,
			TransformBuilder()
			.scale(scale)
			.rotate(0, rotationY, 0)
			.translate(x, y, z)
			.build()
		);
	}

	for (int i = 0; i < numBushes; ++i) {
		float x = xDist(rng);
		float z = zDist(rng);
		float y = -1.4f;
		float scale = bushScaleDist(rng);
		float rotationY = rotationDist(rng);

		std::string bushIndex = "bush_" + std::to_string(i);

		objects[bushIndex] = new DrawableObject(
			new BushModel(),
			shader,
			TransformBuilder()
			.translate(x, y, z)
			.scale(scale)
			.rotate(0, rotationY, 0)
			.build()
		);
	}

	objects["ground"] = new DrawableObject(
		new SquareModel(),
		shader,
		TransformBuilder()
		.translate(0, -1.5f, 0)
		.scale(200.0f)
		.rotate(1.57f, 0, 0)
		.build()
	);

	this->setLight(light);
	this->setLight(light2);
	// this->setLight(light3);
	// light->setPosition(glm::vec3(0.0, 0.0, 0.0));
}

void ForestSceneBludicky::render() {
	recalculateCamera();

    this->controller->processInput();


    for (auto& light : lights) {
		if (light->getType() != 1) {
			continue;
		}

        float randomX = ((std::rand() % 100) / 100.0f) - 0.5;  
        float randomZ = ((std::rand() % 100) / 100.0f) - 0.5; 
	
        glm::vec3 currentPosition = light->getPosition();

        glm::vec3 newPosition = glm::vec3(
            currentPosition.x + randomX * 1.2f,
            currentPosition.y,
			currentPosition.z + randomZ * 1.2f
        );

        light->setPosition(newPosition);
    } 

	rotation += 0.001f;

	if (rotation > 2 * M_PI) {
		rotation = 0;
	}

    for (auto& obj : objects) {
        if (obj.first.find("tree") != std::string::npos) {
            obj.second->setTransform("r0", Transformation::rotate(0, rotation, 0));  
        }

        obj.second->draw();  
    }
}

