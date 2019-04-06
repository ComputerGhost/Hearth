#include "../BinaryReading.hpp"

#include "../FileBundle.hpp"

namespace HearthLib
{
	FileBundle::FileBundle(const std::string &bundle_filename) :
		path_prefix{ bundle_filename + '/' },
		stream{ bundle_filename, std::ios_base::binary }
	{
		if (stream.is_open()) {
			if (!verify(stream, "HearthPack"))
				throw std::runtime_error("Invalid bundle format: " + bundle_filename);
			while (stream.peek() != '0') {
				std::string filename{ readString(stream) };
				std::streampos start{ readDWord(stream) };
				std::streamsize size{ readDWord(stream) };
				entry_map[filename] = std::make_pair(start, size);
			}
		}
	}

	std::streampos FileBundle::open(const std::string &asset_filename)
	{
		// Bundle mode
		if (entry_map.size() != 0) {
			auto entry = entry_map.find(asset_filename);
			if (entry == entry_map.end())
				throw std::runtime_error("Unable to open file: " + asset_filename);
			stream.seekg(entry->second.first);
			return entry->second.second;
		}

		// Directory mode
		else {
			if (stream.is_open())
				stream.close();
			stream.open(path_prefix + asset_filename, std::ios_base::binary);
			if (!stream.is_open())
				throw std::runtime_error("Unable to open file: " + asset_filename);
			stream.seekg(0, std::ios_base::end);
			std::streamsize length = stream.tellg();
			stream.seekg(0);
			return length;
		}
	}

	std::ifstream &FileBundle::getStream()
	{
		return stream;
	}

}