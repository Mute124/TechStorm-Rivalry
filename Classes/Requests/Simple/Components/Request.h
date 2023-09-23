#pragma once
#include <map>

#include "RequestTypes.h"


// First a request is made by what ever, then it gets compiled into a map, packaged, and shipped to the correct system man
template <typename T>
class Request
{
public:
    


    // String is the type of said request, T is the data of the request.
    std::map<RequestTypes, T> RequestData;

    bool isPackaged;
    
    Request(RequestTypes type, T data) {

        this->RequestData[type] = data;

        ShipRequest(this->RequestData);
    };

    

    
};
