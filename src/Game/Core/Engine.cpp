#include "Engine.hpp"

namespace Core
{
	void Engine::tick()
	{
		timer.setToElapsedTime();

		while (timer.useTime()) {
			// update everything here
		}

		// render stuff here
		// use timer.getLeftoverTime() to offset items
	}
}