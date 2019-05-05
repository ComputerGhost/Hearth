#include <Engine/Formats/IniWriter.hpp>
#include <Engine/Logging.hpp>
#include <exception>
#include <fstream>
#include "ConfigReader.hpp"

#include "Config.hpp"

Config config;

namespace
{
	bool loadConfig(std::string filename);
}

void loadConfig()
{
	LOG_INFO("Loading default config.");
	if (!loadConfig("config.ini")) {
		LOG_ERROR("Default config could not be loaded.");
		throw std::runtime_error("loadConfig");
	}

	LOG_INFO("Loading user config.");
	if (!loadConfig(config.user_path + "config.ini"))
		LOG_WARNING("User config could not be loaded.");
}

void saveConfig()
{
	LOG_INFO("Saving user config.");

	std::ofstream f(config.user_path + "config.ini");
	if (!f.is_open()) {
		LOG_WARNING("User config could not be saved.");
		return;
	}

	Hearth::Formats::IniWriter writer(f);

	writer.writeComment("This is a user configuration file.");

	writer.beginSection("display");
	writer.setProperty("width", config.window_size.x);
	writer.setProperty("height", config.window_size.y);
	writer.setProperty("is_fullscreen", config.is_fullscreen);
	writer.setProperty("fullscreen_width", config.fullscreen_size.x);
	writer.setProperty("fullscreen_height", config.fullscreen_size.y);
}

namespace
{
	bool loadConfig(std::string filename)
	{
		LOG_DEBUG("Loading config from path: %s", filename.c_str());

		std::ifstream f(filename);
		if (!f.is_open())
			return false;

		ConfigReader().readAll(f);

		return true;
	}
}