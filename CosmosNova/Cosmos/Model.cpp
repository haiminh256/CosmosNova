#include <Cosmos/Renderer/Model.h>
#include <Cosmos/Core/Log.h>

namespace Cosmos {
    Model::Model(const char* path)
    {
        Load(path);
    }

    bool Model::Load(const char* path)
    {
        m_FilePath = path;

        //------------------------------------------------------------
        // Directory
        //------------------------------------------------------------

        size_t slash = m_FilePath.find_last_of("/");

        if (slash != std::string::npos)
            m_Directory = m_FilePath.substr(0, slash + 1);
        else
            m_Directory = "";

        //------------------------------------------------------------
        // Open glTF
        //------------------------------------------------------------

        std::ifstream file(path);

        if (!file.is_open())
        {
            CORE_ERROR("Cannot open glTF file : {}", path);
            return false;
        }

        try
        {
            file >> m_JSON;
        }
        catch (const std::exception& e)
        {
            CORE_ERROR("JSON Parse Error : {}", e.what());
            return false;
        }

        file.close();

        //------------------------------------------------------------
        // Read binary buffer
        //------------------------------------------------------------

        m_Buffer = ReadBinary();

        if (m_Buffer.empty())
        {
            CORE_ERROR("Failed to load binary buffer.");
            return false;
        }

        //------------------------------------------------------------
        // Clear previous model
        //------------------------------------------------------------

        m_Meshes.clear();

        m_LoadedTextures.clear();
        m_LoadedTextureNames.clear();

        m_MeshTranslations.clear();
        m_MeshRotations.clear();
        m_MeshScales.clear();
        m_MeshMatrices.clear();

        //------------------------------------------------------------
        // Traverse default scene
        //------------------------------------------------------------

        if (!m_JSON.contains("scene"))
        {
            CORE_ERROR("glTF has no default scene.");
            return false;
        }

        unsigned int sceneIndex = m_JSON["scene"];

        auto& scene = m_JSON["scenes"][sceneIndex];

        if (!scene.contains("nodes"))
        {
            CORE_ERROR("Scene contains no nodes.");
            return false;
        }

        for (auto& node : scene["nodes"])
        {
            TraverseNode(node.get<unsigned int>());
        }

        CORE_INFO("Model Loaded");
        CORE_INFO("Meshes : {}", m_Meshes.size());

        return true;
    }

    void Model::Draw(Shader& shader, const glm::mat4& worldTransform)
    {
        for (size_t i = 0; i < m_Meshes.size(); i++)
        {
            // Gửi ma trận worldTransform từ main.cpp vào làm tham số ma trận cha gốc cho từng Mesh
            m_Meshes[i].Draw(
                shader,
                m_MeshMatrices[i],
                m_MeshTranslations[i],
                m_MeshRotations[i],
                m_MeshScales[i],
                worldTransform // <-- THÊM THAM SỐ NÀY VÀO CUỐI HÀM
            );
        }
    }

    std::vector<unsigned char> Model::ReadBinary()
    {
        std::vector<unsigned char> buffer;

        if (!m_JSON.contains("buffers"))
        {
            CORE_ERROR("No buffers found.");
            return buffer;
        }

        std::string uri = m_JSON["buffers"][0]["uri"];

        std::string fullPath = m_Directory + uri;

        std::ifstream file(fullPath, std::ios::binary);

        if (!file.is_open())
        {
            CORE_ERROR("Cannot open binary file : {}", fullPath);
            return buffer;
        }

        file.unsetf(std::ios::skipws);

        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer.reserve(static_cast<size_t>(fileSize));

        buffer.insert(
            buffer.begin(),
            std::istream_iterator<unsigned char>(file),
            std::istream_iterator<unsigned char>());

        file.close();

        CORE_INFO("Binary Size : {} bytes", buffer.size());

        return buffer;
    }
    void Model::TraverseNode(unsigned int nodeIndex, glm::mat4 parentMatrix)
    {
        const json& node = m_JSON["nodes"][nodeIndex];

        //------------------------------------------------------------
        // Default transform
        //------------------------------------------------------------

        glm::vec3 translation(0.0f);
        glm::quat rotation(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 scale(1.0f);
        glm::mat4 localMatrix(1.0f);

        //------------------------------------------------------------
        // Translation
        //------------------------------------------------------------

        if (node.contains("translation"))
        {
            translation.x = node["translation"][0];
            translation.y = node["translation"][1];
            translation.z = node["translation"][2];
        }

        //------------------------------------------------------------
        // Rotation (glTF stores x,y,z,w)
        //------------------------------------------------------------

        if (node.contains("rotation"))
        {
            rotation = glm::quat(
                node["rotation"][3].get<float>(),
                node["rotation"][0].get<float>(),
                node["rotation"][1].get<float>(),
                node["rotation"][2].get<float>());
        }

        //------------------------------------------------------------
        // Scale
        //------------------------------------------------------------

        if (node.contains("scale"))
        {
            scale.x = node["scale"][0];
            scale.y = node["scale"][1];
            scale.z = node["scale"][2];
        }

        //------------------------------------------------------------
        // Matrix
        //------------------------------------------------------------

        if (node.contains("matrix"))
        {
            float values[16];

            for (int i = 0; i < 16; i++)
                values[i] = node["matrix"][i];

            localMatrix = glm::make_mat4(values);
        }

        //------------------------------------------------------------
        // Compose Transform
        //------------------------------------------------------------

        glm::mat4 T = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 R = glm::mat4_cast(rotation);
        glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);

        glm::mat4 globalMatrix =
            parentMatrix *
            localMatrix *
            T *
            R *
            S;

        //------------------------------------------------------------
        // Mesh
        //------------------------------------------------------------

        if (node.contains("mesh"))
        {
            m_MeshTranslations.push_back(translation);
            m_MeshRotations.push_back(rotation);
            m_MeshScales.push_back(scale);
            m_MeshMatrices.push_back(globalMatrix);

            unsigned int meshIndex = node["mesh"];

            CORE_INFO("Loading Mesh {}", meshIndex);

            LoadMesh(meshIndex);
        }

        //------------------------------------------------------------
        // Children
        //------------------------------------------------------------

        if (node.contains("children"))
        {
            for (auto& child : node["children"])
            {
                TraverseNode(
                    child.get<unsigned int>(),
                    globalMatrix);
            }
        }
    }
    void Model::LoadMesh(unsigned int meshIndex)
    {
        const json& mesh = m_JSON["meshes"][meshIndex];
        const json& primitive = mesh["primitives"][0];

        //-----------------------------------------
        // Accessor indices
        //-----------------------------------------

        unsigned int posAccessor =
            primitive["attributes"]["POSITION"];

        unsigned int normalAccessor =
            primitive["attributes"].contains("NORMAL")
            ? primitive["attributes"]["NORMAL"].get<unsigned int>()
            : posAccessor;

        unsigned int texAccessor =
            primitive["attributes"].contains("TEXCOORD_0")
            ? primitive["attributes"]["TEXCOORD_0"].get<unsigned int>()
            : posAccessor;

        unsigned int indexAccessor =
            primitive["indices"];

        //-----------------------------------------
        // Read buffers
        //-----------------------------------------

        std::vector<float> posFloats =
            ReadFloats(m_JSON["accessors"][posAccessor]);

        std::vector<float> normalFloats =
            primitive["attributes"].contains("NORMAL")
            ? ReadFloats(m_JSON["accessors"][normalAccessor])
            : std::vector<float>();

        std::vector<float> texFloats =
            primitive["attributes"].contains("TEXCOORD_0")
            ? ReadFloats(m_JSON["accessors"][texAccessor])
            : std::vector<float>();

        //-----------------------------------------
        // Convert
        //-----------------------------------------

        std::vector<glm::vec3> positions =
            GroupVec3(posFloats);

        std::vector<glm::vec3> normals;

        if (!normalFloats.empty())
            normals = GroupVec3(normalFloats);
        else
            normals.resize(
                positions.size(),
                glm::vec3(0.0f));

        std::vector<glm::vec2> texCoords;

        if (!texFloats.empty())
            texCoords = GroupVec2(texFloats);
        else
            texCoords.resize(
                positions.size(),
                glm::vec2(0.0f));

        std::vector<Vertex> vertices =
            AssembleVertices(
                positions,
                normals,
                texCoords);

        std::vector<unsigned int> indices =
            ReadIndices(m_JSON["accessors"][indexAccessor]);

        std::vector<Texture> textures =
            LoadTextures(primitive);

        m_Meshes.emplace_back(
            std::move(vertices),
            std::move(indices),
            std::move(textures));

        CORE_INFO(
            "Mesh {} loaded ({} vertices, {} indices)",
            meshIndex,
            positions.size(),
            indices.size());
    }
    std::vector<float> Model::ReadFloats(const json& accessor)
    {
        std::vector<float> values;

        //------------------------------------------
        // Accessor
        //------------------------------------------

        unsigned int bufferViewIndex = accessor["bufferView"];
        unsigned int componentType = accessor["componentType"];
        unsigned int count = accessor["count"];

        unsigned int accessorOffset = 0;
        if (accessor.contains("byteOffset"))
            accessorOffset = accessor["byteOffset"];

        //------------------------------------------
        // glTF currently only supports float here
        //------------------------------------------

        if (componentType != 5126)
        {
            CORE_ERROR("Accessor is not FLOAT!");
            return values;
        }

        //------------------------------------------
        // BufferView
        //------------------------------------------

        const json& bufferView = m_JSON["bufferViews"][bufferViewIndex];

        unsigned int bufferOffset = 0;
        if (bufferView.contains("byteOffset"))
            bufferOffset = bufferView["byteOffset"];

        unsigned int stride = 0;

        //------------------------------------------
        // Number of components
        //------------------------------------------

        std::string type = accessor["type"];

        unsigned int componentCount = 0;

        if (type == "SCALAR")
            componentCount = 1;
        else if (type == "VEC2")
            componentCount = 2;
        else if (type == "VEC3")
            componentCount = 3;
        else if (type == "VEC4")
            componentCount = 4;
        else
        {
            CORE_ERROR("Unsupported accessor type {}", type);
            return values;
        }

        //------------------------------------------
        // Byte stride
        //------------------------------------------

        if (bufferView.contains("byteStride"))
            stride = bufferView["byteStride"];
        else
            stride = componentCount * sizeof(float);

        //------------------------------------------
        // Read
        //------------------------------------------

        size_t offset = bufferOffset + accessorOffset;

        values.reserve(count * componentCount);

        for (unsigned int i = 0; i < count; i++)
        {
            const unsigned char* ptr =
                m_Buffer.data() + offset + i * stride;

            const float* floatPtr =
                reinterpret_cast<const float*>(ptr);

            for (unsigned int j = 0; j < componentCount; j++)
            {
                values.push_back(floatPtr[j]);
            }
        }

        return values;
    }
    std::vector<Texture> Model::LoadTextures(const json& primitive)
    {
        std::vector<Texture> textures;

        if (!primitive.contains("material"))
            return textures;

        unsigned int materialIndex = primitive["material"];
        json material = m_JSON["materials"][materialIndex];

        if (!material.contains("pbrMetallicRoughness"))
            return textures;

        json pbr = material["pbrMetallicRoughness"];

        //============================
        // Base Color Texture
        //============================
        if (pbr.contains("baseColorTexture"))
        {
            unsigned int texIndex = pbr["baseColorTexture"]["index"];

            unsigned int imageIndex =
                m_JSON["textures"][texIndex]["source"];

            std::string uri =
                m_JSON["images"][imageIndex]["uri"];

            bool found = false;

            for (size_t i = 0; i < m_LoadedTextureNames.size(); i++)
            {
                if (m_LoadedTextureNames[i] == uri)
                {
                    textures.push_back(m_LoadedTextures[i]);
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                Texture tex;

                tex.setType("texture_diffuse");
                tex.setPath(m_Directory + "/" + uri);

                tex.Load(m_Directory + "/" + uri, true);

                m_LoadedTextures.push_back(tex);
                m_LoadedTextureNames.push_back(uri);

                textures.push_back(tex);
            }
        }

        return textures;
    }
    std::vector<Vertex> Model::AssembleVertices(
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec3>& normals,
        const std::vector<glm::vec2>& texCoords) {
        std::vector<Vertex> vertices;
        vertices.reserve(positions.size());

        for (size_t i = 0; i < positions.size(); i++)
        {
            Vertex vertex{};

            vertex.Position = positions[i];

            if (i < normals.size())
                vertex.Normal = normals[i];
            else
                vertex.Normal = glm::vec3(0.0f);

            vertex.Color = glm::vec4(1.0f);

            if (i < texCoords.size())
            {
                vertex.TexCoord = glm::vec2(texCoords[i].x, 1.0f - texCoords[i].y); // Flip Y
            }
            else
            {
                vertex.TexCoord = glm::vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }

        return vertices;
    }
    std::vector<unsigned int> Model::ReadIndices(const json& accessor)
    {
        std::vector<unsigned int> indices;

        unsigned int bufferViewIndex = accessor["bufferView"];
        unsigned int count = accessor["count"];
        unsigned int componentType = accessor["componentType"];

        unsigned int accessorOffset = accessor.contains("byteOffset") ? accessor["byteOffset"].get<unsigned int>() : 0;

        const json& bufferView = m_JSON["bufferViews"][bufferViewIndex];
        unsigned int bufferOffset = bufferView.contains("byteOffset") ? bufferView["byteOffset"].get<unsigned int>() : 0;

        size_t offset = bufferOffset + accessorOffset;

        // glTF indices thường là UNSIGNED_SHORT (5123) hoặc UNSIGNED_INT (5125)
        if (componentType == 5123) // UNSIGNED_SHORT
        {
            indices.reserve(count);
            for (unsigned int i = 0; i < count; i++)
            {
                const unsigned char* ptr = m_Buffer.data() + offset + i * sizeof(unsigned short);
                unsigned short value = *reinterpret_cast<const unsigned short*>(ptr);
                indices.push_back(value);
            }
        }
        else if (componentType == 5125) // UNSIGNED_INT
        {
            indices.reserve(count);
            for (unsigned int i = 0; i < count; i++)
            {
                const unsigned char* ptr = m_Buffer.data() + offset + i * sizeof(unsigned int);
                unsigned int value = *reinterpret_cast<const unsigned int*>(ptr);
                indices.push_back(value);
            }
        }
        else
        {
            CORE_ERROR("Unsupported index component type: {}", componentType);
        }

        return indices;
    }

    std::vector<glm::vec3> Model::GroupVec3(const std::vector<float>& floats)
    {
        std::vector<glm::vec3> vectors;
        vectors.reserve(floats.size() / 3);

        for (size_t i = 0; i < floats.size(); i += 3)
        {
            vectors.emplace_back(floats[i], floats[i + 1], floats[i + 2]);
        }
        return vectors;
    }

    std::vector<glm::vec2> Model::GroupVec2(const std::vector<float>& floats)
    {
        std::vector<glm::vec2> vectors;
        vectors.reserve(floats.size() / 2);

        for (size_t i = 0; i < floats.size(); i += 2)
        {
            vectors.emplace_back(floats[i], floats[i + 1]);
        }
        return vectors;
    }

    std::vector<glm::vec4> Model::GroupVec4(const std::vector<float>& floats)
    {
        std::vector<glm::vec4> vectors;
        vectors.reserve(floats.size() / 4);

        for (size_t i = 0; i < floats.size(); i += 4)
        {
            vectors.emplace_back(floats[i], floats[i + 1], floats[i + 2], floats[i + 3]);
        }
        return vectors;
    }
}