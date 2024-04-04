#pragma once
#include "Common.h"

class Exporter
{
public:

	void createOutputFolder();

	void moveFolder(const char* folder);

	void moveContents(const char* folder);

	void checkForDuplicateZip();

	void moveFolders();

	void runTool();
};
