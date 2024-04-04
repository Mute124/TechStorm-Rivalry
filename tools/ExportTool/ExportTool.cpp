#include "AssetPacker.h"

int main() {
	AssetPacker* packer = new AssetPacker();
	packer->run("../../resources", "output");

	// we also want to package the data folder. For this, we use the PackDataDir function, same thing as the run func, but less is created.
	packer->packDataDir("../../data", "output");

	//printf(GetWorkingDirectory());
	printf("\nAll tasks have been completed... Goodbye!\n");
	return 0;
}
