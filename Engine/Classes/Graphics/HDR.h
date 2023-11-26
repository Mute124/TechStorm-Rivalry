#pragma once
#include "../../../lib/raylib.h"

#define MAX_HDR_FILE_NAME_LENGTH



class HDR {
    public:


    HDR(const char skyfile[MAX_HDR_FILE_NAME_LENGTH]) {
        panorama = LoadTexture(skyfile);
        
    }

    char skyboxFileName[MAX_HDR_FILE_NAME_LENGTH];

    Texture2D panorama;


    
};