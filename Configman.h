#pragma once

#include "Logman.h"
#include "toml.h"
#include <vector>
#include <stdlib.h>
#include <map>
#include <vector>

// Note : Declared here as some higher in the order classes use it. Do not move this.
class ConfigFile;

// a template file structure.
template<typename T>
struct File
{
	T Data; ///< Data stored in the file.
	const char* FilePath; ///< Full path to the file.
	bool isLoaded; ///< Flag indicating if the file is loaded or not.

	/**
	 * @brief Constructor for File structure.
	 * @param data Data to be stored in the file.
	 * @param filePath Full path to the file.
	 * @param loaded Flag indicating if the file is loaded or not.
	 */
	File(T data, const char* filePath, bool loaded) : Data(data), FilePath(filePath), isLoaded(loaded) {}
};

/**
 * @brief A struct representing an entry in a list
 *
 * @tparam T The type of the entry
 */
template<typename T>
struct ListEntry
{
	T entry; /**< The entry value */
	const char* tag; /**< The tag associated with the entry */
	int id; /**< The unique identifier for the entry */
};

class ConfigTypeConverter {
public:
	/**
	 * @brief Converts a char pointer to an integer value.
	 * @param value The input char pointer.
	 * @return The converted integer value.
	 */
	static int CharToInt(const char* value) {
		return TextToInteger(value);
	}

	/**
	 * @brief Converts a string to an integer.
	 *
	 * This function converts the input string to an integer. If the string is "true", it returns 1; if the string is "false", it returns 0; otherwise, it converts the string to an integer using TextToInteger function.
	 *
	 * @param value The input string.
	 * @return The converted integer value.
	 */
	static int StrToInt(std::string* value) {
		if (value->c_str() == "true") {
			return 1;
		}
		else if (value->c_str() == "false") {
			return 0;
		}
		else {
			const char* charconversion = value->c_str();
			return TextToInteger(charconversion);
		}
	}

	/**
	 * @brief Converts a 64-bit integer to a 16-bit integer value.
	 * @param value The input 64-bit integer pointer.
	 * @return The converted 16-bit integer value.
	 */
	static int Int64ToInt(int64_t* value) {
		return *value;
	}
};

/**
 * @brief The ConfigFile class represents a configuration file and provides methods to access its data.
 */
class ConfigFile
{
public:

	/**
	 * @brief Constructs a ConfigFile object and loads the data from the specified file.
	 *
	 * @param File The path to the configuration file.
	 */
	ConfigFile(const char* File)
	{
		// Assign the file's id
		file.id = AssignId();

		// Set the file path, load and parse the data, and set the tag and loaded status
		file.entry.FilePath = File;
		file.entry.Data = toml::parse_file(File);
		file.tag = "Config";
		file.entry.isLoaded = true;
	}

	/**
	 * @brief Default constructor for ConfigFile.
	 *
	 * @details Creates a Null object.
	 */
	ConfigFile()
	{
		// creates a Null.
	}

	/**
	 * @brief Get the instance of ConfigFile.
	 *
	 * @return ConfigFile* A pointer to the instance of ConfigFile.
	 */
	ConfigFile* Get() {
		return this;
	}

	/**
	 * @brief Get the integer value of a specific entry in the configuration file.
	 *
	 * @param section The section in the configuration file.
	 * @param entry The entry in the specified section.
	 * @return int The integer value of the specified entry.
	 */
	int GetIntEntry(const char* section, const char* entry)
	{
		// convert from int64_t to int
		toml::table tbl = *(file.entry.Data[section][entry].as_table()); // Tableize

		// get the value of the entry parameter in the section parameter of the TOML file table as an int
		int result = tbl[section][entry].as_integer()->operator int64_t & ();

		// Now we can return it.
		return result;
	}

	/**
	 * @brief Get the boolean value of a specific entry in the configuration file.
	 *
	 * @param section The section in the configuration file.
	 * @param entry The entry in the specified section.
	 * @return bool The boolean value of the specified entry.
	 */
	bool GetBoolEntry(const char* section, const char* entry)
	{
		toml::table tbl = *(file.entry.Data[section][entry].as_table());

		bool result = bool{ tbl[section][entry].as_boolean()->operator const bool& () };

		return result;
	}

	/**
	 * @brief Initialize the ConfigFile class.
	 *
	 * @details Set the ConfigFileCount to 0.
	 */
	static void Innit() {
		ConfigFileCount = 0;
	}

	/**
	 * @brief Reset the count of ConfigFile objects.
	 */
	static inline void Flush()
	{
		ConfigFileCount = 0;
	}

	ListEntry<File<toml::v3::parse_result>> file;

private:
	/**
	 * @brief Assigns a unique id to the ConfigFile object.
	 *
	 * @return int The unique id assigned to the ConfigFile object.
	 */
	static inline int AssignId()
	{
		int id = ConfigFileCount;
		ConfigFileCount += 1;
		return id;
	}

	static int ConfigFileCount; // Corresponds with place in what list it is in
};

// Component class of ConfigRegistry, acts as a secretary for the config registry
class ConfigRegistrySecretary {
public:
	ConfigRegistrySecretary() {}

	/**
	 * @brief Find a ConfigFile in the Dataset by TargetFile
	 *
	 * @param Dataset The vector of ConfigFiles to search
	 * @param TargetFile The file to search for
	 * @return The found ConfigFile, or an empty ConfigFile if not found
	 */
	static inline ConfigFile FindFile(std::vector<ConfigFile>& Dataset, const char* TargetFile) {
		ConfigFile file;
		if (DoesFileExist(Dataset, TargetFile)) {
			for (int i = 0; i < Dataset.size(); i++) {
				if (Dataset[i].file.entry.FilePath == TargetFile) {
					file = Dataset[i];
				}
			}
		}
		return file;
	}

	/**
	 * @brief Check if a file exists in the Dataset
	 *
	 * @param Dataset The vector of ConfigFiles to search
	 * @param TargetFile The file to search for
	 * @return true if the file exists, false otherwise
	 */
	static inline bool DoesFileExist(std::vector<ConfigFile>& Dataset, const char* TargetFile) {
		bool found = false;
		for (int i = 0; i < Dataset.size(); i++) {
			if (Dataset[i].file.entry.FilePath == TargetFile) {
				found = true;
			}
		}
		return found;
	}
};

/**
 * @brief The ConfigRegistry class manages a registry of configuration files.
 */
class ConfigRegistry
{
public:
    /**
     * @brief Constructor for ConfigRegistry.
     */
    ConfigRegistry() {
    }

    /**
     * @brief Destructor for ConfigRegistry.
     */
    ~ConfigRegistry() {
        delete ConfigSecretary;
    }

    /**
     * @brief Check if a file is registered in the registry.
     * @param FileName The name of the file to check.
     * @return True if the file is registered, false otherwise.
     */
    bool IsFileRegistered(const char* FileName)
    {
        return ConfigSecretary->DoesFileExist(registry, FileName);
    }

    /**
     * @brief Get a configuration file from the registry.
     * @param FileName The name of the file to get.
     * @return The configuration file.
     */
    ConfigFile GetFile(const char* FileName)
    {
        return ConfigSecretary->FindFile(registry, FileName);
    }

    /**
     * @brief Register a configuration file into the registry.
     * @param FileName The name of the file to register.
     */
    void RegisterFile(const char* FileName)
    {
        registry.push_back(ConfigFile(FileName));
    }

    /**
     * @brief Flush the registry, WILL NOT SAVE!
     * @return 1 if the registry is empty, 0 otherwise.
     */
    int Flush()
    {
        ConfigFile::Flush();
        bool issuccessful = registry.empty();
        return issuccessful;
    }

    ConfigRegistrySecretary* ConfigSecretary = new ConfigRegistrySecretary(); // Searching component
private:

    std::vector<ConfigFile> registry;
};

// NOTE : NO LONGER BROKEN!!! Still have to refactor though to use Registry Class. FUUUUUUUUUUUUUUUUUUUUUU
// ConfigMan class, responsible for managing configurations
class ConfigMan : public ConfigRegistrySecretary, public ConfigTypeConverter
{
public:
	// Constructor for ConfigMan
	ConfigMan() {
		Logman::CustomLog(LOG_INFO, "New Config Manager instance created successfully!", NULL);
	};

	// Destructor for ConfigMan
	~ConfigMan() {
		delete this;
	}

	// Initialize the configuration manager
	static void Innit() {
		Registry = new ConfigRegistry();

		ConfigFile::Innit();
		Logman::CustomLog(LOG_INFO, "Loading TOML files from Config folder...", NULL);

		// TODO : Make this automatic.
		Registry->RegisterFile("Config/Engine.toml");
		Registry->RegisterFile("Config/options.toml");

		Logman::CustomLog(LOG_INFO, "Loaded TOML files from Config folder", NULL);
	}

	static ConfigRegistry* Registry;  // Registry for configuration files
};