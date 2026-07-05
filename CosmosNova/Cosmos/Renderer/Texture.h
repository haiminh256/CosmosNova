#include <Cosmos/Engine.h>

namespace Cosmos {
	class COSMOS_API Texture {
	public:
		Texture();
		void Load(const std::string& filePath, bool flip);
		void Bind(unsigned int unit) const;
		void Delete();
	private:
		unsigned int id = 0;
		int width = 0;
		int height = 0;
		int channels = 0;
	};
}