#pragma once
#include "../../Common.h"


// GBuffer data
typedef struct GBuffer {
    unsigned int framebuffer;

    unsigned int positionTexture;
    unsigned int normalTexture;
    unsigned int albedoSpecTexture;

    unsigned int depthRenderbuffer;
} GBuffer;

// Deferred mode passes
typedef enum {
    EDEFERRED_POSITION,
    EDEFERRED_NORMAL,
    EDEFERRED_ALBEDO,
    EDEFERRED_SHADING
} EDeferredMode;

class DeferedRenderer {
public:
    Shader gBufferShader;
    Shader deferredShader;

    DeferedRenderer() {
    }

    void init() {

    }



private:
    GBuffer gBuffer = { 0 };
};

