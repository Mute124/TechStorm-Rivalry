#pragma once
#include <map>
#include "RequestTypes.h"

template <typename T>
class RawRequest
{
private:
    std::map<T> RequestData;
public:
    RawRequest(std::map<RequestType, T> requestdata) : RequestData(requestdata) {};
};
