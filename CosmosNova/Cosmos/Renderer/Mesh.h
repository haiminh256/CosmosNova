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

		COSMOS_API ~Mesh();

		COSMOS_API void Draw(Shader& shader);

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