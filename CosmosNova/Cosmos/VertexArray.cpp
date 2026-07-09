#include <Cosmos/Vertex/VertexArray.h>
#include <Cosmos/Core/Log.h>

namespace Cosmos {
	VertexArray::VertexArray() {
		glGenVertexArrays(1, &id);
	}
	VertexArray::VertexArray(VertexArray&& other) noexcept
	{
		id = other.id;
		other.id = 0;
	}
	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			id = other.id;
			other.id = 0;
		}

		return *this;
	}
	void VertexArray::Bind() {
		glBindVertexArray(id);
	}
	void VertexArray::VertexAttribPointer(unsigned int layout, unsigned int component, GLsizei stride, unsigned int offset) {
		glVertexAttribPointer(layout, component, GL_FLOAT, GL_FALSE, stride, (const void*)(uintptr_t)offset);
		glEnableVertexArrayAttrib(id, layout);
	}
	void VertexArray::Delete() {
		if (id != 0)
		{
			glDeleteVertexArrays(1, &id);
			id = 0;
		}
	}
}