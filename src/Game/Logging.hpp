#pragma once

// Don't use this directly.
void logMessage(const char *level, const char *format, ...);

// Info the developer may want to know
#define LOG_DEBUG(...) logMessage("DEBUG", __VA_ARGS__)
#ifdef NDEBUG
#undef LOG_DEBUG
#define LOG_DEBUG(...)
#endif

// Provides context in the logs
#define LOG_INFO(...) logMessage("INFO", __VA_ARGS__)

// Needs fixed but we can work with it
#define LOG_NOTICE(...) logMessage("NOTICE", __VA_ARGS__)

// Recovered from problem with possible side effects
#define LOG_WARNING(...) logMessage("WARNING", __VA_ARGS__)

// Task cannot complete due to a problem
#define LOG_ERROR(...) logMessage("ERROR", __VA_ARGS__)
