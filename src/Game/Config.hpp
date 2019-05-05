#pragma once

#include <glm/vec2.hpp>
#include <string>

void loadConfig();
void saveConfig();

struct Config
{
	const glm::ivec2 window_min_size{ 640, 480 };
	glm::ivec2 window_size = window_min_size;
	glm::ivec2 fullscreen_size{ -1, -1 };
	bool is_fullscreen = false;

	std::string user_path = "../usr/";
};

extern Config config;
