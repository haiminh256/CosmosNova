#include <Cosmos/Core/OpenGLDebugger.h>
#include <Cosmos/Core/Log.h> // Đảm bảo include bộ nạp hàm OpenGL trước

namespace Cosmos {

    void OpenGLDebugger::EnableDebug() {
        // 1. Bật tính năng gỡ lỗi của OpenGL
        glEnable(GL_DEBUG_OUTPUT);

        // 2. Ép buộc OpenGL gọi hàm callback ngay lập tức khi xảy ra lỗi (giúp dừng Debugger chính xác dòng lỗi)
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        // 3. Đăng ký hàm callback của chúng ta với OpenGL
        glDebugMessageCallback(MessageCallback, nullptr);

        // 4. (Tùy chọn) Bộ lọc: Nhận tất cả các loại thông báo lỗi từ mọi nguồn
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

        CORE_INFO("OpenGL Debug Output has been successfully enabled!");
    }

    void __stdcall OpenGLDebugger::MessageCallback(unsigned int source, unsigned int type, unsigned int id,
        unsigned int severity, int length, const char* message,
        const void* userParam)
    {
        // Bỏ qua các thông báo thông tin thông thường không quan trọng (ID: 131185 thường là thông báo cấp phát bộ nhớ)
        if (id == 131185 || id == 131218 || id == 131204) return;

        std::string sourceStr, typeStr;

        // Phân loại nguồn phát ra lỗi
        switch (source) {
        case GL_DEBUG_SOURCE_API:             sourceStr = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "Application"; break;
        default:                              sourceStr = "Unknown"; break;
        }

        // Phân loại kiểu lỗi
        switch (type) {
        case GL_DEBUG_TYPE_ERROR:               typeStr = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Undefined Behavior"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Portability Issue"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Performance Issue"; break;
        default:                                typeStr = "Other"; break;
        }

        // In log dựa trên mức độ nghiêm trọng (Severity)
        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            // Mức độ NGUY HIỂM: Thường gây crash hoặc lỗi phần cứng đồ họa
            CORE_ERROR("[OpenGL High Error] Source: {0} | Type: {1} | ID: {2}\nMessage: {3}", sourceStr, typeStr, id, message);

            // Mẹo tối thượng: Đặt một điểm ngắt (Breakpoint) bằng code ở đây. 
            // Khi chạy F5 trong VS2026, ứng dụng sẽ dừng đúng dòng code OpenGL thô gây lỗi trong main.cpp!
            __debugbreak();
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            // Mức độ TRUNG BÌNH: Lỗi logic vẽ sai vật thể
            CORE_ERROR("[OpenGL Medium Error] Source: {0} | Type: {1} | Message: {2}", sourceStr, typeStr, message);
            break;

        case GL_DEBUG_SEVERITY_LOW:
            // Mức độ THẤP: Cảnh báo hiệu năng hoặc sai sót nhỏ
            CORE_WARN("[OpenGL Low Warning] Source: {0} | Message: {1}", sourceStr, message);
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            // Thông báo thông thường
            // CORE_TRACE("[OpenGL Info] Message: {0}", message);
            break;
        }
    }
}
