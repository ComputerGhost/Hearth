#pragma once

#include <fstream>
#include <map>
#include <string>

namespace Hearth::Formats
{
	// A bundle file just contains a lot of files concatenated together. If 
	// the file doesn't exist, it invisibly switches to individual files in a
	// directory. This makes switching between them (dev/release) easy.
	class Bundle
	{
	public:
		Bundle() = delete;
		Bundle(const Bundle &) = delete;

		explicit Bundle(const std::string &bundle_filename);

		std::streampos open(const std::string &asset_filename);
		std::ifstream &getStream();

	private:
		std::string path_prefix;
		std::map<std::string, std::pair<std::streampos, std::streamsize>> entry_map;
		std::ifstream stream;
	};
}
