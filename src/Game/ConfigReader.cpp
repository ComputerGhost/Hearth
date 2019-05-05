#pragma once

#include <Engine/Formats/FormatException.hpp>
#include <Engine/Logging.hpp>
#include <algorithm>
#include "Config.hpp"

#include "ConfigReader.hpp"


void ConfigReader::readAll(std::istream &in)
{
	try {
		Hearth::Formats::IniReader::readAll(in);
	}
	catch (const Hearth::Formats::FormatException &ex) {
		LOG_ERROR("Config was partially read. The file is invalid at offset %d: %s",
			ex.where(), ex.what());
	}
}


void ConfigReader::onSection(std::string section)
{
	if (false);
	else if (section == "display")
		current_section = ConfigSection::Display;
	else if (section == "system")
		current_section = ConfigSection::System;
	else {
		current_section = ConfigSection::Other;
		LOG_NOTICE("Skipping unexpected section '%s'.", section.c_str());
	}
}

void ConfigReader::onProperty(std::string property, std::string value)
{
	try {
		switch (current_section) {
		case ConfigSection::Display:
			onDisplayProperty(property, value);
			break;
		case ConfigSection::System:
			onSystemProperty(property, value);
			break;
		}
	}
	catch (const std::invalid_argument &) {
		LOG_WARNING("Skipping invalid value '%s' for property '%s'.",
			value.c_str(), property.c_str());
	}
	catch (const std::out_of_range &) {
		LOG_WARNING("Skipping out of range value '%s' for property '%s'.",
			value.c_str(), property.c_str());
	}
}


void ConfigReader::onDisplayProperty(std::string property, std::string value)
{
	using std::max;

	if (property == "width") {
		config.window_size.x = max(config.window_size.x, toInt(value));
	}
	else if (property == "height") {
		config.window_size.y = max(config.window_size.y, toInt(value));
	}
	else if (property == "is_fullscreen") {
		config.is_fullscreen = toBool(value);
	}
	else if (property == "fullscreen_width") {
		config.fullscreen_size.x = toInt(value);
		if (config.fullscreen_size.x != -1 && config.fullscreen_size.x >= config.window_min_size.x)
			config.fullscreen_size.x = config.window_min_size.x;
	}
	else if (property == "fullscreen_height") {
		config.fullscreen_size.y = toInt(value);
		if (config.fullscreen_size.y != -1 && config.fullscreen_size.y >= config.window_min_size.y)
			config.fullscreen_size.y = config.window_min_size.y;
	}
	else {
		LOG_NOTICE("Skipping unexpected property '%s'.", property.c_str());
	}
}

void ConfigReader::onSystemProperty(std::string property, std::string value)
{
	using std::max;
	using std::stoi;

	if (property == "user_path")
		config.user_path = value + ((*value.rbegin() == '/') ? "" : "/");
	else
		LOG_NOTICE("Skipping unexpected property '%s'.", property.c_str());
}