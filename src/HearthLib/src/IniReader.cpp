#include <cassert>
#include <regex>

#include "../FormatException.hpp"

#include "../IniReader.hpp"

namespace HearthLib
{
	void IniReader::readAll(std::istream &in)
	{
		assert(in.good());

		const std::regex comment_pattern{ R"(^[;#].*$)" };
		const std::regex section_pattern{ R"(^\[(\w*)\]$)" };
		const std::regex keyvalue_pattern{ R"(^(\w*)\s*=\s*(.*)$)" };
		const std::regex whitespace_pattern{ R"(^\s*$)" };

		std::string line;
		while (std::getline(in, line).good()) {
			std::smatch matches;

			if (std::regex_match(line, matches, keyvalue_pattern))
				onProperty(matches[1], matches[2]);
			else if (std::regex_match(line, matches, section_pattern))
				onSection(matches[1]);

			// Valid lines that we ignore:
			else if (std::regex_match(line, matches, comment_pattern));
			else if (std::regex_match(line, matches, whitespace_pattern));

			// Anything else is an error
			else throw FormatException(in.tellg(), line);
		}
	}

	bool IniReader::toBool(std::string value)
	{
		if (value == "true")
			return true;
		else if (value == "false")
			return false;
		else
			throw std::invalid_argument(value);
	}

	double IniReader::toDouble(std::string value)
	{
		return std::stod(value);
	}

	int IniReader::toInt(std::string value)
	{
		return std::stoi(value);
	}

}
