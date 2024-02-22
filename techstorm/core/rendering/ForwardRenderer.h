#pragma once
#include "../../Common.h"

// handles rendering
class ForwardRenderer final
{
public:

	ForwardRenderer() {
		init();
	}

	void init() {}

	void update() {
	}

	// start drawing mode
	void startDraw()
	{
		isDrawing = true;
		BeginDrawing();
	}

	// end draing move
	void endDraw()
	{
		isDrawing = false;
		EndDrawing();
	}

	// start 3d drawing
	void start3D(Camera* camera)
	{
		if (!isDrawing)
		{
			startDraw();
		}
		else
		{
			isIn3DMode = true;
			BeginMode3D(*camera);
		}
	}

	// end 3d drawing
	void end3D()
	{
		if (isIn3DMode && isDrawing)
		{
			EndMode3D();
			isIn3DMode = false;
		}
	}

	// start baking to fbo
	void startTexturing()
	{
		// StartDraw();
		BeginTextureMode(fbo);
		ClearBackground(BLACK);
	}

	// start shadow mapping
	void startDepthMode()
	{
		BeginTextureMode(depthMapFBO);
	}

	// stop shadow mapping
	void stopDepthMode()
	{
		EndTextureMode();
	}

	// stop baking to fbo
	void stopTexturing()
	{
		// EndDraw();
		EndTextureMode();
	}

	// Create the FBO and depth map FBO
	void createRenderTexture(int width, int height)
	{
		fbo = LoadRenderTexture(width, height);
		depthMapFBO = LoadRenderTexture(width, height);
	}



	RenderTexture2D fbo; // FBO render texture
	RenderTexture2D depthMapFBO; // shadowmap.

	// pbr shader
	Shader pbrShader;
	// bloom shader
	Shader bloomShader;

private:

	// Task Templates




	bool isDrawing;
	bool isIn3DMode;
};