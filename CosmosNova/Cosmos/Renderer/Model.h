#pragma once
#include <Cosmos/CosmosBase.h>
#include <Cosmos/Renderer/Mesh.h>
#include <Cosmos/Shader/Shader.h>
#include <Cosmos/Renderer/Texture.h>

namespace Cosmos {
    class Model
    {
    public:
        COSMOS_API Model(const char* path);
        COSMOS_API void Draw(Shader& shader);
        COSMOS_API void Model::AddMesh(const Mesh& mesh);
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
            std::string typeName);
    };
}