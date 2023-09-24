#pragma once

#include "Request.h"

#include <string>

class PackagedRequest {
    public:
        std::string data;

        RequestType type;
};