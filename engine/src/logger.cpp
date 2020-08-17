// Copyright (c) 2020 udv. All rights reserved.

#include <iostream>

#include <spdlog/sinks/rotating_file_sink.h>

#include "version/logger.hpp"

namespace vn::log {

    registry::registry() {
        default_logger_ = std::make_shared<logger>(logger("vn::log::basic", "logs/basic.txt"));
        spdlog::set_level(spdlog::level::trace);
    }

    logger::logger(std::string &&name, std::string &&file_name = "logs/basic.txt") {
        try {
            native_logger_ = spdlog::rotating_logger_mt(name, file_name, 1048576 * 5, 3, true);
        } catch (spdlog::spdlog_ex &ex) {
            std::cout << "Native logger is not initialized" << ex.what() << "\n";
        }
    }
}