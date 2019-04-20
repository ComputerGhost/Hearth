#pragma once

#include <entt/entity/registry.hpp>
#include "../Core/ResourceCache.hpp"

namespace Systems
{
	void renderOverlayItems(const Core::ResourceCache &cache, entt::registry &registry);
}