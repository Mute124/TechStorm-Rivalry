#pragma once


template<typename T>
struct File
{
    T Data;
    const char *FilePath; // full path to file.
    bool isLoaded;
};
