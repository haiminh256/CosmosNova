#include <Cosmos/Engine.h>
#include <Cosmos/Core/Log.h>

namespace Cosmos {
	bool Engine::Init() {
		Logger::Init();
		if (!glfwInit()) {
			CORE_ERROR("GLFW init failed");
			return false;
		}	
		CORE_INFO("Engine::Init() success");
		return true;
	}
	void Engine::CreateAppWindow(int width, int height, const char* title) {
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (window == nullptr) {
			CORE_ERROR("Engine::CreateAppWindow() failed");
		}
		CORE_INFO("Engine::CreateAppWindow() success");
	}
	void Engine::EventHandle() {
		glfwPollEvents();
	}
	void Engine::Quit() {
		CORE_INFO("Engine::Quit() success");
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	void Engine::SetWindowHint(int hint, int value) {
		glfwWindowHint(hint, value);
	}
	void Engine::ApplyWindowHint() {
		glfwMakeContextCurrent(window);
	}
	void Engine::Terminate() {
		CORE_ERROR("Engine::Terminate() executed");
		glfwTerminate();
	}
	bool Engine::ShouldClose() {
		return glfwWindowShouldClose(window);
	}
	void Engine::SwapBuffers() {
		glfwSwapBuffers(window);
	}
	GLFWwindow* Engine::getWindow() {
		return window;
	}
}