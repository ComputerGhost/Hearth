#include "Engine.hpp"

namespace Core
{
	void Engine::tick()
	{
		timer.setToElapsedTime();

		while (timer.useTime()) {
			// update everything here
		}

		renderer.render(timer.getLeftoverTime());
	}
}