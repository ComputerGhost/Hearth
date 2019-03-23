#pragma once

#include <string>

namespace Core
{
	class Asset
	{
		friend class AssetReferenceBase;
	public:
		virtual ~Asset() = default;
	private:
		int use_count = 0;
		std::string name;
	};
}
