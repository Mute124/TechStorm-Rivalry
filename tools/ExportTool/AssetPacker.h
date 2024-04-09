#pragma once
#include <stdlib.h>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#define REQUISITE_PATH "../data/publishReqs.xml"
#define TEXTURES_CSV_FILE_NAME "textures.csv"
#include <raylib.h>
#include <raygui.h>
using namespace std;

//#include <stdio.h>
class AssetPacker
{
private:
	FilePathList m_assets;

	// Do not include the extension.
	void createCSVFile(std::string name, std::string dir) {
		std::ofstream csvFile(dir + "/" + name + ".csv");
		csvFile.close();
	}

	void populateCSVFile(string file, vector<string> extensions) {
		ofstream csvFile;
		csvFile.open(file + ".csv");
		vector<string> list;

		cout << "Populating CSV at " << file << endl;

		for (int i = 0; i < m_assets.count; i++) {
			bool assetDone = false;
			string assetExt = GetFileExtension(m_assets.paths[i]);
			for (string& ext : extensions) {
				if (assetDone) {
					continue;
				}
				else {
					if (assetExt == ext) {
						printf("Loading asset %s into %s\n", m_assets.paths[i], file.c_str());
						csvFile << m_assets.paths[i] << endl;

						assetDone = true;
					}
				}
			}
			assetDone = false;
		}
		csvFile.close();
	}

public:

	// Run the packer as if this is the resources folder.
	void run(std::string assetsLoc, std::string outputDirectory) {
		if (DirectoryExists(assetsLoc.c_str())
			&& DirectoryExists(outputDirectory.c_str())) {
			createCSVFile("textures", outputDirectory);

			cout << "Registering assets..." << std::endl;

			this->m_assets = LoadDirectoryFilesEx(assetsLoc.c_str(), NULL, true);
			populateCSVFile(outputDirectory + "/textures", { ".png" });
			populateCSVFile(outputDirectory + "/fonts", { "." });

			cout << "Done registering assets" << std::endl;
			UnloadDirectoryFiles(m_assets);
		}
		else {
			printf("No");
		}
	}

	// run the packer as if this is the data folder.
	void packDataDir(std::string assetsLoc, std::string outputDirectory) {
		if (DirectoryExists(assetsLoc.c_str())
			&& DirectoryExists(outputDirectory.c_str())) {
			createCSVFile("fonts", outputDirectory);
			createCSVFile("styles", outputDirectory);
			createCSVFile("tsp", outputDirectory);
			createCSVFile("tsr", outputDirectory);
			createCSVFile("dataImages", outputDirectory);
			createCSVFile("xml", outputDirectory);
			createCSVFile("toml", outputDirectory);

			cout << "Registering data assets..." << std::endl;

			this->m_assets = LoadDirectoryFilesEx(assetsLoc.c_str(), NULL, true);
			populateCSVFile(outputDirectory + "/dataImages", { ".png" });
			populateCSVFile(outputDirectory + "/fonts", { ".ttf" });
			populateCSVFile(outputDirectory + "/styles", { ".rgs" });
			populateCSVFile(outputDirectory + "/tsp", { ".tsp" });
			populateCSVFile(outputDirectory + "/tsr", { ".tsr" });
			populateCSVFile(outputDirectory + "/xml", { ".xml" });
			populateCSVFile(outputDirectory + "/toml", { ".toml" });

			cout << "Done registering data assets" << std::endl;
			UnloadDirectoryFiles(m_assets);
		}
		else {
			printf("No");
		}
	}
};
