#pragma once
#include <Cosmos/CosmosBase.h>

namespace Cosmos {
	class COSMOS_API ElementBuffer {
	public:
		ElementBuffer();
		ElementBuffer(const ElementBuffer&) = delete;
		ElementBuffer& operator=(const ElementBuffer&) = delete;

		ElementBuffer(ElementBuffer&& other) noexcept;
		ElementBuffer& operator=(ElementBuffer&& other) noexcept;
		void LoadData(const void* data, GLsizeiptr size);
		void Bind();
		void Delete();
	private:
		unsigned int id;
	};
}