#pragma once

namespace Core
{
	class Engine;

	class Scene
	{
	public:
		Scene() = default;
		Scene(const Scene &) = delete;
		virtual ~Scene() = default;

		virtual void onAttach() {}
		virtual void onUpdate(double elapsed) {}
		virtual void onDetach() {}

	protected:
	};
}
