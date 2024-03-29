#include <tinyxml2.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <exception>
#define REQUISITE_PATH "../data/publishReqs.xml"

int system(const char* command);

void createOutputFolder() {
	if (!DirectoryExists("output")) {
		system("mkdir output");
	}
}

void moveFolder(const char* folder) {

	// go to the main folder.

	printf("moving folder...");
	system(TextFormat("Mover.bat %s output", folder));
}

void moveContents(const char* folder) {
	printf("moving folder...");
	system(TextFormat("ContentsMover.bat %s output", folder));
}

void checkForDuplicateZip() {
	if (FileExists("publish.zip")) {
		system("del publish.zip");
		system("zipper.bat output");
	}
	else {
		printf("packaging game...\n");
		system("zipper.bat output");
	}
}

void moveFolders() {
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

int main() {
	try
	{
		createOutputFolder();
		moveFolders();
	}
	catch (const std::exception& e)
	{
		printf(e.what());
	}

	printf("\nAll tasks have been completed... Goodbye!\n");
}
