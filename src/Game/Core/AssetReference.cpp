#include "AssetManager.hpp"

#include "AssetReference.hpp"

namespace Core
{
	AssetManager asset_manager;

	AssetReferenceBase::AssetReferenceBase(const AssetReferenceBase &other) :
		ptr(other.ptr)
	{
		++ptr->use_count;
	}

	AssetReferenceBase::AssetReferenceBase(Asset *ptr) :
		ptr(ptr)
	{
		++ptr->use_count;
	}

	AssetReferenceBase::~AssetReferenceBase()
	{
		if (--ptr->use_count == 0)
			asset_manager.remove(typeid(*ptr), ptr->name);
	}
}