#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// global logger to make our lives easier
// TODO: make threadsafe
std::shared_ptr<spdlog::logger> logger;

struct JsonLogger {
    std::shared_ptr<spdlog::logger> logger;
    JsonLogger(const std::string& logfilePath = "log.json") {
        std::remove(logfilePath.c_str());

        spdlog::filename_t filename = logfilePath;
        logger = spdlog::basic_logger_mt("file_logger", filename);
        logger->flush_on(spdlog::level::info);
        spdlog::flush_every(std::chrono::milliseconds(10));

        // Set up the opening brace and an array named "log"
        // we're setting a global format here but as per the docs you can set
        // this on an individual log as well spdlog::set_pattern("{\n \"log\":
        // ["); this initializes the log file with the opening brace and the
        // "log" array as above mylogger->info("");

        // We have some extra formatting on the log level %l below to keep color
        // coding when dumping json to the console and we use a full ISO 8601
        // time/date format
        std::string jsonpattern = {
            "{\"time\": \"%Y-%m-%dT%H:%M:%S.%f%z\", \"name\": \"%n\", "
            "\"level\": "
            "\"%^%l%$\", \"process\": %P, \"thread\": %t, \"message\": \"%v\"}"
        };
        spdlog::set_pattern(jsonpattern);

        // logger->info("Hi boop");
        // logger->flush();
    }
};

void initLogger(const std::string& logfilePath = "log.json") {
    std::remove(logfilePath.c_str());

    spdlog::filename_t filename = logfilePath;
    logger = spdlog::basic_logger_mt("file_logger", filename);
    logger->flush_on(spdlog::level::info);
    spdlog::flush_every(std::chrono::milliseconds(10));

    // Set up the opening brace and an array named "log"
    // we're setting a global format here but as per the docs you can set this
    // on an individual log as well
    // spdlog::set_pattern("{\n \"log\": [");
    // this initializes the log file with the opening brace and the "log" array
    // as above
    // mylogger->info("");

    // We have some extra formatting on the log level %l below to keep color
    // coding when dumping json to the console and we use a full ISO 8601
    // time/date format
    std::string jsonpattern = {
        "{\"time\": \"%Y-%m-%dT%H:%M:%S.%f%z\", \"name\": \"%n\", \"level\": "
        "\"%^%l%$\", \"process\": %P, \"thread\": %t, \"message\": \"%v\"}"
    };
    spdlog::set_pattern(jsonpattern);

    // logger->info("Hi boop");
    // logger->flush();
}