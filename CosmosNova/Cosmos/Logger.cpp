#include <Cosmos/Core/Logger.h>

namespace Cosmos
{
    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;

    void Logger::Init()
    {
        spdlog::set_pattern(
            "%^[%H:%M:%S] [%!:%#] [%n] [Thread:%t] %v%$"
        );

        s_CoreLogger =
            spdlog::stdout_color_mt("Cosmos");

        s_CoreLogger->set_level(
            spdlog::level::trace
        );

        s_CoreLogger->info(
            "Logger::Init() success"
        );
    }
}