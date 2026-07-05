#include <Cosmos/Shader/Shader.h>
#include <Cosmos/Core/Log.h>
#include <Cosmos/EngineEnv.h>

namespace Cosmos {

    std::string Shader::LoadShaderSource(const char* filepath) {
        std::ifstream file(filepath);
        if (!file) {
            CORE_ERROR("Failed to open shader file: {0}", filepath);
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    unsigned int Shader::CompileShader(const char* vertexPath, const char* fragmentPath) {
        int success;
        char infoLog[512];

        // 1. Biên dịch Vertex Shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        std::string vertexCode = LoadShaderSource(vertexPath);
        const char* vertexSourcePtr = vertexCode.c_str();

        glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
        glCompileShader(vertexShader);

        // Kiểm tra lỗi biên dịch Vertex Shader
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            CORE_ERROR("Vertex Shader Compilation Failed ({0}):\n{1}", vertexPath, infoLog);
        }

        // 2. Biên dịch Fragment Shader
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        std::string fragmentCode = LoadShaderSource(fragmentPath);
        const char* fragmentSourcePtr = fragmentCode.c_str();

        glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
        glCompileShader(fragmentShader);

        // Kiểm tra lỗi biên dịch Fragment Shader
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            CORE_ERROR("Fragment Shader Compilation Failed ({0}):\n{1}", fragmentPath, infoLog);
        }
        CORE_INFO("Shader::CompileShader() success");

        // Tạo Shader Program và liên kết ngay sau khi compile thành công
        CreateShaderProgram();

        // Trả về ID của chương trình shader theo đúng khai báo trong file .h
        return shaderProgram;
    }

    void Shader::CreateShaderProgram() {
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Kiểm tra lỗi Link chương trình tổng
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            CORE_ERROR("Shader Program Linking Failed:\n{0}", infoLog);
        }

        // Sau khi link xong, có thể dọn dẹp các shader thành phần để nhẹ bộ nhớ ẩn
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::UseShader() {
        glUseProgram(shaderProgram);
    }

    void Shader::DeleteShader() {
        if (shaderProgram != 0) {
            glDeleteProgram(shaderProgram);
            shaderProgram = 0;
        }
        CORE_INFO("Shader::Delete() success");
    }
    void Shader::SetInt(const char* name, int value) {
        glUniform1i(glGetUniformLocation(shaderProgram, name), value);
    }
    void Shader::SetMat4(const char* name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(
            glGetUniformLocation(shaderProgram, name),
            1,
            GL_FALSE,
            glm::value_ptr(matrix)
        );
    }
}
