#pragma once
#include <raylib.h>
#include <string>
class TextFile {
public:
	const char* filePath;

	TextFile(const char* dst) {
		SaveFileText(dst, NULL);
	}

	~TextFile() {
		UnloadFileText((char*)filePath);
	}

	void Append(const char* txt) {
		SaveFileText(this->filePath, (char*)txt);
	}

	std::string Read() {
		return LoadFileText(this->filePath);
	}
};
