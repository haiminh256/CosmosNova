#pragma once

#include <Cosmos/CosmosBase.h>

#include <Cosmos/Vertex/Vertex.h>
#include <Cosmos/Renderer/Texture.h>

#include <Cosmos/Vertex/VertexArray.h>
#include <Cosmos/Vertex/VertexBuffer.h>
#include <Cosmos/Vertex/ElementBuffer.h>
#include <Cosmos/Shader/Shader.h>

namespace Cosmos
{
	class Mesh
	{
	public:
		COSMOS_API Mesh(
			const std::vector<Vertex>& vertices,
			const std::vector<unsigned int>& indices,
			const std::vector<Texture>& textures = {});
		COSMOS_API Mesh(const Mesh&) = delete;
		COSMOS_API Mesh& operator=(const Mesh&) = delete;
		COSMOS_API Mesh(Mesh&&) noexcept = default;
		COSMOS_API Mesh& operator=(Mesh&&) noexcept = default;
		COSMOS_API ~Mesh();

		COSMOS_API void Draw(Shader& shader, glm::mat4 matrix = glm::mat4(1.0f),
			glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
		);

	private:
		void SetupMesh();

	private:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture> m_Textures;

		VertexArray m_VAO;
		VertexBuffer m_VBO;
		ElementBuffer m_EBO;
	};
}