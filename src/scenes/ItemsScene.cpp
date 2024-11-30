#include "ItemsScene.h"
#include "../models/SquareModel.h"
#include "../models/SphereModel.h"
#include "../models/TreeModel.h"
#include "../models/BushModel.h"
#include "../transformations/TransformBuilder.h"

ItemsScene::ItemsScene(GLFWwindow* window, std::unordered_map<std::string, ShaderProgram*> shaders, Camera* camera, Controller* controller) : Scene(window, camera, controller) {
	objects["square"] = new DrawableObject(
		new SquareModel(),
		shaders["green"],
		TransformBuilder()
		.translate(0, -0.91f, 0)
		.scale(2.0f)
		.build()
	);


	objects["sphere"] = new DrawableObject(
		new SphereModel(),
		shaders["location"],
		TransformBuilder()
		.translate(0.03f, 0.7f, 0)
		.scale(0.15f)
		.rotate(0, 1.5f, 0)
		.build()
	);
	
	objects["tree"] = new DrawableObject(
		new TreeModel(),
		shaders["location"],
		TransformBuilder()
		.translate(0, -0.5f, 0)
		.scale(0.15f)
		.rotate(0, 1.5f, 0)
		.build()
	);

	objects["bush1"] = new DrawableObject(
		new BushModel(),
		shaders["location"],
		TransformBuilder()
		.translate(0.3f, -0.5f, 0)
		.rotate(0, 2.0f, 0)
		.build()
	);

	objects["bush2"] = new DrawableObject(
		new BushModel(),
		shaders["location"],
		TransformBuilder()
		.translate(-0.3f, -0.5f, 0)
		.rotate(0, 0.3f, 0)
		.build()
	);
}

void ItemsScene::render() {
	for (auto& obj : objects) {
		obj.second->draw();

	}
}