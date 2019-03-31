#include "Engine.hpp"

namespace Core
{
	void Engine::tick()
	{
		timer.setToElapsedTime();

		while (timer.useTime())
			updateComponents();

		render();
	}

	void Engine::updateComponents()
	{
		// We'll call the components directly here.
	}

	void Engine::render()
	{
		renderer.render(timer.getLeftoverTime());
	}
}