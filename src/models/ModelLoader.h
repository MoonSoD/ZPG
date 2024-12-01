#pragma once

#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags
#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <iostream>

struct Vertex {
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};


std::tuple<GLuint, int> load(std::string fileName)
{
    GLuint VAO = 0;
    int indicesCount = 0;
    GLuint err = glGetError();

    if (err != GL_NO_ERROR) {
        std::cout << "B4 importer GL ERROR: " << err << std::endl;
    }

    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate //Converts polygons to triangles
        | aiProcess_OptimizeMeshes              // Reduces the number of submeshes
        //| aiProcess_JoinIdenticalVertices       // Removes duplicate vertices
        //| aiProcess_CalcTangentSpace;           // Computes tangents and bitangents
        ;
    //aiProcess_GenNormals/ai_Process_GenSmoothNormals - Generates flat/Smooth normals



    if (err != GL_NO_ERROR) {
        std::cout << "B4 sucecssfull read GL ERROR: " << err << std::endl;
    }

    const aiScene* scene = importer.ReadFile(fileName, importOptions);
 

    if (scene) { //pokud bylo nacteni uspesne

        if (err != GL_NO_ERROR) {
            std::cout << "After sucecssfull read GL ERROR: " << err << std::endl;
        }
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);
        //Materials
        for (unsigned int i = 0; i < scene->mNumMaterials; i++)
        {
            const aiMaterial* mat = scene->mMaterials[i];
            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name %s\n", i, name.C_Str());
            aiColor4D d;
            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);
        }

        if (err != GL_NO_ERROR) {
            std::cout << "Before branch GL ERROR: " << err << std::endl;
        }
        
        //Objects
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[i];
            Vertex* pVertices = new Vertex[mesh->mNumVertices];
            std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);
            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions()) {
                    pVertices[i].Position[0] = mesh->mVertices[i].x;
                    pVertices[i].Position[1] = mesh->mVertices[i].y;
                    pVertices[i].Position[2] = mesh->mVertices[i].z;
                }

                if (mesh->HasNormals()) {
                    pVertices[i].Normal[0] = mesh->mNormals[i].x;
                    pVertices[i].Normal[1] = mesh->mNormals[i].y;
                    pVertices[i].Normal[2] = mesh->mNormals[i].z;
                }

                if (mesh->HasTextureCoords(0)) {
                    pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                    pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                }

                if (mesh->HasTangentsAndBitangents()) {
                    pVertices[i].Tangent[0] = mesh->mTangents[i].x;
                    pVertices[i].Tangent[1] = mesh->mTangents[i].y;
                    pVertices[i].Tangent[2] = mesh->mTangents[i].z;
                }
            }

            if (err != GL_NO_ERROR) {
                std::cout << "Mesh branch GL ERROR: " << err << std::endl;
            }

            unsigned int* pIndices = nullptr;
            if (mesh->HasFaces()) {
                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }

            err = glGetError();
            if (err != GL_NO_ERROR) {
                std::cout << "Mesh GL ERROR: " << err << std::endl;
            }

            glGenVertexArrays(1, &VAO);

            GLuint VBO = 0;
            glGenBuffers(1, &VBO);

            GLuint IBO = 0;
            glGenBuffers(1, &IBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));

            err = glGetError();
            if (err != GL_NO_ERROR) {
                std::cout << "MEM GL ERROR: " << err << std::endl;
            }

            //Tangent for Normal Map
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

            err = glGetError();
            if (err != GL_NO_ERROR) {
                std::cout << "Tangent for normal mapGL ERROR: " << err << std::endl;
            }

            //Index Buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(VAO);

            err = glGetError();
            if (err != GL_NO_ERROR) {
                std::cout << "GL ERROR: " << err << std::endl;
            }
            indicesCount = mesh->mNumFaces * 3;
            delete[] pVertices;
            delete[] pIndices;
        }
    }
    else {
        printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
    }

    glBindVertexArray(0);

    return std::make_tuple(VAO, indicesCount);
}
