#pragma once

#include "Logman.h"
#include "toml.h"
#include <vector>
#include <stdlib.h>
#include <map>
#include <vector>


class ConfigFile;

template<typename T>
struct File
{
	T Data;
	const char* FilePath; // full path to file.
	bool isLoaded;
};
template<typename T>
struct ListEntry
{
	T entry;
	const char* tag;
	int id;
};

class ConfigTypeConverter {
public:

	static int charToInt(const char* value) {
		return textToInteger(value);
	}

	static int textToInteger(const char* value) {
		return atoi(value);
	}

	// converts string into C readable const char *, then passes it to a function.
	static int strToInt(std::string* value) {
		if (value->c_str() == "true") {
			return 1;
		}
		else if (value->c_str() == "false") {
			return 0;
		}
		else {
			const char* charconversion = value->c_str();

			return textToInteger(charconversion);
		}
	}

	static int int64ToInt(int64_t* value) {
		return *value;
	}

private:
};

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
		int id = configFileCount;
		configFileCount += 1;
		return id;
	}

	static int configFileCount; // Corrosponds with place in what list it is in
};

// Component class of ConfigRegistry
class ConfigRegistrySecretary {
public:
	ConfigRegistrySecretary() {}

	static inline ConfigFile findFile(std::vector<ConfigFile>& Dataset, const char* TargetFile) {
		ConfigFile file;
		if (doesFileExist(Dataset, TargetFile)) {
			for (int i = 0; i < Dataset.size(); i++) {
				if (Dataset[i].file.entry.FilePath == TargetFile) {
					file = Dataset[i];
				}
			}
		}
		return file;
	}

	static inline bool doesFileExist(std::vector<ConfigFile>& Dataset, const char* TargetFile) {
		bool found = false;
		for (int i = 0; i < Dataset.size(); i++) {
			if (Dataset[i].file.entry.FilePath == TargetFile) {
				found = true;
			}
		}
		if (!found) {
			found = false;
		}

		return found;
	}
};

class ConfigRegistry
{
public:
	ConfigRegistry() {
	}

	~ConfigRegistry() {
		delete ConfigSecretary;
	}

	bool isFileRegistered(const char* FileName)
	{
		return ConfigSecretary->doesFileExist(registry, FileName);
	}

	// Get a config FileName
	ConfigFile getFile(const char* FileName)
	{
		return ConfigSecretary->findFile(registry, FileName);
	}

	// register a config FileName into the registry
	void registerFile(const char* FileName)
	{
		registry.push_back(ConfigFile(FileName));
	}

	// Flush the registry, WILL NOT SAVE!
	int flushConfig()
	{
		ConfigFile::flushConfig();
		bool issuccessful = registry.empty();
		return issuccessful;
	}

	ConfigRegistrySecretary* ConfigSecretary = new ConfigRegistrySecretary(); // Searching component
private:

	std::vector<ConfigFile> registry;
};

// NOTE : NO LONGER BROKEN!!! Still have to refactor though to use Registry Class. FUUUUUUUUUUUUUUUUUUUUUU
class ConfigMan : public ConfigRegistrySecretary, public ConfigTypeConverter
{
public:

	ConfigMan() {
		Logman::customLog(LOG_INFO, "New Config Manager instance created successfully!", NULL);
	};

	~ConfigMan() {
		delete this;
	}

	static void initConfigFile() {
		Registry = new ConfigRegistry();

		ConfigFile::initConfigFile();
		Logman::customLog(LOG_INFO, "Loading TOML files from Config folder...", NULL);

		// TODO : Make this automatic.
		Registry->registerFile("Config/Engine.toml");
		Registry->registerFile("Config/options.toml");

		Logman::customLog(LOG_INFO, "Loaded TOML files from Config folder", NULL);
	}

	static ConfigRegistry* Registry;

private:
};