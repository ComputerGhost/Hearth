#pragma once

#include <entt/entity/registry.hpp>
#include "EngineTimer.hpp"
#include "Renderer.hpp"

namespace Core
{
	class Engine
	{
	public:
		Engine() = default;
		Engine(const Engine &) = delete;

		void tick();

	private:

		void updateComponents();
		void render();

		EngineTimer timer;
		Renderer renderer;

		entt::registry registry;
	};
}