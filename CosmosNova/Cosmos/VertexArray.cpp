#include <Cosmos/Vertex/VertexArray.h>

namespace Cosmos {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &id);
	}
	void VertexArray::Bind() {
		glBindVertexArray(id);
	}
	void VertexArray::VertexAttribPointer(unsigned int layout, unsigned int component, GLsizei stride, unsigned int offset) {
		glVertexAttribPointer(layout, component, GL_FLOAT, GL_FALSE, stride, (const void*)(uintptr_t)offset);
		glEnableVertexArrayAttrib(id, layout);
	}
	void VertexArray::Delete() {
		glDeleteVertexArrays(1, &id);
	}
}