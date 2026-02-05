#pragma once

#include "logger.hpp"

#define LOG_DEBUG(...) Logger::get()->debug(__VA_ARGS__)
#define LOG_INFO(...)  Logger::get()->info(__VA_ARGS__)
#define LOG_WARN(...)  Logger::get()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Logger::get()->critical(__VA_ARGS__)