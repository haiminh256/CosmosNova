#include <Cosmos/Vertex/VertexBuffer.h>

namespace Cosmos {
	VertexBuffer::VertexBuffer() {
		glGenBuffers(1, &id);
	}
	VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	{
		id = other.id;
		other.id = 0;
	}
	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			id = other.id;
			other.id = 0;
		}

		return *this;
	}
	void VertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void VertexBuffer::LoadData(const void* data, GLsizeiptr size) {
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	void VertexBuffer::Delete() {
		glDeleteBuffers(1, &id);
	}
}