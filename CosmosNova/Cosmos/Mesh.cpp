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
		glm::vec3 scale,
		const glm::mat4& parentTransform)
	{

        // 2. NHÂN DỒN: Ma trận cuối cùng bao gồm cả vị trí dịch chuyển thế giới ngoài main.cpp
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 rot = glm::mat4_cast(rotation);
		glm::mat4 sca = glm::scale(glm::mat4(1.0f), scale);
		glm::mat4 finalModelMatrix = parentTransform * matrix;
        // Đảm bảo kích hoạt Shader trước khi nạp dữ liệu
        shader.UseShader();

        // ========================================================
        // BỘ NẠP TEXTURE ĐA NỀN TẢNG (ĐÃ XÓA BỎ LỆNH BREAK LỖI)
        // ========================================================
        for (unsigned int i = 0; i < m_Textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // Kích hoạt slot texture tăng dần (0, 1, 2...)

            const std::string& name = m_Textures[i].Type;

            // Kiểm tra đúng tên loại texture từ file glTF
            if (name == "texture_diffuse" || name == "texture_baseColor")
            {
                // Thiết lập sampler trong shader đọc đúng slot 'i'
                // Đảm bảo trong fragment.glsl đặt tên uniform trùng với tên bạn truyền vào ở đây
                glUniform1i(glGetUniformLocation(shader.shaderProgram, "tex0"), i);
                m_Textures[i].Bind(i);
            }
            // LƯU Ý: KHÔNG dùng lệnh 'break;' ở đây để các mesh con phía sau đều được nạp ảnh!
        }

		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "translation"), 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "scale"), 1, GL_FALSE, glm::value_ptr(sca));

		// Truyền ma trận đã tích hợp chuyển động thế giới vào biến "model"
		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(finalModelMatrix));

        // Tiến hành vẽ mô hình
        m_VAO.Bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, nullptr);

        // Trả slot texture unit về mặc định
        glActiveTexture(GL_TEXTURE0);
	}

}