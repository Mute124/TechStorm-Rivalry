#pragma once

#include "../fileSystem/File.h"
#include "ConfigFile.h"
#include "../converters/ConfigTypeConverter.h"
#include "../secretaries/ConfigRegistrySecretary.h"
#include "../registry/ListEntry.h"
#include "../logging/Logman.h"
#include "../../lib/toml.h"
#include <vector>
#include <stdlib.h>
#include <map>

class ConfigFile;





// Component class of ConfigRegistry


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
		try {
			delete this;
		}
		catch(std::exception e) {
			throw e.what();
		}
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