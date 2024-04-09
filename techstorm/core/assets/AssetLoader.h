#pragma once
#include "../errorHandling/TechStormException.h"
#include "../logging/Logman.h"
#include "Asset.h"
#include <tinyxml2.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
namespace TechStorm {
	class AssetLoader {
	private:

		static inline std::map<const char*, Sound> m_sounds;
		static inline std::map<const char*, Model> m_models;
		static inline std::map<const char*, Material> m_materials;
		static inline std::map<const char*, Image> m_images;
		static inline std::map<const char*, Texture2D> m_textures;
		static inline std::map<const char*, Music> m_music;
		static inline std::map<const char*, Font> m_fonts;
		static inline std::map<const char*, Shader> m_shaders;

		// holds whether or not a certain extension has been set as supported. This prevents having to check support each time
		//std::map<std::string, bool> m_checkedExtensions;

		//static inline std::vector<std::string>* m_acceptableExtensions = new std::vector<std::string>(); // serves as a dictionary in case support is unknown

		const char* m_createFilePath(const char* folder, const char* file) {
			return TextFormat("%s/%s", folder, file);
		}

		void loadShaders(const char* path) {
			using namespace tinyxml2;

			XMLDocument doc;
			doc.LoadFile(path);

			XMLElement* root = doc.RootElement();
			if (NULL != root) {
				XMLElement* shaders = root->FirstChildElement("shaders");

				if (NULL != shaders) {
					XMLElement* shader = shaders->FirstChildElement("shader");

					while (shader) {
						XMLElement* fs = shader->FirstChildElement("fs");
						XMLElement* vs = shader->FirstChildElement("vs");
						XMLElement* nameElm = shader->FirstChildElement("name");

						const char* name = nameElm->GetText();
						const char* fsPath = TextFormat("resources/shaders/%s.fs", fs->GetText());
						const char* vsPath = TextFormat("resources/shaders/%s.vs", vs->GetText());

						m_shaders[name] = LoadShader(vsPath, fsPath);
						shader = shaders->NextSiblingElement("shader");
					}
				}
			}
		}

		/*
		* 		void m_loadSupportedFileTypesList(const char* engineDataPath) {
					using namespace tinyxml2;

					if (DirectoryExists(engineDataPath)) {
						const char* filetypesPath = "data/techstorm/filetypesupport.tsp"
							if (FileExists(filetypesPath)) {
								XMLDocument doc;

								doc.LoadFile(filetypesPath);

								XMLElement* root = doc.RootElement();

								Logman::Log("Loading supported file extensions into dictionary...");
								if (NULL != root) {
									XMLElement* elements = root->FirstChildElement("types");

									if (NULL != elements) {
										XMLElement* element = elements->FirstChildElement("type");

										while (element) {
											const char* extension = element->Attribute("ext");
											bool isEnabled = element->BoolText();

											if (isEnabled) {
												m_acceptableExtensions->push_back(extension);
											}

											Logman::Log(TextFormat("Extension of (%s) : %i", extension, isEnabled));

											//m_checkedExtensions[extension] = isEnabled;
											element = element->NextSiblingElement("type");
										}
									}
								}
								Logman::Log("Loaded supported file extensions into dictionary.");
							}
							else {

								//throw new EngineException("Cannot find filetypesupport.tsp, of which is needed for asset loading!", ESEVERITY_HIGH);
							}
					}
					else {

						//throw new EngineException("Cannot find Techstorm's data folder!", ESEVERITY_HIGH);
					}
				}

		*/

		void m_init(const char* assetPath, const char* dataPath) {
			if (DirectoryExists(dataPath)) {

				//this->m_loadSupportedFileTypesList(TextFormat("%s/techstorm/", dataPath));
				if (DirectoryExists(assetPath)) {
					FilePathList assets = LoadDirectoryFilesEx(assetPath, NULL, true);

					Logman::Log(TextFormat("Loading a total of %i files...", assets.count));

					//bool ispng = false;
					int textureCount = 0;

					if (assets.count <= assets.capacity) {
						bool isSupported = false;
						for (int i = 0; i < assets.count; i++) {
							const char* extension = GetFileExtension(assets.paths[i]);
							const char* fileName = GetFileNameWithoutExt(assets.paths[i]);
							Logman::Log(TextFormat("Loading file at %s", assets.paths[i]));

							//for (std::string& ext : *m_acceptableExtensions) {
							if (IsFileExtension(assets.paths[i], ".png")) {
								m_textures[fileName] = LoadTexture(assets.paths[i]);
								textureCount++;
							}
							if (IsFileExtension(assets.paths[i], ".jpg") || IsFileExtension(assets.paths[i], ".jpeg")) {
								m_images[fileName] = LoadImage(assets.paths[i]);
								textureCount++;
							}
							if (IsFileExtension(assets.paths[i], ".mp3")) {
								m_sounds[fileName] = LoadSound(assets.paths[i]);
								m_music[fileName] = LoadMusicStream(assets.paths[i]);
							}

							if (IsFileExtension(assets.paths[i], ".glb")) {
								m_models[fileName] = LoadModel(assets.paths[i]);
							}

							if (IsFileExtension(assets.paths[i], ".shdr")) {
								loadShaders(assets.paths[i]);
							}
						}
					}
					UnloadDirectoryFiles(assets);
				}
				else {

					//throw new TechStorm::EngineException(TextFormat("Cannot load assets as the file count(%i) has exceeded the maximum(%i)", assets.count, assets.capacity), ESEVERITY_HIGH);
				}
			}
			else {

				//throw new TechStorm::EngineException(TextFormat("The directory %s does not exist and the Asset Loader cannot run!", assetPath), ESEVERITY_HIGH);
			}
		}

	public:

		bool doneLoading = false;

		void LoadAssets(const char* assetPath, const char* dataPath) {
			this->m_init(assetPath, dataPath);
			doneLoading = true;
		}

		void loadCSVFiles(const char* loc) {
		}

		void unloadAssets() {
			for (auto& sound : m_sounds) {
				UnloadSound(sound.second);
			}

			for (auto& model : m_models) {
				UnloadModel(model.second);
			}

			for (auto& material : m_materials) {
				UnloadMaterial(material.second);
			}

			for (auto& img : m_images) {
				UnloadImage(img.second);
			}

			for (auto& tex : m_textures) {
				UnloadTexture(tex.second);
			}

			for (auto& music : m_music) {
				UnloadMusicStream(music.second);
			}
			for (auto& font : m_fonts) {
				UnloadFont(font.second);
			}

			for (auto& shdr : m_shaders) {
				UnloadShader(shdr.second);
			}
		}

		AssetLoader() {
		}

		static inline Sound getSound(const char* sound) {
			return m_sounds[sound];
		}

		static inline Texture getTexture(const char* texture) {
			return m_textures[texture];
		}

		static inline Image getImage(const char* img) {
			return m_images[img];
		}
	};
}
