#pragma once

#include <iostream>
#include <string>

namespace Formats
{

	//
	// This is a simple INI format reader.
	// It does not support escape sequences nor additional features.
	//
	class IniReader
	{
	public:

		// Reads all of the INI file
		// Will throw FormatException on failure.
		void readAll(std::istream &in);

	protected:

		virtual void onSection(std::string section) = 0;
		virtual void onProperty(std::string property, std::string value) = 0;

		// Use these to convert the value to another type.
		// Will throw std::invalid_argument or std::out_of_range on error.
		bool toBool(std::string value);
		double toDouble(std::string value);
		int toInt(std::string value);

	};

}
