#pragma once

#include "../fileSystem/File.h"
#include "ConfigFile.h"
#include "../converters/ConfigTypeConverter.h"
#include "../secretaries/ConfigRegistrySecretary.h"
#include "../registry/ListEntry.h"
#include "../logging/Logman.h"
#include <toml++/toml.hpp>
#include <vector>
#include <stdlib.h>
#include <map>

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

	std::vector<ConfigFile> registry;
};

class ConfigMan : public ConfigRegistrySecretary, public ConfigTypeConverter
{
public:
	static ConfigRegistry* Registry;

	ConfigMan() {
		Logman::customLog(LOG_INFO, "New Config Manager instance created successfully, finding valid TOML and XML files...", NULL);
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

private:
};
