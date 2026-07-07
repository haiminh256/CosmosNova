#pragma once
#include <Cosmos/Core/Engine.h>

namespace Cosmos {
	class Texture {
	public:
		COSMOS_API Texture();
		COSMOS_API bool Load(const std::string& filePath, bool flip);
		COSMOS_API void Bind(unsigned int unit) const;
		COSMOS_API void Delete();
		COSMOS_API void setType(std::string Type);
		COSMOS_API void setPath(std::string Path);
		std::string Type;
		std::string Path;
		unsigned int id = 0;
	private:

		int width = 0;
		int height = 0;
		int channels = 0;
	};
}