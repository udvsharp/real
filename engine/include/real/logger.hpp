// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_LOGGER
#define REAL_LOGGER

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "real/core.hpp"

// TODO: new logging!
namespace real {
	class REAL_API logger {
	public:
		static void init();

		static std::shared_ptr<spdlog::logger> &core() { return core_logger_; }
		static std::shared_ptr<spdlog::logger> &client() { return client_logger_; }
	private:
		static std::shared_ptr<spdlog::logger> core_logger_;
		static std::shared_ptr<spdlog::logger> client_logger_;
	};
}

// Core log macros
#define REAL_CORE_TRACE(...)    ::real::logger::core()->trace(__VA_ARGS__)
#define REAL_CORE_INFO(...)     ::real::logger::core()->info(__VA_ARGS__)
#define REAL_CORE_WARN(...)     ::real::logger::core()->warn(__VA_ARGS__)
#define REAL_CORE_ERROR(...)    ::real::logger::core()->error(__VA_ARGS__)
#define REAL_CORE_CRITICAL(...) ::real::logger::core()->critical(__VA_ARGS__)

// Client log macros
#define REAL_TRACE(...)         ::real::logger::client()->trace(__VA_ARGS__)
#define REAL_INFO(...)          ::real::logger::client()->info(__VA_ARGS__)
#define REAL_WARN(...)          ::real::logger::client()->warn(__VA_ARGS__)
#define REAL_ERROR(...)         ::real::logger::client()->error(__VA_ARGS__)
#define REAL_CRITICAL(...)      ::real::logger::client()->critical(__VA_ARGS__)

#endif //REAL_LOGGER
