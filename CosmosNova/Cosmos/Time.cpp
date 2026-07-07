#include <Cosmos/Math/Time.h>

namespace Cosmos {
	float Time::getDeltaTime() {
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		return deltaTime;
	}
}