#pragma once
#include "../../../lib/raylib.h"

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
            } else {
                
            }
        }

        static void FxManLoop() {
            while (!WindowShouldClose()) {
                if (IsAudioDeviceReady()) {
                    PlayAudioStream(ambiance);
                }
            }
        }
        
        void AddAmbiance(Music music) {
            ambiance.buffer[nextAudioSlot] = music;

            nextAudioSlot += 1;
        }

        




    private:
        AudioStream ambiance;

        int nextAudioSlot = 0;


    protected:
        const bool isThreaded;
};