#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <chrono>
#include <string>

#include "../Logging.hpp"

namespace
{
	void logMessage(const char *level, const char *format, va_list args);
}

void logMessage(const char *level, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	logMessage(level, format, args);
	va_end(args);
}

namespace
{
	void logMessage(const char *level, const char *format, va_list args)
	{
		// Get the current elapsed time in seconds, with millisecond precision
		using namespace std::chrono;
		static auto start = steady_clock::now();
		double elapsed = duration_cast<milliseconds>(steady_clock::now() - start).count() / 1000.0;

		// Create the message into a buffer
		int size = vsnprintf(NULL, 0, format, args);
		auto message = std::make_unique<char[]>(size + 1);
		vsprintf(message.get(), format, args);

		// Replace any newlines with a space
		std::replace(message.get(), message.get() + size + 1, '\n', ' ');

		// Output the log entry
		assert(strlen(level) <= 7);
		printf("[%13.3f] %7s - %s\n", elapsed, level, message.get());
	}
}