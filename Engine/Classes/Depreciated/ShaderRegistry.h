#pragma once 
#include "lib/raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include "Logman.h"

using namespace std;

struct shader_registry_entry
{
	string registry_entry_name;
	Shader *entry_data; // where all data shall be housed
	shader_registry_entry(string name, Shader *data) : registry_entry_name(name), entry_data(data) {
		Logman::CustomLog(LOG_INFO, "New Shader Entry created in game registry", NULL);
	};
};


class ShaderRegistry
{
    private:
        vector<shader_registry_entry> reg;

    public:
        
        Shader Pull(string uname) {};

        void Push(string uname, Shader *new_Data) {}

};
