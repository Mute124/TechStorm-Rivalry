#pragma once
#include "IScriptable.h"
#include <tinyxml2.h>

using namespace tinyxml2;

class AfflictionManager : public IScriptable {
    AfflictionManager(const char *file) {
        XMLDocument doc;
        doc.LoadFile(file);

        
    }


};

