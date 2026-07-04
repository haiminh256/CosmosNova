#pragma once
#include <Cosmos/EngineEnv.h>

namespace Cosmos {
	class COSMOS_API VertexBuffer {
	public:
		VertexBuffer();
		void Bind();
		void LoadData(const void* data, GLsizeiptr size);
		void Delete();
	private:
		unsigned int id;
	};
}