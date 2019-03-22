#include "EngineTimer.hpp"

namespace Core
{
	EngineTimer::EngineTimer() :
		previous_time(Clock::now())
	{
	}

	void EngineTimer::setToElapsedTime()
	{
		auto current_time = Clock::now();
		auto elapsed = current_time - previous_time;

		// If we're too fast, return immediately; if we're too slow, lag a little.
		if (elapsed < min_delta_time)
			return;
		if (elapsed > max_delta_time)
			elapsed = max_delta_time;

		leftover_time += elapsed;
		previous_time = current_time;
	}

	bool EngineTimer::useTime()
	{
		using namespace std::chrono;
		if (duration<double>(leftover_time) < min_delta_time)
			return false;
		leftover_time -= tick_interval;
		return true;
	}

	double EngineTimer::getLeftoverTime() const
	{
		using namespace std::chrono;
		return duration_cast<milliseconds>(leftover_time).count() * 0.001;
	}
}
