#include <stdexcept>
#include "Monitor.hpp"

#include "Window.hpp"

namespace Hearth
{
	WindowPointer window{ nullptr };

	Window::Window(const char *title, glm::ivec2 size) :
		window_size(size)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
		if (!window)
			throw std::runtime_error("Error creating GLFW Window.");

		glfwSetWindowUserPointer(window, this);

		// Display callbacks
		//glfwSetWindowSizeCallback(window, WindowInternals::onWindowSize);
		//glfwSetFramebufferSizeCallback(window, onFramebufferSize);

		//// Input callbacks
		//glfwSetCharCallback(window, onChar);
		//glfwSetCursorPosCallback(window, onCursorPos);
		//glfwSetKeyCallback(window, onKey);
		//glfwSetMouseButtonCallback(window, onMouseButton);
		//glfwSetScrollCallback(window, onScroll);
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	void Window::setMinimumSize(glm::ivec2 size)
	{
		glfwSetWindowSizeLimits(window, size.x, size.y, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}

	glm::ivec2 Window::getWindowSize()
	{
		if (!isFullscreen())
			glfwGetWindowSize(window, &window_size.x, &window_size.y);
		return window_size;
	}

	void Window::setWindowSize(glm::ivec2 size)
	{
		window_size = size;
		if (!isFullscreen())
			glfwSetWindowSize(window, size.x, size.y);
	}

	Monitor Window::getMonitor() const
	{
		if (isFullscreen())
			return glfwGetWindowMonitor(window);

		// If not fullscreen, get the monitor the top-left is on.
		for (auto monitor : getMonitors()) {
			auto bounds = monitor.getBounds();
			if (bounds.x < window_position.x) continue;
			if (bounds.y < window_position.y) continue;
			if (bounds.x > bounds.x + window_position.x) continue;
			if (bounds.y > bounds.y + window_position.y) continue;
			return monitor;
		}

		throw std::runtime_error("Unable to get the window's monitor.");
	}

	bool Window::isFullscreen() const
	{
		if (glfwGetWindowMonitor(window) == NULL)
			return false;
		return true;
	}

	glm::ivec2 Window::getFullscreenSize() const
	{
		return fullscreen_size;
	}

	void Window::setFullscreenSize(glm::ivec2 size)
	{
		fullscreen_size = size;

		if (isFullscreen()) {
			if (size.x < 0 || size.y < 0) {
				auto monitor = getMonitor();
				size = monitor.getNativeResolution();
			}
			glfwSetWindowSize(window, size.x, size.y);
		}
	}

	void Window::setFullscreen(bool flag)
	{
		// If no change, ignore
		if (isFullscreen() == flag)
			return;

		// Change to fullscreen if true
		if (flag) {
			auto monitor = getMonitor();

			// If the size is (-1, -1), then use the native resolution.
			glm::ivec2 size = fullscreen_size;
			if (size.x < 0 || size.y < 0)
				size = monitor.getNativeResolution();

			glfwSetWindowMonitor(window, 
				monitor.monitor, 0, 0, size.x, size.y, GLFW_DONT_CARE);
		}

		// Change to window mode by setting the monitor to NULL.
		else {
			glfwSetWindowMonitor(window, 
				NULL, 0, 0, window_size.x, window_size.y, GLFW_DONT_CARE);
		}
	}

	glm::ivec2 Window::getFramebufferSize() const
	{
		glm::ivec2 size;
		glfwGetFramebufferSize(window, &size.x, &size.y);
		return size;
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::makeCurrent()
	{
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(window);
	}
}
