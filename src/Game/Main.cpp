#include <glad/glad.h>
#include <cassert>
#include <exception>

#include "Core/Engine.hpp"
#include "Platform/Platform.hpp"
#include "Platform/Window.hpp"
#include "Config.hpp"
#include "Logging.hpp"

int main()
{
	try {

		LOG_INFO("Engine is starting.");
		loadConfig();

		Platform::Platform platform;

		Platform::Window window("Hearth", display_config.size);
		window.setMinimumSize(display_config.min_size);
		window.setFullscreenSize(display_config.fullscreen_size);
		window.setFullscreen(display_config.is_fullscreen);
		window.makeCurrent();

		if (!gladLoadGL())
			throw new std::runtime_error("Unable to initialize OpenGL context.");

		Core::Engine engine;
		LOG_INFO("Engine is running.");

		while (!window.shouldClose()) {
			engine.tick();
			window.swapBuffers();
			glfwPollEvents();
		}

		display_config.size = window.getWindowSize();
		display_config.is_fullscreen = window.isFullscreen();

		saveConfig();

		LOG_INFO("Engine is stopped.");
		return EXIT_SUCCESS;
	}
	catch (const std::exception &ex) {
		LOG_ERROR(ex.what());
		return EXIT_FAILURE;
	}
	catch (const std::exception *ex) {
		LOG_WARNING("Programmer threw a pointer to an exception.");
		LOG_ERROR(ex->what());
		return EXIT_FAILURE;
	}

	assert(false && "We should never reach this point.");
}