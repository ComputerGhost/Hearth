#include <cassert>
#include <cstdio>
#include <memory>

#include "IniWriter.hpp"


namespace Formats
{

	IniWriter::IniWriter(std::ostream &out) :
		out(&out)
	{
	}

	void IniWriter::writeComment(std::string_view comment)
	{
		*out << "; " << comment << std::endl;
	}

	void IniWriter::beginSection(std::string_view section)
	{
		*out << std::endl;
		*out << "[" << section << "]" << std::endl;
	}

	void IniWriter::setProperty(std::string_view property, bool value)
	{
		std::string_view formatted_value = value ? "true" : "false";
		setProperty(property, formatted_value);
	}

	void IniWriter::setProperty(std::string_view property, double value)
	{
		int size = snprintf(NULL, 0, "%f", value);
		auto buffer = std::make_unique<char[]>(size + 1);
		sprintf(buffer.get(), "%f", value);
		setProperty(property, std::string_view(buffer.get()));
	}

	void IniWriter::setProperty(std::string_view property, int value)
	{
		int size = snprintf(NULL, 0, "%d", value);
		auto buffer = std::make_unique<char[]>(size + 1);
		sprintf(buffer.get(), "%d", value);
		setProperty(property, std::string_view(buffer.get()));
	}

	void IniWriter::setProperty(
		std::string_view property, std::string_view value)
	{
		*out << property << " = " << value << std::endl;
	}

}
