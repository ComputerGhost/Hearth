#pragma once

#include "Asset.hpp"

namespace Core
{
	// Do not use this one. Use AssetReference<T> instaed.
	class AssetReferenceBase
	{
	public:
		AssetReferenceBase() = delete;
		AssetReferenceBase(const AssetReferenceBase &);
		AssetReferenceBase(Asset *ptr);
		~AssetReferenceBase();
	protected:
		Asset *ptr;
	};

	// Use this one.
	template<typename T>
	class AssetReference : public AssetReferenceBase
	{
	public:
	};
}