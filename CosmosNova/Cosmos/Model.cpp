#include <Cosmos/Renderer/Model.h>
#include <Cosmos/Core/Log.h>

namespace Cosmos {

    void Model::Draw(Shader& shader)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }
    Model::Model(const char* path) {
        loadModel(path);
    }
    void Model::loadModel(std::string path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            CORE_ERROR("Failed to load model");
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }
    void Model::processNode(aiNode* node, const aiScene* scene)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }
    Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // ==================== XỬ LÝ VERTEX ====================
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;

            // Position
            vertex.Position = glm::vec3(
                mesh->mVertices[i].x,
                mesh->mVertices[i].y,
                mesh->mVertices[i].z
            );

            // Normal
            if (mesh->HasNormals())
            {
                vertex.Normal = glm::vec3(
                    mesh->mNormals[i].x,
                    mesh->mNormals[i].y,
                    mesh->mNormals[i].z
                );
            }
            else
            {
                vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
            }

            // Texture Coordinates
            if (mesh->mTextureCoords[0])
            {
                vertex.TexCoord = glm::vec2(
                    mesh->mTextureCoords[0][i].x,
                    mesh->mTextureCoords[0][i].y
                );
            }
            else
            {
                vertex.TexCoord = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        // ==================== XỬ LÝ INDICES ====================
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // ==================== XỬ LÝ MATERIAL / TEXTURE ====================
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            // Load diffuse texture (thường là texture chính)
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
                aiTextureType_DIFFUSE,
                "texture_diffuse");

            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        }

        // Trả về Mesh
        return Mesh(vertices, indices, textures);
    }
    std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            std::string fullPath = directory + "/" + str.C_Str();

            CORE_INFO("Loading texture from: {}", fullPath);

            Texture texture;                          // Tạo object Texture
            if (texture.Load(fullPath, true))         // true = flip vertically
            {
                texture.setType(typeName);            // Gọi setter
                // texture.setPath(str.C_Str());      // Nếu cần

                textures.push_back(texture);
            }
            else
            {
                CORE_ERROR("Failed to load texture: {}", fullPath);
            }
        }

        return textures;
    }
    void Model::AddMesh(const Mesh& mesh)
    {
        meshes.push_back(mesh);
    }
}