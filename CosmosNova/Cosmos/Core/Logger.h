#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <Cosmos/CosmosBase.h>

namespace Cosmos
{
    class Logger
    {
    public:
        static void COSMOS_API Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            return s_CoreLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}