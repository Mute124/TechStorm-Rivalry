#include "Registry.h"
#include "Errorcode.h"

auto Registry::Get(string entry_name, string SearchTable)
{


    // figures out what exactly the inputted registry table is.
    if (SearchTable == "camera register") goto Camera_Registry;
    else if (SearchTable == "shader register") goto Shader_Registry;
    else Logman::CustomLog(LOG_WARNING, TextFormat("%s is not a valid registry!", SearchTable), NULL);

Camera_Registry:
    
    bool found_entry = false;
    for (int i = 0; i < camera_registry.size() && !found_entry; i++)
    {
        // search for said shader within the registry

        if (camera_registry[i].registry_entry_name == entry_name) {
            return camera_registry[i];
            found_entry == true;
            break;
        } 
        
        // error handling for something that may or may not happen.
        try
        {
            if (i > camera_registry.size())
            {
                throw(i);
            }
        }
        catch (const std::exception &e)
        {
            
            std::cerr << e.what() << '\n';
            Logman::CustomLog(LOG_ERROR, TextFormat("Error %i", ErrorCode::OVERFLOW_EXCEPTION), NULL);
        }
        if (i == shader_registry.size() && !found_entry) {
            Logman::CustomLog(LOG_WARNING, TextFormat("Registry entry %s seems to not exist or was unable to be found!", entry_name), NULL);
        }
    }

Shader_Registry:

    bool found_entry = false;
    for (int i = 0; i < shader_registry.size() && !found_entry; i++)
    {
        // search for said shader within the registry

        if (shader_registry[i].registry_entry_name == entry_name) {
            return shader_registry[i];
            found_entry == true;
            break;
        } 
        
        // error handling for something that may or may not happen.
        try
        {
            if (i > shader_registry.size())
            {
                throw(i);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            Logman::CustomLog(LOG_ERROR, TextFormat("Error %i", ErrorCode::OVERFLOW_EXCEPTION), NULL);
        }
        if (i == shader_registry.size() && !found_entry) {
            Logman::CustomLog(LOG_WARNING, TextFormat("Registry entry %s seems to not exist or was unable to be found", entry_name), NULL);
        }
    }
    
}


Registry::~Registry() {
    
    shader_registry.empty();
    camera_registry.empty();

    delete &shader_registry;
    delete &camera_registry;
}