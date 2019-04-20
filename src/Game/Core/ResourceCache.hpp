#pragma once

#include <entt/resource/cache.hpp>
#include "../ResourceTypes/ShaderProgram.hpp"
#include "../ResourceTypes/Texture.hpp"

namespace Core
{
	struct ResourceCache
	{
		entt::resource_cache<ResourceTypes::Texture> textures;
		entt::resource_cache<ResourceTypes::ShaderProgram> shader_programs;
	};
}