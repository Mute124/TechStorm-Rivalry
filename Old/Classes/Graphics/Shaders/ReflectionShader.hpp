#include "../GameShader.hpp"

class ReflectionShader : public GameShader {
    public:
        ReflectionShader() {
            
        };

        static inline Shader GetShader() {}

        static inline int GetShaderLoc(const char *UniformName) {}
        
        static inline void SetShaderVal(int locIndex, const void *value, int uniformType) {}
    private:

        
        

};