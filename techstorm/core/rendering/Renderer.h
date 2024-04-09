#pragma once
#include "../../Common.h"
#include <raylib.h>
#include <rlgl.h>
#include "../universalTypes/uDimension.h"
#include "../universalTypes/uFBO.h"
#include "../TechStormGlobals.h"
#include "../registry/Registry.h"
#include "../ui/UIMan.h"

namespace TechStorm {
	class Renderer : public uFBO, public UIMan, public GameobjectManager {
	private:

	public:
		static inline int pbrShdrLoc;
		static inline int bloomShdrLoc;
		static inline int lightsCount;
	};

	// PBR related crap is in here. You can get locations here aswell.
	class PBRRenderer : public Renderer {
	public:
		static inline float ambientIntensity;
		static inline Color ambientColor;
		static inline Vector3 ambientColorNormalized;
		static inline int lightCountLoc;
		static inline int emissiveIntensityLoc;
		static inline int emissiveColorLoc;
		static inline int textureTilingLoc;
		static inline Shader pbrShader = { 0 };

		void initPBR(uDimension dimensions) {
			this->m_FBO = LoadRenderTexture(dimensions.x, dimensions.y);
			this->fboDimensions = dimensions;
			this->initUIMan();
			this->m_initPBR();

			this->setClearColor(BLACK);
		}

		RenderTexture& getFBO() {
			return this->m_FBO;
		}

		void startTexturingStep(Camera* camera) {
			m_updateRenderer(camera);

			startTexturing();
		}

		void endTexturingStep() {
			endTexturing();

			rlPopMatrix();
		}

		void startRenderingStep(Camera camera) {
			start3D(camera);
		}

		void endRenderingStep() {
			end3D();
		}

		void startDrawingstep() {
			startDraw();
			DrawFPS(100, 100);
		}

		void endDrawingStep() {
			endDraw();
		}

		void destruct() {
			flushBuffer();
			flushUI();
		}

		static inline void reload() {

			// Load the shader into memory
			pbrShader = LoadShader(TextFormat("resources/shaders/glsl330/pbr.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl330/pbr.fs", GLSL_VERSION));

			// Get shader locations
			pbrShader.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(pbrShader, "albedoMap");

			// WARNING: Metalness, roughness, and ambient occlusion are all packed into a MRA texture They
			// are passed as to the SHADER_LOC_MAP_METALNESS location for convenience, shader already takes
			// care of it accordingly
			pbrShader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(pbrShader, "mraMap");
			pbrShader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(pbrShader, "normalMap");

			// WARNING: Similar to the MRA map, the emissive map packs different information into a single
			// texture: it stores height and emission data It is binded to SHADER_LOC_MAP_EMISSION location
			// an properly processed on shader
			pbrShader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(pbrShader, "emissiveMap");
			pbrShader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(pbrShader, "albedoColor");

			// Setup additional required shader locations, including lights data
			pbrShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(pbrShader, "viewPos");
			lightCountLoc = GetShaderLocation(pbrShader, "numOfLights");

			// set it to the value of the MAX_LIGHTS macro and pass it to the shader
			int maxLightCount = MAX_LIGHTS;
			SetShaderValue(pbrShader, lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

			// Setup ambient color and intensity (brightness) parameters
			ambientIntensity = 0.02f;
			ambientColor = GRAY;
			ambientColorNormalized = Vector3{ ambientColor.r / 255.0f, ambientColor.g / 255.0f, ambientColor.b / 255.0f };
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "ambientColor"), &ambientColorNormalized, SHADER_UNIFORM_VEC3);
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "ambient"), &ambientIntensity, SHADER_UNIFORM_FLOAT);

			// Get location for shader parameters that can be modified
			emissiveIntensityLoc = GetShaderLocation(pbrShader, "emissivePower");
			emissiveColorLoc = GetShaderLocation(pbrShader, "emissiveColor");
			textureTilingLoc = GetShaderLocation(pbrShader, "tiling");

			// Assignment of shaders
			// NOTE: By default, the texture maps are always used
			int usage = 1;
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "useTexAlbedo"), &usage, SHADER_UNIFORM_INT);
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "useTexNormal"), &usage, SHADER_UNIFORM_INT);
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "useTexMRA"), &usage, SHADER_UNIFORM_INT);
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "useTexEmissive"), &usage, SHADER_UNIFORM_INT);

			float brightness = 10.0f;
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "brightness"), &brightness, SHADER_UNIFORM_FLOAT);
		}

	private:

		void m_updateRenderer(Camera* camera) {
			if (IsKeyPressed(KEY_F9))
			{
				// take a screenshot
				for (int i = 0; i < INT_MAX; i++)
				{
					const char* fileName = TextFormat("screenshots/screen%i.screenshot", i);

					// if there isnt a duplicate file, it then will create a screenshot.
					if (FileExists(fileName) == 0)
					{
						std::ofstream outfile(fileName);

						outfile.close();
						ExportImage(LoadImageFromTexture(this->operator RenderTexture().texture), fileName);

						break;
					}
				}
			}

			// Where the player's camera is. We need to have this as a float array for the shader
			float cameraPos[3] =
			{
				camera->position.x,
				camera->position.y,
				camera->position.z
			};

			SetShaderValue(pbrShader, pbrShader.locs[SHADER_LOC_VECTOR_VIEW], &cameraPos, SHADER_UNIFORM_VEC3);

			GameobjectManager::updateObjects();
		}

		void m_initPBR() {

			// Load the shader into memory
			pbrShader = LoadShader(TextFormat("resources/shaders/glsl330/pbr.vs", GLSL_VERSION), TextFormat("resources/shaders/glsl330/pbr.fs", GLSL_VERSION));

			// Get shader locations
			pbrShader.locs[SHADER_LOC_MAP_ALBEDO] = GetShaderLocation(pbrShader, "albedoMap");

			// WARNING: Metalness, roughness, and ambient occlusion are all packed into a MRA texture They
			// are passed as to the SHADER_LOC_MAP_METALNESS location for convenience, shader already takes
			// care of it accordingly
			pbrShader.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(pbrShader, "mraMap");
			pbrShader.locs[SHADER_LOC_MAP_NORMAL] = GetShaderLocation(pbrShader, "normalMap");

			// WARNING: Similar to the MRA map, the emissive map packs different information into a single
			// texture: it stores height and emission data It is binded to SHADER_LOC_MAP_EMISSION location
			// an properly processed on shader
			pbrShader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(pbrShader, "emissiveMap");
			pbrShader.locs[SHADER_LOC_COLOR_DIFFUSE] = GetShaderLocation(pbrShader, "albedoColor");

			// Setup additional required shader locations, including lights data
			pbrShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(pbrShader, "viewPos");
			lightCountLoc = GetShaderLocation(pbrShader, "numOfLights");

			// set it to the value of the MAX_LIGHTS macro and pass it to the shader
			int maxLightCount = MAX_LIGHTS;
			SetShaderValue(pbrShader, lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

			// Setup ambient color and intensity (brightness) parameters
			ambientIntensity = 0.02f;
			ambientColor = GRAY;
			ambientColorNormalized = Vector3{ ambientColor.r / 255.0f, ambientColor.g / 255.0f, ambientColor.b / 255.0f };
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "ambientColor"), &ambientColorNormalized, SHADER_UNIFORM_VEC3);
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "ambient"), &ambientIntensity, SHADER_UNIFORM_FLOAT);

			// Get location for shader parameters that can be modified
			emissiveIntensityLoc = GetShaderLocation(pbrShader, "emissivePower");
			emissiveColorLoc = GetShaderLocation(pbrShader, "emissiveColor");
			textureTilingLoc = GetShaderLocation(pbrShader, "tiling");

			// Assignment of shaders
			// NOTE: By default, the texture maps are always used
			int usage = 1;
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "useTexAlbedo"), &usage, SHADER_UNIFORM_INT);
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "useTexNormal"), &usage, SHADER_UNIFORM_INT);
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "useTexMRA"), &usage, SHADER_UNIFORM_INT);
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "useTexEmissive"), &usage, SHADER_UNIFORM_INT);

			float brightness = 2.0f;
			SetShaderValue(pbrShader, GetShaderLocation(pbrShader, "brightness"), &brightness, UNIFORM_FLOAT);
		}
	};
}
