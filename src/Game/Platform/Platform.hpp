#pragma once

#include "Geometry.hpp"
#include "Monitor.hpp"
#include "Window.hpp"

namespace Platform
{
	// Exactly one of these should be created and kept in scope.
	// It must be created before anything else in Platform is used.
	class Platform
	{
	public:
		Platform(const char *title, Size size);
		~Platform();
	};

	// Internal code
	class PlatformInternals
	{
		PlatformInternals() = delete;

		friend class Monitor;

		static Size getNativeResolution(GLFWmonitor *monitor);
	};
}