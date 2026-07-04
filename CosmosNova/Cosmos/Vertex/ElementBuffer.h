#pragma once
#include <Cosmos/EngineEnv.h>

namespace Cosmos {
	class COSMOS_API ElementBuffer {
	public:
		ElementBuffer();
		void LoadData(const void* data, GLsizeiptr size);
		void Bind();
		void Delete();
	private:
		unsigned int id;
	};
}