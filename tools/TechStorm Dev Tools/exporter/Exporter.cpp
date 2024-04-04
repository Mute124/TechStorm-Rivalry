#include "exporter.h"

inline void Exporter::createOutputFolder() {
	if (!DirectoryExists("output")) {
		system("mkdir output");
	}
}

inline void Exporter::moveFolder(const char* folder) {

	// go to the main folder.

	printf("moving folder...");
	system(TextFormat("Mover.bat %s output", folder));
}

inline void Exporter::moveContents(const char* folder) {
	printf("moving folder...");
	system(TextFormat("ContentsMover.bat %s output", folder));
}

inline void Exporter::checkForDuplicateZip() {
	if (FileExists("publish.zip")) {
		system("del publish.zip");
		system("zipper.bat output");
	}
	else {
		printf("packaging game...\n");
		system("zipper.bat output");
	}
}

inline void Exporter::moveFolders() {
	using namespace tinyxml2;
	XMLDocument doc;

	doc.LoadFile(REQUISITE_PATH);

	XMLElement* root = doc.RootElement();

	if (NULL != root) {
		XMLElement* reqs = root->FirstChildElement("reqs");
		if (NULL != reqs) {
			XMLElement* folders = reqs->FirstChildElement("folders");

			if (NULL != folders) {
				XMLElement* folder = folders->FirstChildElement("folder");

				while (folder) {
					moveFolder(folder->GetText());
					folder = folder->NextSiblingElement("folder");
				}
			}

			XMLElement* foldersContents = reqs->FirstChildElement("folderContents");

			if (NULL != foldersContents) {
				XMLElement* folderContent = foldersContents->FirstChildElement("folder");

				while (folderContent) {
					moveContents(folderContent->GetText());
					folderContent = folderContent->NextSiblingElement("folder");
				}
			}
		}
	}

	checkForDuplicateZip();
}

inline void Exporter::runTool() {

	// make sure the output directory doesnt exist.
	if (DirectoryExists("output")) {
		system("rmdir output");
	}

	createOutputFolder();
	moveFolders();
}
