// this is just a dictonary of all the shaders that can be used everywhere. The current system is not going to work forever.
#pragma once
#include "lib/raylib.h"
#include "Globals.h"
#include "Logman.h"
#include <iostream>
#include <vector>
#include <string>


using namespace std;
struct shader_registry_entry 
{
    const string *object_name;
    const Shader *shader;
    const int id;

};

class ShaderPool {
    private:
        vector<shader_registry_entry> shader_registry;

        bool m_delete_requested = false;



    public:
        ShaderPool() : shader_registry() {}

        void SetPooledShaderValue(std::string Name, int locIndex, const void *Value, int UniformType) {}
        
        Shader *GetPooledShader(std::string Name) {}

        ~ShaderPool() {}
};

/*    shader_registry_entry(const string *entry_name, const Shader *shader) : object_name(entry_name), shader(shader), id() {
        Logman::CustomLog(LOG_INFO, TextFormat("Registering shader object %s.", entry_name), NULL);
    }*/