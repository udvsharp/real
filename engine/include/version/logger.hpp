// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_LOGGER
#define VN_LOGGER

#include <memory>
#include <utility>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "version/core.hpp"

// TODO: new logging!
namespace vn {
	class VN_API logger
	{
	public:
		static void init();

		static std::shared_ptr<spdlog::logger>& core() { return core_logger_; }
		static std::shared_ptr<spdlog::logger>& client() { return client_logger_; }
	private:
		static std::shared_ptr<spdlog::logger> core_logger_;
		static std::shared_ptr<spdlog::logger> client_logger_;
	};
}

// Core log macros
#define VN_CORE_TRACE(...)    ::vn::logger::core()->trace(__VA_ARGS__)
#define VN_CORE_INFO(...)     ::vn::logger::core()->info(__VA_ARGS__)
#define VN_CORE_WARN(...)     ::vn::logger::core()->warn(__VA_ARGS__)
#define VN_CORE_ERROR(...)    ::vn::logger::core()->error(__VA_ARGS__)
#define VN_CORE_CRITICAL(...) ::vn::logger::core()->critical(__VA_ARGS__)

// Client log macros
#define VN_TRACE(...)         ::vn::logger::client()->trace(__VA_ARGS__)
#define VN_INFO(...)          ::vn::logger::client()->info(__VA_ARGS__)
#define VN_WARN(...)          ::vn::logger::client()->warn(__VA_ARGS__)
#define VN_ERROR(...)         ::vn::logger::client()->error(__VA_ARGS__)
#define VN_CRITICAL(...)      ::vn::logger::client()->critical(__VA_ARGS__)

#endif //VN_LOGGER
