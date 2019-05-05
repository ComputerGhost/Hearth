#include "Binary.hpp"

namespace Hearth::Formats::Binary
{
	std::uint_fast8_t readByte(std::istream &in)
	{
		return in.get();
	}

	std::uint_fast16_t readWord(std::istream &in)
	{
		return (in.get() << 8) | in.get();
	}

	std::uint_fast32_t readDWord(std::istream &in)
	{
		std::uint_fast32_t value = in.get();
		value = (value << 8) | in.get();
		value = (value << 8) | in.get();
		value = (value << 8) | in.get();
		return value;
	}

	std::string readString(std::istream &in)
	{
		std::string value;
		std::getline(in, value);
		return value;
	}

	bool verify(std::istream &in, std::string_view value)
	{
		for (auto c : value) {
			if (c != in.get())
				return false;
		}
		return true;
	}
}