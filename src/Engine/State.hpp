#pragma once

namespace Hearth
{
	class State
	{
	public:
		State() = default;
		State(const State &) = delete;
		virtual ~State() = default;

		virtual void update(double elapsed) {}
		virtual void render(double lag) {}
	};
}
