#pragma once

#include <Cosmos/Core/Logger.h>

#define CORE_TRACE(...)    ::Cosmos::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)     ::Cosmos::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)     ::Cosmos::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)    ::Cosmos::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Cosmos::Logger::GetCoreLogger()->critical(__VA_ARGS__)