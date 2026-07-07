#pragma once
#include <Cosmos/CosmosBase.h>

namespace Cosmos {
    class COSMOS_API OpenGLDebugger {
    public:
        // Kích hoạt hệ thống bắt lỗi tự động của OpenGL
        static void EnableDebug();

    private:
        // Hàm Callback chuẩn mã nguồn OpenGL sẽ tự động gọi khi có lỗi
        static void __stdcall MessageCallback(unsigned int source, unsigned int type, unsigned int id,
            unsigned int severity, int length, const char* message,
            const void* userParam);
    };
}
