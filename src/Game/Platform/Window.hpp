#pragma once

#include <GLFW/glfw3.h>
#include "Geometry.hpp"
#include "Monitor.hpp"

namespace Platform
{
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

		bool shouldClose() const;

		void makeCurrent();
		void swapBuffers();

	private:
		GLFWwindow *window = nullptr;
		Position window_position{ 0, 0 };
		Size window_size;
		Size fullscreen_size{ -1, -1 };
	};
}