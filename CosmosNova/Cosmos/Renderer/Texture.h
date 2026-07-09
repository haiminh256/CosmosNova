#pragma once
#include <Cosmos/Core/Engine.h>

namespace Cosmos {
	class Texture {
	public:
		COSMOS_API Texture();

		// MỞ LẠI COPY VÀ MOVE MẶC ĐỊNH
		COSMOS_API Texture(const Texture&) = default;
		COSMOS_API Texture& operator=(const Texture&) = default;
		COSMOS_API Texture(Texture&&) noexcept = default;
		COSMOS_API Texture& operator=(Texture&&) noexcept = default;

		COSMOS_API bool Load(const std::string& filePath, bool flip);
		COSMOS_API void Bind(unsigned int unit) const;
		COSMOS_API void Delete();
		COSMOS_API void setType(std::string type);
		COSMOS_API void setPath(std::string path);
		COSMOS_API bool LoadFromMemory(const unsigned char* buffer, int bufferSize, bool flip);

		std::string Type;
		std::string Path;
	private:
		unsigned int id = 0;

		int width = 0;
		int height = 0;
		int channels = 0;
	};
}