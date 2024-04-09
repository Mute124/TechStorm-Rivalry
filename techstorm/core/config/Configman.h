#pragma once
#include "../TechStorm.h"
#include "../fileSystem/File.h"
#include "ConfigFile.h"
#include "../converters/ConfigTypeConverter.h"
#include "../secretaries/ConfigRegistrySecretary.h"
#include "../registry/ListEntry.h"
#include "../logging/Logman.h"
#include "../registry/Registry.h"
#include <toml++/toml.hpp>
#include <vector>
#include <stdlib.h>
#include <map>

#ifdef TECHSTORM_ENABLE_CONFIG

namespace TechStorm {

	// Component class of ConfigRegistry
	class ConfigRegistry : virtual MRegistry_Str<ConfigFile>, public ConfigRegistrySecretary
	{
	public:
		ConfigRegistry() {
		}

		~ConfigRegistry() {
		}

		bool isFileRegistered(const char* file)
		{
			return entryExists(file);
		}

		// Get a config FileName
		ConfigFile* getFile(const char* file)
		{
			return getEntry(file);
		}

		// register a config FileName into the registry
		void registerFile(const char* path)
		{
			addEntry(new ConfigFile(path), GetFileName(path));
		}

		// Flush the registry, WILL NOT SAVE!
		int flushConfig()
		{
			ConfigFile::flushConfig();

			return true;
		}
	};

	class ConfigMan : public ConfigRegistrySecretary, public ConfigTypeConverter
	{
	public:
		static inline ConfigRegistry* confRegistry;

		ConfigMan() {};

		~ConfigMan() {
		}

		void initConfigMan() {
			Logman::customLog(LOG_INFO, "New Config Manager instance created successfully, finding valid TOML and XML files...", NULL);
			confRegistry = new ConfigRegistry();
			ConfigFile::initConfigFile();

			try
			{
				FilePathList tomlConfigs = LoadDirectoryFilesEx("data/config", ".toml", false);
				Logman::Log("Configman : Loading all game and engine config files...");

				if (tomlConfigs.count == 0) {
					Logman::Log("Configman : No global TOML files found, Skipping step...");
				}
				else {
					for (int i = 0; i < tomlConfigs.count; i++) {
						const char* path = tomlConfigs.paths[i];
						Logman::Log(TextFormat("Configman : TOML Config file found at %s! Loading file...", path));

						confRegistry->registerFile(path);
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
						confRegistry->registerFile(path);
					}
				}

				UnloadDirectoryFiles(modConfigs);

				Logman::Log("Configman : All TOML files loaded!");
			}
			catch (const std::exception& e)
			{
				Logman::Error(TextFormat("Configman : I have experienced an error! %s", e.what()));
			}
		}
		static void initConfigFile() {
			confRegistry = new ConfigRegistry();

			Logman::customLog(LOG_INFO, "Loading TOML files from Config folder...", NULL);

			Logman::customLog(LOG_INFO, "Loaded TOML files from Config folder", NULL);
		}
	};
}
#endif // TECHSTORM_ENABLE_CONFIG
