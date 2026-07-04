#include <Cosmos/Renderer/Renderer.h>
#include <Cosmos/EngineEnv.h>
#include <Cosmos/Core/Log.h>

namespace Cosmos {

    bool Renderer::Init() {
        if (!gladLoadGL(glfwGetProcAddress)) {
            CORE_ERROR("Renderer::Init() failed");
            return false;
        }
        CORE_INFO("Renderer::Init() success");
    }

    void Renderer::SetViewport(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }

    void Renderer::SetClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    void Renderer::Clear() {
        // Xóa cả bộ đệm màu sắc lẫn bộ đệm chiều sâu
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Draw(unsigned int offset, unsigned int indexCount) {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const void*)(uintptr_t)offset);
    }

    void Renderer::DrawArrays(unsigned int offset, unsigned int vertexCount) {
        glDrawArrays(GL_TRIANGLES, offset, vertexCount);
    }
}
