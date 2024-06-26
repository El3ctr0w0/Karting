#pragma once
#include <vector>
#include <iostream>
#include "Texture.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
    // model data 
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>    meshes;
    glm::vec3 Rotation;
    string directory;
    bool gammaCorrection;
    float Yaw;

    void UpdatePosition(const glm::vec3& direction);
    
    glm::mat4 GetTransformMatrix() const;
    glm::vec3 GetPosition() const { return Position; }
    // constructor, expects a filepath to a 3D model.
    Model(string const& path, bool bSmoothNormals, bool gamma = false);
    void Rotate(float angle, glm::vec3 axis);
    
    float getMidValYaw();
    glm::vec3 getMidValPosition();
    float getYaw();
    void SetPosition(const glm::vec3& newPosition);

    // draws the model, and thus all its meshes
    void Draw(Shader& shader);

private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const& path, bool bSmoothNormals);
    glm::vec3 Position;
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

