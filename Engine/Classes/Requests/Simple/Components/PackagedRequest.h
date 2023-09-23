#pragma once

#include "Request.h"

template<typename T>
class PackagedRequest {
    public:
        
        const Request<T> request;
};