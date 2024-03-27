#pragma once
#include "../../Common.h"
#include "../universalTypes/uDimension.h"
#include "../universalTypes/uFBO.h"
#include "../TechStormGlobals.h"

namespace TechStorm {
	class Renderer abstract : public uFBO {
	private:

	public:
	};

	class PBRRenderer : public Renderer {
	public:
		Shader pbrShader = { 0 };
		Shader bloomShader = { 0 };

		PBRRenderer(uDimension dimensions) {
			this->fboDimensions = dimensions;
			this->m_FBO = LoadRenderTexture(dimensions.x, dimensions.y);
		}

		virtual void startDraw() override {
			uFBO::startDraw();
		}

		virtual void endDraw() override {
			EndShaderMode();
			uFBO::endDraw();
		}
	};
}
