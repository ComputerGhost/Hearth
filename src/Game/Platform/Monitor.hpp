#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include "Geometry.hpp"

namespace Platform
{
	class Monitor
	{
		friend class Window;
		friend class Platform;

	public:
		Monitor() = delete;
		Monitor(const Monitor &) = default;
		Monitor(GLFWmonitor *glfwMonitor);

		Position getPosition() const;
		Size getSize() const;
		Rectangle getBounds() const;

		Size getNativeResolution() const;

	private:
		GLFWmonitor *monitor;
	};

	std::vector<Monitor> getMonitors();
}