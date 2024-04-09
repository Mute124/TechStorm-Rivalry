#pragma once
#include <raylib.h>
#include "uStr.h"

#include "uVec3.h"

namespace TechStorm {
	class uShdr {
	protected:
		Shader mShdr;
	public:

		uShdr(uStr vertPath, uStr fragPath) : mShdr(LoadShader(vertPath, fragPath)) {}

		uShdr(const char* vertPath, const char* fragPath) : mShdr(LoadShader(vertPath, fragPath)) {}

		uShdr(std::string vertPath, std::string fragPath) : mShdr(LoadShader(vertPath.c_str(), fragPath.c_str())) {}

		uShdr(uShdr& other) : mShdr(other.mShdr) {}

		uShdr(Shader& other) : mShdr(other) {}

		virtual Shader& get() { return mShdr; }

		virtual unsigned int getID() { return mShdr.id; }

		static void unload(Shader& other) { UnloadShader(other); }

		virtual Shader& unload() { UnloadShader(mShdr); return mShdr; }

		virtual void load(const char* vertPath, const char* fragPath) { mShdr = LoadShader(vertPath, fragPath); }

		virtual void load(std::string vertPath, std::string fragPath) { mShdr = LoadShader(vertPath.c_str(), fragPath.c_str()); }

		virtual void load(uStr vertPath, uStr fragPath) { mShdr = LoadShader(vertPath, fragPath); }

		virtual void selfUnload() { UnloadShader(mShdr); }

		virtual void swap(uShdr& other) {
			this->mShdr = other.mShdr;

			other.mShdr = this->mShdr;
		}

		virtual void swap(Shader& other) {
			this->mShdr = other;

			other = this->mShdr;
		}

		virtual void use() { BeginShaderMode(mShdr); }

		static void use(Shader& other) { BeginShaderMode(other); }

		static void use(uShdr& other) { other.use(); }

		virtual void unuse() { EndShaderMode(); }

		static void unuse(uShdr& other) { other.unuse(); }

		// uniform settings

		// numbers
		virtual void setInt(const char* name, int value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value, SHADER_UNIFORM_INT); }

		virtual void setFloat(const char* name, float value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value, SHADER_UNIFORM_FLOAT); }

		// vectors
		virtual void setVec2(const char* name, const Vector2& value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value, SHADER_UNIFORM_VEC2); }

		virtual void setVec2(const char* name, float x, float y) {
			Vector2 vec = { x, y };
			SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &vec, SHADER_UNIFORM_VEC2);
		}

		virtual void setVec3(const char* name, const Vector3& value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value, SHADER_UNIFORM_VEC3); }

		virtual void setVec3(const char* name, Vector3& value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value, SHADER_UNIFORM_VEC3); }

		virtual void setVec3f(const char* name, uVec3f& value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value.operator Vector3(), SHADER_UNIFORM_VEC3); }

		virtual void setVec3i(const char* name, uVec3i& value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value.operator Vector3(), SHADER_UNIFORM_VEC3); }

		virtual void setVec3(const char* name, float x, float y, float z) {
			Vector3 vec = { x, y, z };
			SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &vec, SHADER_UNIFORM_VEC3);
		}

		virtual void setVec4(const char* name, const Vector4& value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value, SHADER_UNIFORM_VEC4); }

		virtual void setVec4(const char* name, float x, float y, float z, float w) {
			Vector4 vec = { x, y, z, w };
			SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &vec, SHADER_UNIFORM_VEC4);
		}

		virtual void setColor(const char* name, const Color& value) {
			Color col = { value.r, value.g, value.b, value.a };
			SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &col, SHADER_UNIFORM_VEC4);
		}

		virtual void setColor(const char* name, float r, float g, float b, float a) {
			Color col = { r, g, b, a };
			SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &col, SHADER_UNIFORM_VEC4);
		}

		virtual void setMat(const char* name, const Matrix& value) { SetShaderValueMatrix(mShdr, GetShaderLocation(mShdr, name), value); }

		virtual void setSampler(const char* name, const Texture& value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value, SHADER_UNIFORM_SAMPLER2D); }

		virtual void setSampler(const char* name, const Texture2D& value) { SetShaderValue(mShdr, GetShaderLocation(mShdr, name), &value, SHADER_UNIFORM_SAMPLER2D); }

		virtual void setTexture(const char* name, const Texture& value) { SetShaderValueTexture(mShdr, GetShaderLocation(mShdr, name), value); }

		virtual void setTexture(const char* name, const Texture2D& value) { SetShaderValueTexture(mShdr, GetShaderLocation(mShdr, name), value); }

		~uShdr() { UnloadShader(mShdr); }
	};
}
