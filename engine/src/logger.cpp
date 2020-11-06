// Copyright (c) 2020 udv. All rights reserved.

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "real/logger.hpp"

namespace Real
{
	std::shared_ptr<spdlog::logger> Logger::coreLogger;
	std::shared_ptr<spdlog::logger> Logger::clientLogger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> log_sinks;
		log_sinks.emplace_back(
				Real::MakeReference<spdlog::sinks::stdout_color_sink_mt>());
		log_sinks.emplace_back(
				Real::MakeReference<spdlog::sinks::basic_file_sink_mt>("real.log", true));

		log_sinks[0]->set_pattern("%^[%T] %n: %v%$");
		log_sinks[1]->set_pattern("[%T] [%l] %n: %v");

		coreLogger = Real::MakeReference<spdlog::logger>("REAL", begin(log_sinks),
				end(log_sinks));
		spdlog::register_logger(coreLogger);
		coreLogger->set_level(spdlog::level::trace);
		coreLogger->flush_on(spdlog::level::trace);

		clientLogger = Real::MakeReference<spdlog::logger>("APP", begin(log_sinks),
				end(log_sinks));
		spdlog::register_logger(clientLogger);
		clientLogger->set_level(spdlog::level::trace);
		clientLogger->flush_on(spdlog::level::trace);
	}
}