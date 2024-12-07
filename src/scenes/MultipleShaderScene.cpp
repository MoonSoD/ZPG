#include "MultipleShaderScene.h"
#include "../models/SphereModel.h"
#include "../models/TreeModel.h"
#include "../models/BushModel.h"
#include "../transformations/TransformBuilder.h"
#include "../lights/PointLight.h"

MultipleShaderScene::MultipleShaderScene(GLFWwindow* window, Camera* camera, Controller* controller) : Scene(window, camera, controller) {
    auto light = new PointLight(
        glm::vec3(0, 0, 0),
        glm::vec3(0, 0, 0)
    );

	Material* material = new Material(glm::vec3(0.385, 0.647, 0.812));

	auto lambertShader = new ShaderProgram("src/shaders/LambertVertexShader.glsl", "src/shaders/LambertFragmentShader.glsl");
	lambertShader->setCamera(camera);

	objects["lambertSphere"] = new DrawableObject(
		new SphereModel(),
		lambertShader,
		material,
		TransformBuilder()
		.build()
	);

	objects["lambertTree"] = new DrawableObject(
		new TreeModel(),
		lambertShader,
		material,
		TransformBuilder()
		.translate(0, 3.0f, 0)
		.build()
	);

	auto phongShader = new ShaderProgram("src/shaders/PhongVertexShader.glsl", "src/shaders/PhongFragmentShader.glsl");
	phongShader->setCamera(camera);

	objects["phongSphere"] = new DrawableObject(
		new SphereModel(),
		phongShader,
		material,
		TransformBuilder()
		.translate(5.0f, 0, 0)
		.build()
	);


	objects["phongTree"] = new DrawableObject(
		new TreeModel(),
		phongShader,
		material,
		TransformBuilder()
		.translate(5.0f, 3.0f, 0)
		.build()
	);

	auto constShader = new ShaderProgram("src/shaders/ConstantVertexShader.glsl", "src/shaders/GreenFragmentShader.glsl");
	constShader->setCamera(camera);

	objects["constSphere"] = new DrawableObject(
		new SphereModel(),
		constShader,
		TransformBuilder()
		.translate(-5.0f, 0, 0)
		.build()
	);

	objects["constTree"] = new DrawableObject(
		new TreeModel(),
		constShader,
		TransformBuilder()
		.translate(-5.0f, 3.0f, 0)
		.build()
	);

	auto blinnShader = new ShaderProgram("src/shaders/BlinnVertexShader.glsl", "src/shaders/BlinnFragmentShader.glsl");
	blinnShader->setCamera(camera);

	objects["blinnSphere"] = new DrawableObject(
		new SphereModel(),
		blinnShader,
		material,
		TransformBuilder()
		.translate(-10.0f, 0, 0)
		.build()
	);

	objects["blinnTree"] = new DrawableObject(
		new TreeModel(),
		blinnShader,
		material,
		TransformBuilder()
		.translate(-10.0f, 3.0f, 0)
		.build()
	);

	this->setLight(light);

	// this->light->setPosition(glm::vec3(10.0f, 30.0f, 10.0f));
}

void MultipleShaderScene::render() {
	recalculateCamera();
	this->controller->processInput();

	for (auto& obj : objects) {
		obj.second->draw();
	}
}
