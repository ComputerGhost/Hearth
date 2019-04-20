#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include "../ResourceTypes/Texture.hpp"

namespace Components
{
	struct OverlayItem
	{
		entt::resource_handle<ResourceTypes::Texture> texture_id;
		glm::vec3 position;
		glm::vec2 size;
	};
}