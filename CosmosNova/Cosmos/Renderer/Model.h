#pragma once

#include <Cosmos/CosmosBase.h>

#include <Cosmos/Shader/Shader.h>
#include <Cosmos/Renderer/Mesh.h>
#include <Cosmos/Renderer/Texture.h>

namespace Cosmos
{
    using json = nlohmann::json;

    class Model
    {
    public:

        COSMOS_API Model() = default;
        COSMOS_API explicit Model(const char* path);

        COSMOS_API bool Load(const char* path);

        COSMOS_API void Draw(Shader& shader, const glm::mat4& worldTransform = glm::mat4(0.0f));

    private:

        //---------------------------------------------------------
        // File
        //---------------------------------------------------------

        std::string m_FilePath;
        std::string m_Directory;

        json m_JSON;
        std::vector<unsigned char> m_Buffer;

        //---------------------------------------------------------
        // Scene Data
        //---------------------------------------------------------

        std::vector<Mesh> m_Meshes;

        //---------------------------------------------------------
        // Texture Cache
        //---------------------------------------------------------

        std::vector<Texture> m_LoadedTextures;
        std::vector<std::string> m_LoadedTextureNames;

        //---------------------------------------------------------
        // Transform Cache
        //---------------------------------------------------------

        std::vector<glm::vec3> m_MeshTranslations;
        std::vector<glm::quat> m_MeshRotations;
        std::vector<glm::vec3> m_MeshScales;
        std::vector<glm::mat4> m_MeshMatrices;

        //---------------------------------------------------------
        // Scene Traversal
        //---------------------------------------------------------

        void TraverseNode(
            unsigned int nodeIndex,
            glm::mat4 parentMatrix = glm::mat4(1.0f));

        void LoadMesh(unsigned int meshIndex);

        //---------------------------------------------------------
        // Buffer Reading
        //---------------------------------------------------------

        std::vector<unsigned char> ReadBinary();

        std::vector<float> ReadFloats(
            const json& accessor);

        std::vector<unsigned int> ReadIndices(
            const json& accessor);

        //---------------------------------------------------------
        // Texture
        //---------------------------------------------------------

        std::vector<Texture> LoadTextures(
            const json& primitive);

        //---------------------------------------------------------
        // Vertex
        //---------------------------------------------------------

        std::vector<Vertex> AssembleVertices(
            const std::vector<glm::vec3>& positions,
            const std::vector<glm::vec3>& normals,
            const std::vector<glm::vec2>& texCoords);

        //---------------------------------------------------------
        // Helpers
        //---------------------------------------------------------

        std::vector<glm::vec2> GroupVec2(
            const std::vector<float>& data);

        std::vector<glm::vec3> GroupVec3(
            const std::vector<float>& data);

        std::vector<glm::vec4> GroupVec4(
            const std::vector<float>& data);
    };

}