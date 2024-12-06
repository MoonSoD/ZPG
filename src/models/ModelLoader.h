#pragma once

#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags

#include <GL/glew.h>

#include "../materials/Material.h"

#include <iostream>

struct Vertex {
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

class ModelLoader {
    public:
        static std::tuple<GLuint, int, std::vector<Material>> loadModelFromFile(std::string fileName);
};