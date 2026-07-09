#pragma once
#include <Cosmos/CosmosBase.h>

namespace Cosmos {
	class COSMOS_API VertexArray {
	public:
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray(VertexArray&& other) noexcept;
		VertexArray& operator=(VertexArray&& other) noexcept;

		void Bind();
		void VertexAttribPointer(unsigned int layout, unsigned int component, GLsizei stride, unsigned int offset);
		void Delete();
	private:
		unsigned int id;
	};
}