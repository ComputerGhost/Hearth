#pragma once

namespace Hearth
{
	// Exactly one of these should be created and kept in scope.
	// It must be created before anything else in the engine is used.
	class System
	{
		static void onGlfwError(int code, const char *description);

	public:
		System(const char *title, glm::ivec2 size);
		~System();
	};
}