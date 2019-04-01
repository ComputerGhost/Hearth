#pragma once

#include <entt/entity/registry.hpp>
#include <memory>
#include "EngineTimer.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"

namespace Scenes { class TestScene; }

namespace Core
{
	class Engine
	{
	public:
		Engine();
		Engine(const Engine &) = delete;

		void setScene(std::unique_ptr<Scene> scene);

		void tick();

	private:

		void updateComponents(double elapsed);
		void render(double lag);

		EngineTimer timer;
		Renderer renderer;
		std::unique_ptr<Scene> active_scene;

		entt::registry registry;
	};
}