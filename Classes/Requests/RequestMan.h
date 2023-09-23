
/*

    This class is "control tower" of the request system, it keeps track of shipping and what not.
    Packaging process goes like this :

        Request is made by what ever and once filled, it is sent to RequestPackageFactory Class to process 
        the request, then that is sent to a package dock of the correct type, then is sent to the correct
        system's dock to then be unboxed and processed/executed.

        
    

*/
#pragma once

#include "../lib/raylib.h"

#include "Simple/Components/Request.h"
#include "Simple/Components/PackageDock.h"
#include "Simple/Components/RequestTypes.h"
#include "Simple/Components/RequestPackageFactory.h"


// THIS CLASS IS THREADED! This is the request system. If threading is not wanted, it can be turned off
class RequestMan {
    public:
        RequestMan(const bool isThreaded) {
            if (isThreaded) {
                RequestManLoop();
            }
        }

        static void RequestManLoop() {
            while (!WindowShouldClose()) {
                
            }
        }

        
    private:

};