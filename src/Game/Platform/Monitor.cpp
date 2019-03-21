#include "Platform.hpp"

#include "Monitor.hpp"

namespace Platform
{
	Monitor::Monitor(GLFWmonitor *monitor) :
		monitor(monitor)
	{}

	Position Monitor::getPosition() const
	{
		Position position;
		glfwGetMonitorPos(monitor, &position.x, &position.y);
		return position;
	}

	Size Monitor::getSize() const
	{
		auto mode = glfwGetVideoMode(monitor);
		return Size(mode->width, mode->height);
	}

	Rectangle Monitor::getBounds() const
	{
		return Rectangle(getPosition(), getSize());
	}

	Size Monitor::getNativeResolution() const
	{
		return PlatformInternals::getNativeResolution(monitor);
	}

	std::vector<Monitor> getMonitors()
	{
		int count;
		auto monitors = glfwGetMonitors(&count);
		return std::vector<Monitor>(monitors, monitors + count);
	}
}