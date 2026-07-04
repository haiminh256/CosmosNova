#include <Cosmos/Math/Time.h>

namespace Cosmos {
	float Time::getDeltaTime() {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		return deltaTime;
	}
}