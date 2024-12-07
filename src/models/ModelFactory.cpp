#include "ModelFactory.h"

#include "BushModel.h"
#include "HouseModel.h"
#include "PlainModel.h"
#include "SphereModel.h"
#include "TreeModel.h"
#include "ZombieModel.h"
#include "LoginModel.h"
#include "TriangleModel.h"
#include "Skybox.h"

Model* ModelFactory::createModel(std::string modelName) {
    if (modelName == "bush") {
        return new BushModel();
    }

    if (modelName == "house") {
        return new HouseModel();
    }

    if (modelName == "plain") {
        return new PlainModel();
    }

    if (modelName == "sphere") {
        return new SphereModel();
    }

    if (modelName == "tree") {
        return new TreeModel();
    }

    if (modelName == "zombie") {
        return new ZombieModel();
    }

    if (modelName == "login") {
        return new LoginModel();
    }

    if (modelName == "triangle") {
        return new TriangleModel();
    }

    if (modelName == "skybox") {
        return new Skybox();
    }

    return nullptr;
}