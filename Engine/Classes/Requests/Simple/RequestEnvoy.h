// this is to be used as something implemented into classes, this just communicates with RequestMan class

#pragma once
#include "Components/Request.h"
#include "Components/RequestTypes.h"


class RequestEnvoy 
{
public:
    RequestEnvoy() {

    }
    
    template <typename T>
    void PlaceRequest(Request<T> request, RequestType type) {
        
    }
private:

};
