#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <HearthLib/Logging.hpp>
#include <cassert>
#include <map>

#include "Monitor.hpp"

#include "Platform.hpp"

namespace Platform
{
	namespace
	{
		void onGlfwError(int code, const char *description)
		{
			LOG_NOTICE("GLFW logged an error: %d - %s", code, description);
		}

		// We can't query this from GLFW, so we keep track of it here.
		std::map<GLFWmonitor*, Size> nativeResolutions;

		// When a monitor is added or removed, we can update our map.
		void onMonitorEvent(GLFWmonitor *monitor, int event)
		{
			if (event == GLFW_CONNECTED) {
				auto mode = glfwGetVideoMode(monitor);
				nativeResolutions[monitor] = Size(mode->width, mode->height);
			}
			else {
				assert(event == GLFW_DISCONNECTED);
				nativeResolutions.erase(monitor);
			}
		}
	}

	Platform::Platform(const char *title, Size size)
	{
		if (glfwInit() == GLFW_FALSE)
			throw std::runtime_error("Could not initialize GLFW.");

		glfwSetErrorCallback(onGlfwError);
		glfwSetMonitorCallback(onMonitorEvent);

		// Initialize our native resolutions map
		for (auto monitor : getMonitors()) {
			auto pointer = monitor.monitor;
			auto mode = glfwGetVideoMode(pointer);
			nativeResolutions[pointer] = Size(mode->width, mode->height);
		}

		// And now the window
		window.reset(new Window(title, size));
	}

	Platform::~Platform()
	{
		window.reset();
		glfwTerminate();
	}

	Size PlatformInternals::getNativeResolution(GLFWmonitor *monitor)
	{
		auto resolution = nativeResolutions.find(monitor);
		if (resolution == nativeResolutions.end())
			throw std::runtime_error("Could not get monitor native resolution.");
		return resolution->second;
	}
}