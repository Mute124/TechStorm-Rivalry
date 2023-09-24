#pragma once
#include "../lib/raylib.h"

#include "../Requests/Request.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>



using namespace std;
class FxMan
{
    public:
        FxMan(bool isThreaded) : isThreaded(isThreaded)
        {
            if (isThreaded) {
                FxManLoop();
            }
        }

        static void FxManLoop() {
            while (!WindowShouldClose()) {
                
            }
        }
        
        template<typename T>
        static int ReceiveShipment() {
            
        }
        

    private:


        static void UnboxShipment(std::map<RequestType, T> **PackagedRequest) {

        }
    protected:
        const bool isThreaded;
};