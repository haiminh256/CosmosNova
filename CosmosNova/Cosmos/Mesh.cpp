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

	void Mesh::Draw(Shader& shader, 
		glm::mat4 matrix,
		glm::vec3 translation,
		glm::quat rotation,
		glm::vec3 scale)
	{
		// Đảm bảo Shader đang được sử dụng
		shader.UseShader(); // Hoặc tùy thuộc vào hàm kích hoạt Shader của bạn

		// Bind textures
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			const std::string& name = m_Textures[i].Type;

			// Nếu là texture_diffuse (texture màu chính của xe)
			if (name == "texture_diffuse" || m_Textures[i].Type == "texture_baseColor")
			{
				m_Textures[i].Bind(i);           // Bind vào unit 0
				break; // Nếu Shader chỉ nhận 1 map chính, ta thoát vòng lặp luôn
			}
		}

		// Draw
		glm::mat4 trans = glm::mat4(1.0f);
		glm::mat4 rot = glm::mat4(1.0f);
		glm::mat4 sca = glm::mat4(1.0f);

		// Transform the matrices to their correct form
		trans = glm::translate(trans, translation);
		rot = glm::mat4_cast(rotation);
		sca = glm::scale(sca, scale);

		// Push the matrices to the vertex shader
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "scale"), 1, GL_FALSE, glm::value_ptr(sca));
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(matrix));
		m_VAO.Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, nullptr);

		// Reset texture unit
		glActiveTexture(GL_TEXTURE0);
	}

}