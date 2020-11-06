// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_LOGGER
#define REAL_LOGGER

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "real/core.hpp"

// TODO: new logging!
namespace Real
{
	class REAL_API Logger
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& Core()
		{ return coreLogger; }
		static std::shared_ptr<spdlog::logger>& Client()
		{ return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

// Core log macros
#define REAL_CORE_TRACE(...)    ::Real::Logger::Core()->trace(__VA_ARGS__)
#define REAL_CORE_INFO(...)     ::Real::Logger::Core()->info(__VA_ARGS__)
#define REAL_CORE_WARN(...)     ::real::Logger::Core()->warn(__VA_ARGS__)
#define REAL_CORE_ERROR(...)    ::Real::Logger::Core()->error(__VA_ARGS__)
#define REAL_CORE_CRITICAL(...) ::real::Logger::Core()->critical(__VA_ARGS__)

// Client log macros
#define REAL_TRACE(...)         ::Real::Logger::Client()->trace(__VA_ARGS__)
#define REAL_INFO(...)          ::real::Logger::Client()->info(__VA_ARGS__)
#define REAL_WARN(...)          ::real::Logger::Client()->warn(__VA_ARGS__)
#define REAL_ERROR(...)         ::real::Logger::Client()->error(__VA_ARGS__)
#define REAL_CRITICAL(...)      ::real::Logger::Client()->critical(__VA_ARGS__)

#endif //REAL_LOGGER
