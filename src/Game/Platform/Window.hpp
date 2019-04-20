#pragma once

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Geometry.hpp"
#include "Monitor.hpp"

namespace Platform
{
	// Platform::Platform will create one of these.
	// Use Platform::window to access it.
	class Window
	{
	public:
		Window(const Window &) = delete;

		Window(const char *title, Size size);
		~Window();

		void setMinimumSize(Size size);
		void setWindowSize(Size size);
		Size getWindowSize();

		Monitor getMonitor() const;
		bool isFullscreen() const;
		void setFullscreenSize(Size size);
		void setFullscreen(bool flag);

		Size getFramebufferSize() const;

		bool shouldClose() const;

		void makeCurrent();
		void swapBuffers();

	private:
		GLFWwindow *window = nullptr;
		Position window_position{ 0, 0 };
		Size window_size;
		Size fullscreen_size{ -1, -1 };
	};

	// You can use the pointer but not change it.
	class WindowPointer : public std::unique_ptr<Window>
	{
		friend class Platform;
		using std::unique_ptr<Window>::reset;
	};

	// This is the pointer to the window.
	extern WindowPointer window;
}