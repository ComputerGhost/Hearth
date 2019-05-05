#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <map>
#include <vector>

namespace Hearth
{
	class Monitor
	{
		friend class Window; // it needs to set its monitor
		friend class System; // it needs to tie up the events

		static void initializeMonitors();
		static void onGlfwEvent(GLFWmonitor *monitor, int event);

	public:
		Monitor() = delete;
		Monitor(const Monitor &) = default;
		Monitor(GLFWmonitor *glfwMonitor);

		glm::ivec2 getPosition() const;
		glm::ivec2 getSize() const;
		glm::ivec4 getBounds() const;

		glm::ivec2 getNativeResolution() const;

	private:
		GLFWmonitor *monitor;
	};

	std::vector<Monitor> getMonitors();
}