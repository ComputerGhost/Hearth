#pragma once

#include <chrono>

namespace Core
{
	class EngineTimer
	{
	public:
		typedef std::chrono::steady_clock Clock;

		const std::chrono::milliseconds min_delta_time{ 8 };
		const std::chrono::milliseconds max_delta_time{ 250 };
		const std::chrono::milliseconds tick_interval{ 50 };

		EngineTimer();

		// Call this at the start of each game loop.
		void setToElapsedTime();

		// Uses up time. Returns false if none left to use.
		bool useTime();

		Clock::duration getLeftoverTime() const;

	private:
		Clock::time_point previous_time;
		Clock::duration leftover_time{ 0 };
	};
}