#include "Shaderpool.h"
#include "Errorcode.h"



ShaderPool::ShaderPool() : shader_registry() {
    Logman::CustomLog(LOG_INFO, TextFormat("Shader pool Created at %i", &shader_registry), NULL);

}

void ShaderPool::SetPooledShaderValue(std::string shader_name, int locIndex, const void *Value, int UniformType) {
    bool foundShader = false;
    for (int i = 0; i < shader_registry.size() && !foundShader; i++) {
        // search for said shader within the registry

        if (shader_registry[i].object_name == shader_name) {
            
            SetShaderValue(shader_registry[i].shader, );
            break;
        }

        // error handling for something that may or may not happen.
        try
        {
            if (i > shader_registry.size()) {
                throw (i);
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            Logman::CustomLog(LOG_ERROR, TextFormat("Error %i", ErrorCode::OVERFLOW_EXCEPTION), NULL);
        }

        
    }
}