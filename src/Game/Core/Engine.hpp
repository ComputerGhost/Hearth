#pragma once

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
		EngineTimer timer;
		Renderer renderer;
	};
}