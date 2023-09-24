#pragma once


template<typename T>
struct File
{
    T Data;
    const char *File; // full path to file.
    bool isLoaded;
};
