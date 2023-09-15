#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "lib/raylib.h"
#include "Logman.h"


using namespace std;


struct camera_registry_entry
{
	string registry_entry_name;
	Camera *entry_data; // where all data shall be housed
	
	camera_registry_entry(string name, Camera *data) : registry_entry_name(name), entry_data(data) {
		Logman::CustomLog(LOG_INFO, "New Camera Entry created in game registry", NULL);
	};
};



class Registry
{
private:
	static int registry_count;
	vector<shader_registry_entry> shader_registry;
	vector<shader_registry_entry> camera_registry;

public:


	
	
	auto Get(string entry_name, string SearchTable) {};
	
	enum RegistryEntryTypes
	{
		RegistryShaderType = 0,
		RegistryCameraType,
	}EntryTypes;

	enum RegistryDataValueTranslation {
		enum_registry_entry_name_translation = 0,
		enum_registry_entry_data_translation = 1
	};

	struct RegistryDataValueDictionary
	{
		const static string registry_entry_name_translation = "entry name";
		const static string registry_entry_data_translation = "entry data";
		
	};

	template<typename T>
	void Set(string entry_name, Registry::RegistryDataValueTranslation DatasetToModify, T value) {
		auto *entry = &Get(entry_name, entry_name);

		switch (DatasetToModify)
		{
		case RegistryDataValueTranslation::enum_registry_entry_name_translation :
			entry->registry_entry_name = (string)value;
			break;
		
		case RegistryDataValueTranslation::enum_registry_entry_data_translation :
			
			entry->entry_data = (typename)value;
			break;
		default:
			Logman::CustomLog(LOG_WARNING, TextFormat("Translation unit not found! Error code %i", ErrorCode::NULL_EXCEPTION), NULL);
			
			break;
		}

		
		Logman::CustomLog(LOG_INFO, TextFormat("Registry entry %s has been modified!", entry_name), NULL);
		

		//clean up time!
		delete &entry;
	}

	

};
