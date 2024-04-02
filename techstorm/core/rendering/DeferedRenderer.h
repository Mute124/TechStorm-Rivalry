#pragma once
#include "../../Common.h"
#include "../states/GameState.h"
#include <rlgl.h>

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

	void init(GameState* gameState) {
		gBufferShader = LoadShader("resources/shaders/glsl330/gbuffer.vs", "resources/shaders/glsl330/gbuffer.fs");
		deferredShader = LoadShader("resources/shaders/glsl330/deferred_shading.vs", "resources/shaders/glsl330/deferred_shading.fs");

		deferredShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(deferredShader, "viewPosition");

		gBuffer = { 0 };
		gBuffer.framebuffer = rlLoadFramebuffer();

		rlEnableFramebuffer(gBuffer.framebuffer);

		gBuffer.positionTexture = rlLoadTexture(NULL, gameState->screenWidth, gameState->screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32, 1);
		gBuffer.normalTexture = rlLoadTexture(NULL, gameState->screenWidth, gameState->screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32, 1);

		// Albedo (diffuse color) and specular strength can be combined into one texture.
		// The color in RGB, and the specular strength in the alpha channel.
		gBuffer.albedoSpecTexture = rlLoadTexture(NULL, gameState->screenWidth, gameState->screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);

		// Activate the draw buffers for our framebuffer
		rlActiveDrawBuffers(3);

		// Now we attach our textures to the framebuffer.
		rlFramebufferAttach(gBuffer.framebuffer, gBuffer.positionTexture, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
		rlFramebufferAttach(gBuffer.framebuffer, gBuffer.normalTexture, RL_ATTACHMENT_COLOR_CHANNEL1, RL_ATTACHMENT_TEXTURE2D, 0);
		rlFramebufferAttach(gBuffer.framebuffer, gBuffer.albedoSpecTexture, RL_ATTACHMENT_COLOR_CHANNEL2, RL_ATTACHMENT_TEXTURE2D, 0);

		// Finally we attach the depth buffer.
		gBuffer.depthRenderbuffer = rlLoadTextureDepth(gameState->screenWidth, gameState->screenHeight, true);
		rlFramebufferAttach(gBuffer.framebuffer, gBuffer.depthRenderbuffer, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);

		// Make sure our framebuffer is complete.
		// NOTE: rlFramebufferComplete() automatically unbinds the framebuffer, so we don't have
		// to rlDisableFramebuffer() here.
		if (!rlFramebufferComplete(gBuffer.framebuffer))
		{
			TraceLog(LOG_WARNING, "Framebuffer is not complete");
			exit(1);
		}

		// Now we initialize the sampler2D uniform's in the deferred shader.
		// We do this by setting the uniform's value to the color channel slot we earlier
		// bound our textures to.
		rlEnableShader(deferredShader.id);

		rlSetUniformSampler(rlGetLocationUniform(deferredShader.id, "gPosition"), 0);
		rlSetUniformSampler(rlGetLocationUniform(deferredShader.id, "gNormal"), 1);
		rlSetUniformSampler(rlGetLocationUniform(deferredShader.id, "gAlbedoSpec"), 2);

		rlDisableShader();
	}

private:
	GBuffer gBuffer = { 0 };
};
