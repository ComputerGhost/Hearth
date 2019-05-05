#pragma once

#include <memory>
#include <chrono>

#include "State.hpp"

namespace Hearth
{
	// One of these is automagically created as Hearth::engine.
	class Engine
	{
	public:
		const std::chrono::milliseconds min_delta_time{ 8 };
		const std::chrono::milliseconds max_delta_time{ 250 };
		const std::chrono::milliseconds tick_interval{ 50 };

		Engine();
		Engine(const Engine &) = delete;
		~Engine() = default;

		void setState(std::unique_ptr<State> state);
		void run();

	private:
		void tick();
		void update();
		void render();

		typedef std::chrono::steady_clock Clock;
		Clock::time_point previous_time;
		Clock::duration leftover_time{ 0 };

		std::unique_ptr<State> active_state;
	};

	// You can use the pointer but not change it.
	class EnginePointer : public std::unique_ptr<Engine>
	{
		using std::unique_ptr<Engine>::reset;
	public:
		EnginePointer() : std::unique_ptr<Engine>(new Engine) {}
	};

	// This is the pointer to the engine.
	extern EnginePointer engine;
}
