#include <cassert>
#include <map>

#include "Monitor.hpp"

namespace
{
	std::map<GLFWmonitor *, glm::ivec2> nativeResolutions;
}

namespace Hearth
{
	void Monitor::initializeMonitors()
	{
		for (auto monitor : getMonitors()) {
			auto pointer = monitor.monitor;
			auto mode = glfwGetVideoMode(pointer);
			nativeResolutions[pointer] = glm::ivec2(mode->width, mode->height);
		}
	}

	// When a monitor is added or removed, we can update our map.
	void Monitor::onGlfwEvent(GLFWmonitor *monitor, int event)
	{
		if (event == GLFW_CONNECTED) {
			auto mode = glfwGetVideoMode(monitor);
			nativeResolutions[monitor] = glm::ivec2(mode->width, mode->height);
		}
		else {
			assert(event == GLFW_DISCONNECTED);
			nativeResolutions.erase(monitor);
		}
	}

	Monitor::Monitor(GLFWmonitor *monitor) :
		monitor(monitor)
	{}

	glm::ivec2 Monitor::getPosition() const
	{
		glm::ivec2 position;
		glfwGetMonitorPos(monitor, &position.x, &position.y);
		return position;
	}

	glm::ivec2 Monitor::getSize() const
	{
		auto mode = glfwGetVideoMode(monitor);
		return glm::ivec2(mode->width, mode->height);
	}

	glm::ivec4 Monitor::getBounds() const
	{
		auto position = getPosition();
		auto size = getSize();
		return glm::ivec4(position.x, position.y, size.x, size.y);
	}

	glm::ivec2 Monitor::getNativeResolution() const
	{
		auto resolution = nativeResolutions.find(monitor);
		if (resolution == nativeResolutions.end())
			throw std::runtime_error("Could not get monitor native resolution.");
		return resolution->second;
	}

	std::vector<Monitor> getMonitors()
	{
		int count;
		auto monitors = glfwGetMonitors(&count);
		return std::vector<Monitor>(monitors, monitors + count);
	}
}