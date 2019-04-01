#include "Engine.hpp"

namespace Core
{
	Engine::Engine() :
		active_scene(new Scene())
	{
		// We just need a scene so we don't have to check if it's set.
		// So we'll set it to a scene that does nothing by default.
	}

	void Engine::setScene(std::unique_ptr<Scene> scene)
	{
		active_scene->onDetach();

		active_scene = std::move(scene);
		active_scene->onAttach();
	}

	void Engine::tick()
	{
		timer.setToElapsedTime();

		while (timer.useTime()) {
			std::chrono::duration<double> elapsed = timer.tick_interval;
			active_scene->onUpdate(elapsed.count());
			updateComponents(elapsed.count());
		}

		std::chrono::duration<double> lag = timer.getLeftoverTime();
		render(lag.count());
	}

	void Engine::updateComponents(double elapsed)
	{
		// We'll call the components directly here.
	}

	void Engine::render(double lag)
	{
		renderer.render(lag);
	}
}