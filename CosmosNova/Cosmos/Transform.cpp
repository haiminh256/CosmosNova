#include <Cosmos/Renderer/Transform.h>

namespace Cosmos
{
	glm::mat4 Transform::GetModelMatrix() const
	{
		glm::mat4 model = glm::mat4(1.0f);

		// Translation
		model = glm::translate(model, Position);

		// Rotation (X -> Y -> Z)
		model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// Scale
		model = glm::scale(model, Scale);

		return model;
	}
}