#include "BasicScene.h"
#include "../models/TriangleModel.h"
#include "../transformations/TransformBuilder.h"

BasicScene::BasicScene(GLFWwindow* window, Camera* camera, Controller* controller) : Scene(window, camera, controller) {
	auto shader = new ShaderProgram("src/shaders/ConstantVertexShader.glsl", "src/shaders/GreenFragmentShader.glsl");
	shader->setCamera(camera);

	objects["triangle"] = new DrawableObject(
		new TriangleModel(),
		shader,
		TransformBuilder()
		.rotate(0, 1.4, 0)
		.translate(0, 0, 1.0f)
		.build()
	);
}

void BasicScene::render() {
	recalculateCamera();
	this->controller->processInput();

	for (auto& obj : objects) {
		obj.second->draw();
	}
}