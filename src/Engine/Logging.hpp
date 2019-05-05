#pragma once

namespace Hearth
{
	// Don't use this directly.
	void logMessage(const char *level, const char *format, ...);
}

// Info the developer may want to know
#define LOG_DEBUG(...) Hearth::logMessage("DEBUG", __VA_ARGS__)
#ifdef NDEBUG
#undef LOG_DEBUG
#define LOG_DEBUG(...)
#endif

// Provides context in the logs
#define LOG_INFO(...) Hearth::logMessage("INFO", __VA_ARGS__)

// Needs fixed but we can work with it
#define LOG_NOTICE(...) Hearth::logMessage("NOTICE", __VA_ARGS__)

// Recovered from problem with possible side effects
#define LOG_WARNING(...) Hearth::logMessage("WARNING", __VA_ARGS__)

// Task cannot complete due to a problem
#define LOG_ERROR(...) Hearth::logMessage("ERROR", __VA_ARGS__)
