#include <Cosmos/Renderer/Mesh.h>
#include <Cosmos/Core/Log.h>

namespace Cosmos
{

	Mesh::Mesh(
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<Texture>& textures)
		:
		m_Vertices(vertices),
		m_Indices(indices),
		m_Textures(textures)
	{
		SetupMesh();
	}

	Mesh::~Mesh()
	{
		m_VAO.Delete();
		m_VBO.Delete();
		m_EBO.Delete();
	}

	void Mesh::SetupMesh()
	{
		m_VAO.Bind();

		m_VBO.Bind();
		m_VBO.LoadData(
			m_Vertices.data(),
			static_cast<unsigned int>(m_Vertices.size() * sizeof(Vertex)));

		m_EBO.Bind();
		m_EBO.LoadData(
			m_Indices.data(),
			static_cast<unsigned int>(m_Indices.size() * sizeof(unsigned int)));

		// Vertex Attributes
		m_VAO.VertexAttribPointer(0, 3, sizeof(Vertex), offsetof(Vertex, Position));
		m_VAO.VertexAttribPointer(1, 3, sizeof(Vertex), offsetof(Vertex, Normal));
		m_VAO.VertexAttribPointer(2, 4, sizeof(Vertex), offsetof(Vertex, Color));
		m_VAO.VertexAttribPointer(3, 2, sizeof(Vertex), offsetof(Vertex, TexCoord));
	}

	void Mesh::Draw(Shader& shader)
	{
		// Bind textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;

		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			const std::string& name = m_Textures[i].Type;
			std::string number;
			std::string uniformName;

			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);
			else
				number = std::to_string(1);

			uniformName = name + number;

			m_Textures[i].Bind(i);
		}

		// Draw
		m_VAO.Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, nullptr);

		// Reset texture unit
		glActiveTexture(GL_TEXTURE0);
	}

}