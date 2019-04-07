#pragma once

#include <HearthLib/FormatException.hpp>
#include <algorithm>
#include "Config.hpp"
#include "Logging.hpp"

#include "ConfigReader.hpp"


void ConfigReader::readAll(std::istream &in)
{
	try {
		HearthLib::IniReader::readAll(in);
	}
	catch (const HearthLib::FormatException &ex) {
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

	auto& cfg = display_config;
	if (property == "width") {
		cfg.size.width = max(cfg.min_size.width, toInt(value));
	}
	else if (property == "height") {
		cfg.size.height = max(cfg.min_size.height, toInt(value));
	}
	else if (property == "is_fullscreen") {
		cfg.is_fullscreen = toBool(value);
	}
	else if (property == "fullscreen_width") {
		cfg.fullscreen_size.width = toInt(value);
		if (cfg.fullscreen_size.width != -1 && cfg.fullscreen_size.width > cfg.min_size.width)
			cfg.fullscreen_size.width = cfg.min_size.width;
	}
	else if (property == "fullscreen_height") {
		cfg.fullscreen_size.height = toInt(value);
		if (cfg.fullscreen_size.height != -1 && cfg.fullscreen_size.height > cfg.min_size.height)
			cfg.fullscreen_size.height = cfg.min_size.height;
	}
	else {
		LOG_NOTICE("Skipping unexpected property '%s'.", property.c_str());
	}
}

void ConfigReader::onSystemProperty(std::string property, std::string value)
{
	using std::max;
	using std::stoi;

	auto& cfg = system_config;
	if (property == "user_path")
		cfg.user_path = value + ((*value.rbegin() == '/') ? "" : "/");
	else
		LOG_NOTICE("Skipping unexpected property '%s'.", property.c_str());
}