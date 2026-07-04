#include <Cosmos/Vertex/ElementBuffer.h>

namespace Cosmos {
	ElementBuffer::ElementBuffer() {
		glGenBuffers(1, &id);
	}
	void ElementBuffer::LoadData(const void* data, GLsizeiptr size) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	void ElementBuffer::Delete() {
		glDeleteBuffers(1, &id);
	}
	void ElementBuffer::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
}