#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// NOTE: MSVC C++ compiler does not support compound literals (C99 feature)
// Plain structures in C++ (without constructors) can be initialized with { }
// This is called aggregate initialization (C++11 feature)
#if defined(__cplusplus)
#define CLITERAL(type)      type
#else
#define CLITERAL(type)      (type)
#endif

// Per parent element
#define MAX_CHILDREN_ELEMENTS 10

// 16 bit limit
#define MAX_LOADED_FILES 65536

// WIP
/*
-------------------------------------------------------------------------------------
|	C API																		    |
-------------------------------------------------------------------------------------
*/
#ifdef XML_C

// Some compilers (mostly macos clang) default to C++98,
// where aggregate initialization can't be used
// So, give a more clear error stating how to fix this
#if !defined(_MSC_VER) && (defined(__cplusplus) && __cplusplus < 201103L)
#error "C++11 or later is required. Add -std=c++11"
#endif

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

	typedef enum XMLDataTypes {
		XMLTYPE_NULL,
		XMLTYPE_INT,
		XMLTYPE_FLOAT,
		XMLTYPE_STR
	};

	typedef enum XMLFileType {
		XML_NULL,
		XML_GAME_ASSET,
		XML_CONFIG
	};

	typedef struct XMLFileInfo {
		const char* path;
		XMLFileType xmlType;
		bool isReady = false;
	};

	typedef struct XMLFile {
	};

#if defined(__cplusplus)
}
#endif
#endif

/*
-------------------------------------------------------------------------------------
|	C++ API 																		|
-------------------------------------------------------------------------------------
*/
#ifdef XML_CPP

using namespace tinyxml2;

typedef enum XMLDataTypes {
	XMLTYPE_NULL,
	XMLTYPE_INT,
	XMLTYPE_FLOAT,
	XMLTYPE_STR
};

typedef enum XMLFileType {
	XML_NULL,
	XML_GAME_ASSET,
	XML_CONFIG
};

typedef struct XMLFileInfo {
	const char* path;
	XMLFileType xmlType;
	bool isReady = false;
};

template<typename T>
struct XMLChildElement {
	T value;
	const int id;
	const char name;
};

template<typename T>
struct XMLFile {
	XMLDocument document;
	XMLElement* root;
	XMLFileInfo fileInfo;

	int mapSize;
	int vectorSize;

	std::map<const char*, T> fileMap = { 0 };
	std::vector<T*> fileVector = { 0 };

	int loadedCount = 0;
};

// Registers
template<typename T>
extern int Register();

template<typename T>
extern XMLFile<T> LoadFile(const char* path, XMLFileType type);

#endif
