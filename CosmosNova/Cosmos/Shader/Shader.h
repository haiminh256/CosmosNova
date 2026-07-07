#pragma once
#include <Cosmos/CosmosBase.h>

namespace Cosmos {
	class COSMOS_API Shader {
	public:
		void CreateShaderProgram();
		void UseShader();
		void DeleteShader();	
		void SetInt(const char* name, int value);
		void SetMat4(const char* name, const glm::mat4& matrix);
		unsigned int CompileShader(const char* vertexPath, const char* fragmentPath);
		unsigned int shaderProgram;
	private:
		std::string LoadShaderSource(const char* filepath);
		unsigned int vertexShader;
		unsigned int fragmentShader;
	};
}