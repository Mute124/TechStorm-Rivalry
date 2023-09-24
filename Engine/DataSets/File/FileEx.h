#pragma once



typedef enum StdFileTypes {
    FILETYPE_UNKNOWN,
    FILETYPE_TEXT,
    FILETYPE_BINARY,
    FILETYPE_IMAGE
};


typedef struct FileEx {
    StdFileTypes filetype;
    const char *File; // full path to file.
    bool isLoaded;
};