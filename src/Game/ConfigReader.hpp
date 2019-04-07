#pragma once

#include <HearthLib/IniReader.hpp>

//
// Assists in reading in a configuration file.
// Prefer to call loadConfig in Config instead.
//
class ConfigReader : private HearthLib::IniReader
{
public:

	// Reads all of the INI file
	void readAll(std::istream &in);

private:

	enum class ConfigSection
	{
		Display,
		System,
		Other,
	};

	// Necessary overrides from parent class
	void onSection(std::string section) override;
	void onProperty(std::string property, std::string value) override;

	// Our helper functions for cleaner code
	void onDisplayProperty(std::string property, std::string value);
	void onSystemProperty(std::string property, std::string value);

	ConfigSection current_section;

};
