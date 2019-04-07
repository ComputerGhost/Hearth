#pragma once

#include <iostream>
#include <string_view>

namespace HearthLib
{
	//
	// Simple INI format writer.
	// This does not support escape sequences nor additional features.
	//
	class IniWriter
	{
	public:

		IniWriter() = delete;
		IniWriter(IniWriter &) = delete;
		explicit IniWriter(std::ostream &out);

		void writeComment(std::string_view comment);

		void beginSection(std::string_view section);

		void setProperty(std::string_view property, bool value);
		void setProperty(std::string_view property, double value);
		void setProperty(std::string_view property, int value);
		void setProperty(std::string_view property, std::string_view value);

	private:
		std::ostream *out = nullptr;
	};

}
