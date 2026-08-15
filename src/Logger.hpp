#ifndef MINESWEEPER_LOGGER_HPP
#define MINESWEEPER_LOGGER_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <vector>
#include <memory>

namespace Log {
    inline void init() {
        try {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

            std::vector<spdlog::sink_ptr> sinks { console_sink };
            auto logger = std::make_shared<spdlog::logger>("main", sinks.begin(), sinks.end());

#ifdef NDEBUG
            logger->set_level(spdlog::level::info);
#else
            logger->set_level(spdlog::level::trace);
#endif

            spdlog::set_default_logger(logger);
            spdlog::flush_on(spdlog::level::warn);

            spdlog::info("Logging system initialized successfully");
        } catch (const spdlog::spdlog_ex& ex) {
            printf("Log init failed: %s\n", ex.what());
        }
    }
}

#endif // MINESWEEPER_LOGGER_HPP