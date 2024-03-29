#pragma once
#include <rlgl.h>
#include <raylib.h>
#include "uDimension.h"
#include "../TechStormOptions.h"

namespace TechStorm {
	class uFBO {
	protected:
		uColor m_clearColor;
		RenderTexture m_FBO;
		uDimension fboDimensions;
		bool m_isDrawing;
		static inline std::map<int, Shader> m_globalPostShaders;
		std::map<int, Shader> m_postProcessShaders;

#ifdef TECHSTORM_ENGINE_3D
		bool m_isIn3DMode;
#else
		bool m_isIn2DMode;
#endif // TECHSTORM_ENGINE_3D
	public:

		virtual void updateDimensions(uDimension updatedDimensions) {
			this->m_FBO = LoadRenderTexture(updatedDimensions.x, updatedDimensions.y);
			if (!IsRenderTextureReady(this->m_FBO)) {
				_sleep(1);
			}
			fboDimensions = updatedDimensions;
		}

		void setClearColor(uColor color) {
			this->m_clearColor = color;
		}

		RenderTexture& getRenderTexture() {
			return this->m_FBO;
		}

		// start drawing mode
		virtual void startDraw()
		{
			BeginDrawing();
			//ClearBackground(m_clearColor);  // Clear texture background
			DrawTextureRec(m_FBO.texture, Rectangle{ 0, 0, (float)(fboDimensions.x), (float)(-fboDimensions.y) }, Vector2{ 0, 0 }, WHITE);
		}

		virtual void enterPost() {
			for (auto& shdr : m_postProcessShaders) {
				BeginShaderMode(shdr.second);
			}
		}

		virtual void exitPost() {
			EndShaderMode();
		}

		// end draing move
		virtual void endDraw()
		{
			EndDrawing();
		}
#ifdef TECHSTORM_ENGINE_3D

		// start 3d drawing
		void start3D(Camera camera)
		{
			BeginMode3D(camera);
		}

		// end 3d drawing
		void end3D()
		{
			EndMode3D();
		}

#else

		// start 2d drawing
		void start2D(Camera* camera)
		{
			if (!m_isDrawing)
			{
				startDraw();
			}
			else
			{
				m_isIn2DMode = true;
				BeginMode2D(*camera);
			}
		}

		// end 2d drawing
		void end2D()
		{
			if (m_isIn2DMode && m_isDrawing)
			{
				EndMode2D();
				m_isIn2DMode = false;
			}
		}
#endif // TECHSTORM_ENGINE_3D

		// start baking to fbo
		void startTexturing()
		{
			// StartDraw();
			BeginTextureMode(m_FBO);
			ClearBackground(m_clearColor);  // Clear texture background
		}

		// stop baking to fbo
		void endTexturing()
		{
			// EndDraw();

			EndTextureMode();
			//ClearBackground(m_clearColor);
			// Warning : DO NOT MOVE THIS! this is important! due to a bug within raylib, this must be
			// done after the texturing is done or a stack overflow WILL occur. GOD DAMN IT!

			//SetTextureFilter(this->operator RenderTexture().texture, TEXTURE_FILTER_ANISOTROPIC_16X);
		}

		void pushGlobalPostShdr(Shader shdr) {
			this->m_postProcessShaders[shdr.id] = shdr;
			m_globalPostShaders[shdr.id] = shdr;
		}

		static Shader getGlobalPostShader(int shdr) {
			return m_globalPostShaders[shdr];
		}

		virtual operator RenderTexture() const {
			return m_FBO;
		}
	};
}
