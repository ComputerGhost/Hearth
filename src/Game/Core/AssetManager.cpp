#include "AssetManager.hpp"

namespace Core
{

	AssetManager::~AssetManager()
	{
	}

	Asset *AssetManager::load(std::type_index id, const std::string &name)
	{
		auto found = assets[id].find(name);
		if (found == assets[id].end())
			return nullptr;
		return found->second;
	}

	void AssetManager::add(std::type_index id, const std::string &name, Asset *ptr)
	{
		assets[id][name] = ptr;
	}

	void AssetManager::remove(std::type_index id, const std::string &name)
	{
		auto found = assets[id].find(name);
		if (found == assets[id].end())
			return;
		delete found->second;
		assets[id].erase(found);
	}
}