
#pragma once
#include "Request.h"

#include <stdio.h>
#include <stdlib.h>
#include <map>


/*
 acts like a harbor, it takes all the packaged requests recieved from the factory, and ships it.
 Also will manage sending through threads. 
*/

template <typename T>
class PackageSenderDock
{
public:

    PackageSenderDock()
    {
    }

    

    // Ship data to the correct system manager
    static int ShipRequest(std::map<RequestTypes, T> PackagedRequest)
    {
        if (PackagedRequest[REQUEST_AUDIO] == 0)
        {

            return 0;
        }
        else if (PackagedRequest[REQUEST_GRAPHICS] == 0)
        {
            return 0;
        }
        else if (PackagedRequest[REQUEST_INPUT] == 0)
        {
            return 0;
        }
        else if (PackagedRequest[REQUEST_PHYSICS] == 0)
        {
            return 0;
        }
        else if (PackagedRequest[REQUEST_NETWORK] == 0)
        {
            return 0;
        }
        else if (PackagedRequest[REQUEST_ACTIONS] == 0)
        {
            return 0;
        }

        return 0;
    }
};