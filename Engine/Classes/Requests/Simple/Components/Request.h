
#pragma once
#include <map>

#include "RequestTypes.h"

#include "../../../Logging/Logman.h"

// First a request is made by what ever, then it gets compiled into a map, packaged, and shipped to the correct system man
template <typename T>
class Request
{
public:
    T RequestData;
    RequestType type;
    bool isPackaged;
    int id;

    Request(RequestType type, T data)
    {
        id = AssignId();
        this->RequestData = data;
        this->type = type;
    };

    static void Flush() {
        RequestCount = 0;
    }

private:
    static inline int AssignId()
    {
        if (RequestCount == 0) {
            return 0;
        } else {
            return RequestCount++;
        }
    }
    static int RequestCount;
};
