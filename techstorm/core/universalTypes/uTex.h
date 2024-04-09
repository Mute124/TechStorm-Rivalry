#pragma once
#include <raylib.h>
#include "uStr.h"
#include "uVec2.h"

namespace TechStorm {
	class uTex {
	protected:
		Texture mTexture;

	public:

		uTex(Texture& tex) : mTexture(tex) {}

		uTex(const Texture& tex) : mTexture(tex) {}

		uTex(Image& img) : mTexture(LoadTextureFromImage(img)) {}

		uTex(const Image& img) : mTexture(LoadTextureFromImage(img)) {}

		uTex(uStr path) : mTexture(LoadTexture(path)) {}

		uTex(const char* path) : mTexture(LoadTexture(path)) {}

		uTex(std::string path) : mTexture(LoadTexture(path.c_str())) {}

		virtual Texture& getTexture() {
			return mTexture;
		}

		virtual const Texture& getTexture() const {
			return mTexture;
		}

		virtual int& getFormat() {
			return mTexture.format;
		}

		virtual const int& getFormat() const {
			return mTexture.format;
		}

		virtual void unload() {
			UnloadTexture(mTexture);
		}

		virtual operator Texture() {
			return mTexture;
		}

		virtual operator Image() {
			return LoadImageFromTexture(mTexture);
		}

		virtual operator Texture2D() {
			return mTexture;
		}
	};
}
