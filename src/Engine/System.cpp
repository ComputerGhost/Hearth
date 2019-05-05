#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "Logging.hpp"
#include "Monitor.hpp"
#include "Window.hpp"

#include "System.hpp"


namespace Hearth
{
	void System::onGlfwError(int code, const char *description)
	{
		LOG_NOTICE("GLFW logged an error: %d - %s", code, description);
	}

	System::System(const char *title, glm::ivec2 size)
	{
		if (glfwInit() == GLFW_FALSE)
			throw std::runtime_error("Could not initialize GLFW.");

		glfwSetErrorCallback(onGlfwError);

		Monitor::initializeMonitors();
		glfwSetMonitorCallback(Monitor::onGlfwEvent);

		// And now the window
		window.reset(new Window(title, size));

		// Now we have a context, initialize OpenGL.
		if (!gladLoadGL())
			throw std::runtime_error("Unable to initialize OpenGL context.");
	}

	System::~System()
	{
		window.reset();
		glfwTerminate();
	}
}