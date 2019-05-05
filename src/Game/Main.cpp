#include <Engine/Window.hpp>
#include <Engine/Engine.hpp>
#include <Engine/Logging.hpp>
#include <Engine/System.hpp>
#include <cassert>

#include "Scenes/TestScene.hpp"
#include "Config.hpp"

int main()
{
	try {

		LOG_INFO("Loading configuration.");
		loadConfig();

		LOG_INFO("Initializing system.");
		Hearth::System system("Hearth", config.window_size);
		Hearth::window->setMinimumSize(config.window_min_size);
		Hearth::window->setFullscreenSize(config.fullscreen_size);
		Hearth::window->setFullscreen(config.is_fullscreen);
		Hearth::window->makeCurrent();

		LOG_INFO("Starting game.");
		Hearth::engine->setState(std::make_unique<Scenes::TestScene>());

		LOG_INFO("Engine is running.");
		Hearth::engine->run();

		LOG_INFO("Saving config.");
		config.window_size = Hearth::window->getWindowSize();
		config.fullscreen_size = Hearth::window->getFullscreenSize();
		config.is_fullscreen = Hearth::window->isFullscreen();
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
