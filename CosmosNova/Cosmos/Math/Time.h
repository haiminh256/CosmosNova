#include <Cosmos/EngineEnv.h>

namespace Cosmos {
	class COSMOS_API Time {
	public:
		float getDeltaTime();
	private:
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
	};
}