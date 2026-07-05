#pragma once

#include <Cosmos/EngineEnv.h>

namespace Cosmos
{
	class Transform
	{
	public:
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

	public:
		Transform() = default;

		glm::mat4 COSMOS_API GetModelMatrix() const;
	};
}