#pragma once

#include <string>

#include "Platform/Geometry.hpp"

struct DisplayConfig;
struct SystemConfig;

extern DisplayConfig display_config;
extern SystemConfig system_config;

void loadConfig();
void saveConfig();


struct DisplayConfig
{
	const Platform::Size min_size = Platform::Size(640, 480);
	Platform::Size size = min_size;
	Platform::Size fullscreen_size = Platform::Size(-1, -1);
	bool is_fullscreen = false;
};

struct SystemConfig
{
	std::string user_path = "../usr/";
};
