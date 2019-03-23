#pragma once

#include <map>
#include <string>
#include <typeindex>

#include "AssetReference.hpp"

namespace Core
{
	class AssetManager
	{
		friend class AssetReferenceBase;
	public:

		AssetManager() = default;
		AssetManager(const AssetManager &) = delete;
		~AssetManager();

		template<typename T>
		AssetReference<T> load(const std::string &name);

	private:
		Asset *load(std::type_index id, const std::string &name);
		void add(std::type_index id, const std::string &name, Asset *ptr);
		void remove(std::type_index id, const std::string &name);

		typedef std::map<std::string, Asset*> AssetCollection;
		typedef std::map<std::type_index, AssetCollection> AssetCollectionCollection;
		AssetCollectionCollection assets;
	};

	extern AssetManager asset_manager;


	/* Template method definitions */

	template<typename T>
	AssetReference<T> AssetManager::load(const std::string &name)
	{
		auto ptr = load(typeid(T), name);
		if (ptr == nullptr) {
			ptr = new T();
			add(typeid(T), name, ptr);
		}
		return ptr;
	}
}
