#include "Window.hpp"

namespace Platform
{
	Window::Window(const char *title, Size size) :
		window_size(size)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(size.width, size.height, title, NULL, NULL);
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

	void Window::setMinimumSize(Size size)
	{
		glfwSetWindowSizeLimits(window,
			size.width, size.height,
			GLFW_DONT_CARE, GLFW_DONT_CARE);
	}

	Size Window::getWindowSize()
	{
		if (!isFullscreen())
			glfwGetWindowSize(window, &window_size.width, &window_size.height);
		return window_size;
	}

	void Window::setWindowSize(Size size)
	{
		window_size = size;
		if (!isFullscreen())
			glfwSetWindowSize(window, size.width, size.height);
	}

	Monitor Window::getMonitor() const
	{
		if (isFullscreen())
			return glfwGetWindowMonitor(window);

		// If not fullscreen, get the monitor the top-left is on.
		for (auto monitor : getMonitors()) {
			if (doesIntersect(monitor.getBounds(), window_position))
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

	void Window::setFullscreenSize(Size size)
	{
		fullscreen_size.width = size.width;
		fullscreen_size.height = size.height;

		if (isFullscreen()) {
			if (size.width < 0 || size.height < 0) {
				auto monitor = getMonitor();
				size = monitor.getNativeResolution();
			}
			glfwSetWindowSize(window, size.width, size.height);
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
			Size size = fullscreen_size;
			if (size.width < 0 || size.height < 0)
				size = monitor.getNativeResolution();

			glfwSetWindowMonitor(window,
				monitor.monitor,
				0, 0, size.width, size.height,
				GLFW_DONT_CARE);
		}

		// Change to window mode by setting the monitor to NULL.
		else {
			glfwSetWindowMonitor(window,
				NULL,
				0, 0, window_size.width, window_size.height,
				GLFW_DONT_CARE);
		}
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
