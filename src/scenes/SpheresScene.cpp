#include "SpheresScene.h"
#include "../lights/PointLight.h"

SpheresScene::SpheresScene(GLFWwindow* window, Camera* camera, Controller* controller) : Scene(window, camera, controller) {
    auto shader = new ShaderProgram("src/shaders/PhongVertexShader.glsl", "src/shaders/PhongFragmentShaderMultiple.glsl");
    shader->setCamera(this->getCamera());

    // Light* light = new Light(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.385, 0.647, 0.812));
    // this->setLight(light);

    Light* light = new Light(
        1,
        glm::vec3(0, 0, 0),
        glm::vec3(1, 1, 1),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(0.8, 0.8, 0.8),
        glm::vec3(1, 1, 1),
        glm::vec3(0.385, 0.647, 0.812),
        glm::vec3(0, 0, 0)
    );


    Light* light2 = new Light(
        2,
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(0.8, 0.8, 0.8), 
        glm::vec3(1, 1, 1),
        glm::vec3(0.385, 0.647, 0.812),
        glm::vec3(0, 0, 0)
    );


    objects["sp1"] = new DrawableObject(
        new SphereModel(),
        shader,
        TransformBuilder()
        .translate(2.0f, 0.0f, 0.0f)
        .build()
    );


    objects["sp2"] = new DrawableObject(
        new SphereModel(),
        shader,
        TransformBuilder()
        .translate(-2.0f, 0.0f, 0.0f)
        .build()
    );

    objects["sp3"] = new DrawableObject(
        new SphereModel(),
        shader,
        TransformBuilder()
        .translate(0.0f, 0.0f, 2.0f)
        .build()
    );

    objects["sp4"] = new DrawableObject(
        new SphereModel(),
        shader,
        TransformBuilder()
        .translate(0.0f, 0.0f, -2.0f)
        .build()
    );

    //light->setPosition(glm::vec3(0.0, 0.0, 0.0));
    this->setLight(light);
    // this->setLight(light2);
    // this->setLight(light3);
}

void SpheresScene::render() {
    recalculateCamera();
    this->controller->processInput();

    for (auto& obj : objects) {
        obj.second->draw();
    }
}

