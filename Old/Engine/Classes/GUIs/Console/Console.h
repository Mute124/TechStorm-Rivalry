#pragma once

#include "../../Logging/Logman.h"

#include <stdio.h>


class ConsoleGUI 
{
public:

    ConsoleGUI(bool AlwaysOpen = false) {


        if (enabled) {
            active = AlwaysOpen;
        }        
    }

    void ConsoleUpdate() {
        if(enabled){
            if (!active) {
                shouldClose = true;
            } 

            if (sizeof(commandBuffer) < bufferSize) {
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (commandBufferCursor > 0) {
                        commandBufferCursor--;
                        commandBuffer[commandBufferCursor] = '\0';
                    }
                }

                UpdateBuffer();

                if (DEBUGMODE) {
                    Logman::Log(commandBuffer);
                }
            }

        }

    }

    void SwitchMode() {
        active = !active;
    }

private:

    // gets input;
    void UpdateBuffer() {
        int pressedkey = GetCharPressed();

        if(pressedkey == KEY_NULL) {
            
        } else {
            commandBuffer[commandBufferCursor] = pressedkey;
            commandBufferCursor++;


        }
    }

    char *commandBuffer;
    int bufferSize = 256;
    int commandBufferCursor; // position in the buffer

    bool active = false; // is it active?
    bool enabled = true; // Is the console allowed to be opened
    bool shouldClose = false; // Should this close

    const bool DEBUGMODE = true;
    

};