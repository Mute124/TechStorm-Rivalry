#pragma once

#include <stdio.h>
#include <stdlib.h>

template<typename T>
class RequestPackagingFactory {
    public:
        RequestPackagingFactory() {}

        
        void ProcessRequest(std::map<RequestTypes, T> *Request) {
           
        }
        
    private:
        void BoxPackage() {}
};