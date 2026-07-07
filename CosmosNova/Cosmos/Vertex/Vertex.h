#pragma once
#include <Cosmos/CosmosBase.h>

namespace Cosmos {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};
}