#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <memory>

namespace Hearth
{
	class Monitor;
}

namespace Hearth
{
	// System will create one of these. Use Hearth::window to access it.
	class Window
	{
	public:
		Window(const Window &) = delete;

		Window(const char *title, glm::ivec2 size);
		~Window();

		void setMinimumSize(glm::ivec2 size);
		void setWindowSize(glm::ivec2 size);
		glm::ivec2 getWindowSize();

		Monitor getMonitor() const;
		bool isFullscreen() const;
		glm::ivec2 getFullscreenSize() const;
		void setFullscreenSize(glm::ivec2 size);
		void setFullscreen(bool flag);

		glm::ivec2 getFramebufferSize() const;

		bool shouldClose() const;

		void makeCurrent();
		void swapBuffers();

	private:
		GLFWwindow *window = nullptr;
		glm::ivec2 window_position{ 0, 0 };
		glm::ivec2 window_size;
		glm::ivec2 fullscreen_size{ -1, -1 };
	};

	// You can use the pointer but not change it.
	class WindowPointer : public std::unique_ptr<Window>
	{
		friend class System;
		using std::unique_ptr<Window>::reset;
	};

	// This is the pointer to the window.
	extern WindowPointer window;
}