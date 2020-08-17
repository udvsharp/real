// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_LOGGER
#define VN_LOGGER

#include <memory>
#include <utility>

#include <spdlog/spdlog.h>

#include "version/core.hpp"

// TODO: new logging!
namespace vn::log {

	class VN_API logger {
			friend class registry;

			private:
			std::shared_ptr<spdlog::logger> native_logger_;
			public:
			logger() = delete;

			logger(std::string &&name, std::string &&file_name);

			template<typename T, typename ... Args>
			constexpr void trace(T &&msg, Args &&...args) {
				native_logger_->trace(std::forward<T>(msg), std::forward<Args>(args)...);
			}

			template<typename T, typename ... Args>
			constexpr void info(T &&msg, Args &&...args) {
				native_logger_->info(std::forward<T>(msg), std::forward<Args>(args)...);
			}

			template<typename T, typename ... Args>
			constexpr void warn(T &&msg, Args &&...args) {
				native_logger_->warn(std::forward<T>(msg), std::forward<Args>(args)...);
			}

			template<typename T, typename ... Args>
			constexpr void error(T &&msg, Args &&...args) {
				native_logger_->error(std::forward<T>(msg), std::forward<Args>(args)...);
			}

			template<typename T, typename ... Args>
			constexpr void critical(T &&msg, Args &&...args) {
				native_logger_->critical(std::forward<T>(msg), std::forward<Args>(args)...);
			}
	};

	class VN_API registry {
			friend inline std::shared_ptr<logger> get_default_logger();
			private:
			std::shared_ptr<logger> default_logger_;
			public:
			registry();

			static registry &instance() {
				static registry s_instance{};

				return s_instance;
			}
	};

	inline std::shared_ptr<logger> get_default_logger() {
		return registry::instance().default_logger_;
	}

	template<typename T, typename ... Args>
	constexpr void trace(T &&msg, Args &&...args) {
		get_default_logger()->trace(std::forward<T>(msg), std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr void info(T &&msg, Args &&...args) {
		get_default_logger()->info(std::forward<T>(msg), std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr void warn(T &&msg, Args &&...args) {
		get_default_logger()->warn(std::forward<T>(msg), std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr void error(T &&msg, Args &&...args) {
		get_default_logger()->error(std::forward<T>(msg), std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr void critical(T &&msg, Args &&...args) {
		get_default_logger()->critical(std::forward<T>(msg), std::forward<Args>(args)...);
	}
}

#endif //VN_LOGGER
