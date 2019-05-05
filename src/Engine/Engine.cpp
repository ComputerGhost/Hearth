#include "State.hpp"
#include "Window.hpp"

#include "Engine.hpp"

namespace Hearth
{
	EnginePointer engine;

	Engine::Engine() :
		previous_time(Clock::now()),
		active_state(new State())
	{
	}

	void Engine::setState(std::unique_ptr<State> state)
	{
		active_state = std::move(state);
	}

	void Engine::run()
	{
		while (!window->shouldClose()) {

			tick();
			update();
			render();

			window->swapBuffers();
			glfwPollEvents();
		}
	}

	void Engine::tick()
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

	void Engine::update()
	{
		using namespace std::chrono;
		while (duration<double>(leftover_time) >= min_delta_time) {
			leftover_time -= tick_interval;

			double elapsed = duration<double>(tick_interval).count();
			active_state->update(elapsed);
		}
	}

	void Engine::render()
	{
		using namespace std::chrono;
		double lag = duration<double>(leftover_time).count();

		active_state->render(lag);
	}
}
