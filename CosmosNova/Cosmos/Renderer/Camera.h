<<<<<<< HEAD
#include <Cosmos/CosmosBase.h>
=======
#include <Cosmos/EngineEnv.h>
>>>>>>> origin
#include <Cosmos/Shader/Shader.h>

namespace Cosmos {
	class Camera {
	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -0.1);
		glm::vec3 Up = glm::vec3(0.0f, 0.1f, 0.0f);

		double lastMouseX = 0.0;
		double lastMouseY = 0.0;
		bool firstClick = true;

		bool mouseLocked = true;
		bool escPressed = false;
		float width, height;

		float speed = 1.0f;
		float sensitivity = 100.0f;

		COSMOS_API Camera(float width, float height, glm::vec3 Position);
		void COSMOS_API Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
		void COSMOS_API HandleInputs(GLFWwindow* window, float deltaTime);
	};
}