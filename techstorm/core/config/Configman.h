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
		registry.push_back(new ConfigFile(FileName));
		Logman::Log(TextFormat("Config Registry : TOML Config File at %s registered and loaded...", FileName));
	}

	// Flush the registry, WILL NOT SAVE!
	int flushConfig()
	{
		ConfigFile::flushConfig();
		bool issuccessful = registry.empty();
		return issuccessful;
	}

	ConfigRegistrySecretary* ConfigSecretary = new ConfigRegistrySecretary(); // Searching component

	std::vector<ConfigFile*> registry;
};

class ConfigMan : public ConfigRegistrySecretary, public ConfigTypeConverter
{
public:
	static inline ConfigRegistry* Registry;

	ConfigMan() {
		Logman::customLog(LOG_INFO, "New Config Manager instance created successfully, finding valid TOML and XML files...", NULL);
		Registry = new ConfigRegistry();
		ConfigFile::initConfigFile();

		try
		{
			FilePathList tomlConfigs = LoadDirectoryFilesEx("Config", ".toml", false);
			Logman::Log("Configman : Loading all game and engine config files...");

			if (tomlConfigs.count == 0) {
				Logman::Log("Configman : No global TOML files found, Skipping step...");
			}
			else {
				for (int i = 0; i < tomlConfigs.count; i++) {
					const char* path = tomlConfigs.paths[i];
					Logman::Log(TextFormat("Configman : TOML Config file found at %s! Loading file...", path));

					Registry->registerFile(path);
				}
			}

			// we dont need them anymore, they have been pushed elsewhere.
			UnloadDirectoryFiles(tomlConfigs);
			Logman::Log("Configman : Game and Engine config files loaded... Searching for mod TOML Files...");

			FilePathList modConfigs = LoadDirectoryFilesEx("mods", ".toml", true);

			if (modConfigs.count == 0) {
				Logman::Log("Configman : No mod TOML files found, Skipping step...");
			}
			else {
				for (int i = 0; i < modConfigs.count; i++) {
					const char* path = modConfigs.paths[i];
					Logman::Log(TextFormat("Configman : TOML Config file found at %s! Loading file...", path));
					Registry->registerFile(path);
				}
			}

			UnloadDirectoryFiles(modConfigs);

			Logman::Log("Configman : All TOML files loaded!");
		}
		catch (const std::exception& e)
		{
			Logman::Error(TextFormat("Configman : I have experienced an error! %s", e.what()));
		}
	};

	~ConfigMan() {
		delete this;
	}

	static void initConfigFile() {
		Registry = new ConfigRegistry();

		Logman::customLog(LOG_INFO, "Loading TOML files from Config folder...", NULL);

		Logman::customLog(LOG_INFO, "Loaded TOML files from Config folder", NULL);
	}
};
