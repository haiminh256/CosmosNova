#include <Cosmos/Renderer/Camera.h>
#include <Cosmos/Math/Time.h>

namespace Cosmos {
	Camera::Camera(float width, float height, glm::vec3 Position) {
		Camera::width = width;
		Camera::height = height;
		Camera::Position = Position;
	}
	void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = glm::lookAt(Position, Position + Orientation, Up);
		projection = glm::perspective(glm::radians(FOVdeg), width / height, nearPlane, farPlane);

		glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
	}
    void Camera::HandleInputs(GLFWwindow* window, float deltaTime)
    {
        // Toggle mouse capture
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            firstClick = true;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            if (firstClick)
            {
                glfwSetCursorPos(window, width / 2.0, height / 2.0);
                firstClick = false;
            }
        }

        // Sprint
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            speed = 6.0f;
        else
            speed = 3.0f;

        // Movement
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            Position += Orientation * speed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            Position -= Orientation * speed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            Position -= glm::normalize(glm::cross(Orientation, Up)) * speed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            Position += glm::normalize(glm::cross(Orientation, Up)) * speed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            Position += Up * speed * deltaTime;

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            Position -= Up * speed * deltaTime;

        // Only rotate when cursor is captured
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        {
            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);

            float rotX = sensitivity *
                (float)(mouseY - height / 2.0) / height;

            float rotY = sensitivity *
                (float)(mouseX - width / 2.0) / width;

            glm::vec3 newOrientation =
                glm::rotate(
                    Orientation,
                    glm::radians(-rotX),
                    glm::normalize(glm::cross(Orientation, Up)));

            if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f))
                <= glm::radians(85.0f))
            {
                Orientation = newOrientation;
            }

            Orientation =
                glm::rotate(
                    Orientation,
                    glm::radians(-rotY),
                    Up);

            glfwSetCursorPos(window, width / 2.0, height / 2.0);
        }
    }
}