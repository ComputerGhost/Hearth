#include <HearthLib/IniWriter.hpp>
#include <HearthLib/Logging.hpp>
#include <exception>
#include <fstream>
#include "ConfigReader.hpp"

#include "Config.hpp"

DisplayConfig display_config;
SystemConfig system_config;

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

void loadConfig()
{
	LOG_INFO("Loading default config.");
	if (!loadConfig("config.ini")) {
		LOG_ERROR("Default config could not be loaded.");
		throw std::runtime_error("loadConfig");
	}

	LOG_INFO("Loading user config.");
	if (!loadConfig(system_config.user_path + "config.ini"))
		LOG_WARNING("User config could not be loaded.");
}

void saveConfig()
{
	LOG_INFO("Saving user config.");

	std::ofstream f(system_config.user_path + "config.ini");
	if (!f.is_open()) {
		LOG_WARNING("User config could not be saved.");
		return;
	}

	HearthLib::IniWriter writer(f);

	writer.writeComment("This is a user configuration file.");

	writer.beginSection("display");
	writer.setProperty("width", display_config.size.width);
	writer.setProperty("height", display_config.size.height);
	writer.setProperty("is_fullscreen", display_config.is_fullscreen);
	writer.setProperty("fullscreen_width", display_config.fullscreen_size.width);
	writer.setProperty("fullscreen_height", display_config.fullscreen_size.height);
}
