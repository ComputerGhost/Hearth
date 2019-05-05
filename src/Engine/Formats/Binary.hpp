#pragma once

#include <cstdint>
#include <istream>
#include <string>

namespace Hearth::Formats::Binary
{
	// All of these functions assume the stream is in binary mode.
	// i.e. don't open an fstream in the default text mode.

	std::uint_fast8_t readByte(std::istream &in);
	std::uint_fast16_t readWord(std::istream &in);
	std::uint_fast32_t readDWord(std::istream &in);

	// Reads in a null-terminated string.
	std::string readString(std::istream &in);

	// Returns true if the next bytes are equal to the value.
	bool verify(std::istream &in, std::string_view value);
}
