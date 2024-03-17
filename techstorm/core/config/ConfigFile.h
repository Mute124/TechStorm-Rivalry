#pragma once
#include "../../lib/toml.h"
#include "ConfigFile.h"
#include "../registry/ListEntry.h"
#include "../fileSystem/File.h"

class ConfigFile
{
public:
	// FilePath path goes in here
	ConfigFile(const char* File)
	{
		file.id = assignId(); // Assign the file's id;

		file.entry.FilePath = File;
		file.entry.Data = toml::parse_file(File);
		file.tag = "Config";
		file.entry.isLoaded = true; // signals that this is ready.
	}

	ConfigFile()
	{
		// creates a Null.
	}

	ConfigFile* getConfig() {
		return this;
	}

	// The solution to the issue of not being able to get a int from a config file.
	int getIntEntry(const char* section, const char* entry)
	{
		// convert from int64_t to int
		toml::table tbl = *(file.entry.Data[section][entry].as_table()); // Tableize

		int result = tbl[section][entry].as_integer()->operator int64_t & ();

		return result;
	}

	bool getBoolEntry(const char* section, const char* entry)
	{
		toml::table tbl = *(file.entry.Data[section][entry].as_table());

		bool result = bool{ tbl[section][entry].as_boolean()->operator const bool& () };

		return result;
	}

	// since VSCode complains, this needs to be here.
	static void initConfigFile() {
		configFileCount = 0;
	}

	// reset count
	static inline void flushConfig()
	{
		configFileCount = 0;
	}
	ListEntry<File<toml::v3::parse_result>> file;
private:
	static inline int assignId()
	{
		int fileId = configFileCount;
		configFileCount++;
		return fileId;
	}

	static int configFileCount; // Corrosponds with place in what list it is in
};
