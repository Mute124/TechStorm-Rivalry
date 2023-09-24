#pragma once

#include "../../../lib/raylib.h"
#include <map>
#include <string>
#include <stdio.h>

using namespace std;

template<typename T>
class ShaderAttribute {
    public:

        ShaderLocationIndex loc;
        T value;
        ShaderUniformDataType type;
        const char *Uniformname;


};