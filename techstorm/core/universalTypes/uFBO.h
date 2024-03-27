#pragma once

#include <raylib.h>
#include "uDimension.h"
#include "../TechStormOptions.h"

namespace TechStorm {
	class uFBO {
	protected:
		uColor m_clearColor;
		RenderTexture m_FBO;
		bool m_isDrawing;

#ifdef ENGINE_3D
		bool m_isIn3DMode;
#else
		bool m_isIn2DMode;
#endif // ENGINE_3D
	public:

		uDimension fboDimensions;

		uFBO(uDimension dimensions) : m_clearColor(BLACK) {
			m_FBO = LoadRenderTexture(dimensions.x, dimensions.y);
			fboDimensions = dimensions;
		}

		uFBO() : m_clearColor(BLACK) {
			m_FBO = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
			fboDimensions = uDimension(GetScreenWidth(), GetScreenHeight());
		}

		virtual void updateDimensions(uDimension updatedDimensions) {
			this->m_FBO = LoadRenderTexture(updatedDimensions.x, updatedDimensions.y);
			fboDimensions = updatedDimensions;
		}

		void setClearColor(uColor color) {
			this->m_clearColor = color;
		}

		// start drawing mode
		virtual void startDraw()
		{
			BeginDrawing();
			DrawTextureRec(m_FBO.texture, Rectangle{ 0, 0, (float)(fboDimensions.x), (float)(-fboDimensions.y) }, Vector2{ 0, 0 }, WHITE);
		}

		// end draing move
		virtual void endDraw()
		{
			EndDrawing();
			
		}
#ifdef ENGINE_3D
		// start 3d drawing
		void start3D(Camera* camera)
		{
			BeginMode3D(*camera);
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
#endif // ENGINE_3D

		// start baking to fbo
		void startTexturing()
		{
			// StartDraw();
			BeginTextureMode(m_FBO);
			ClearBackground(m_clearColor);
		}

		// stop baking to fbo
		void stopTexturing()
		{
			// EndDraw();
			EndTextureMode();
			ClearBackground(m_clearColor);
		}

		virtual operator RenderTexture() const {
			return m_FBO;
		}
	};
}
