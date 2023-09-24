#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../../../../DataSets/FactoryTaskType.h"
#include "Request.h"
#include "PackagedRequest.h"

template <typename T>
class RequestPackagingFactory
{
public:
    virtual void ProcessRequest(Request<T> *request, FactoryTaskType task)
    {
        switch (task)
        {
        case TASK_BOX:
            BoxPackage(request);
            break;
        case TASK_UNBOX:
            UnboxPackage();
            break;
        default:
            break;
        }
    }

    virtual PackagedRequest *BoxPackage(Request<T> *request)
    {
        PackagedRequest *Package;
        Package.data = EncodeDataBase64(request->RequestData, sizeof(request->RequestData));
        Package.type = request->type;
        return Package;
    }

     Request<T> UnboxPackage(PackagedRequest PackagedRequest)
    {
        Request unboxedrequest;
        unboxedrequest.type = PackagedRequest.type;
        unboxedrequest.data = DecodeDataBase64(PackagedRequest.data);

    }

private:
};