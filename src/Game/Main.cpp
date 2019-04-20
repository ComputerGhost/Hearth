#include <HearthLib/Logging.hpp>
#include <glad/glad.h>
#include <cassert>
#include <exception>

#include "Core/Engine.hpp"
#include "Platform/Platform.hpp"
#include "Platform/Window.hpp"
#include "Scenes/TestScene.hpp"
#include "Config.hpp"

namespace
{
	//
}

int main()
{
	try {

		LOG_INFO("Initializing system.");
		loadConfig();

		Platform::Platform platform("Hearth", display_config.size);
		Platform::window->setMinimumSize(display_config.min_size);
		Platform::window->setFullscreenSize(display_config.fullscreen_size);
		Platform::window->setFullscreen(display_config.is_fullscreen);
		Platform::window->makeCurrent();

		if (!gladLoadGL())
			throw std::runtime_error("Unable to initialize OpenGL context.");

		LOG_INFO("Starting Engine.");
		Core::Engine engine;
		{
			auto scene = std::make_unique<Scenes::TestScene>();
			scene->initialize();
			engine.setScene(std::move(scene));
		}

		LOG_INFO("Engine is running.");
		while (!Platform::window->shouldClose()) {
			engine.tick();
			Platform::window->swapBuffers();
			glfwPollEvents();
		}

		display_config.size = Platform::window->getWindowSize();
		display_config.is_fullscreen = Platform::window->isFullscreen();

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