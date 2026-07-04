#include <Cosmos/Vertex/VertexBuffer.h>

namespace Cosmos {
	VertexBuffer::VertexBuffer() {
		glGenBuffers(1, &id);
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