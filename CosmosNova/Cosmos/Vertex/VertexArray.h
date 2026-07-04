#pragma once
#include <Cosmos/EngineEnv.h>

namespace Cosmos {
	class COSMOS_API VertexArray {
	public:
		VertexArray();
		void Bind();
		void VertexAttribPointer(unsigned int layout, unsigned int component, GLsizei stride, unsigned int offset);
		void Delete();
	private:
		unsigned int id;
	};
}