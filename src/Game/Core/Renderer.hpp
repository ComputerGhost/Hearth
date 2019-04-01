#pragma once

namespace Core
{
	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(const Renderer &) = delete;

		void render(double lag);

	};
}