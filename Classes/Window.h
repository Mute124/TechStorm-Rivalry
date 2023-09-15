#pragma once
#include "lib/raylib.h"
#include <stdio.h>


#include <stdlib.h>
#include <thread>
#include "Monitor.h"
#include "MonoBehavior.h"



using namespace std;
class Window {
    public:

        Window(int width, int Height, const char *Title) : WIDTH(width), HEIGHT(Height), Title(Title) {
            if (sizeof(Title) > MAX_WINDOW_TITLE_LENGTH) {
                throw std::runtime_error("Title is too long");
            } else {
                this->Run(WIDTH, HEIGHT, Title);
            }
            
        };

    

        ~Window() {
            delete DrawingMonitor;
            delete this;
        };

        static void Run(const int WIDTH, const int HEIGHT, const char *Title) {
            
        };


        Vector2 GetMiddlePoint() {
            return (Vector2){this->WIDTH/2, this->HEIGHT/2};
        }


    private:

        Monitor *DrawingMonitor = new Monitor();

        Global::Tag tag;

        const int WIDTH = 800;
        const int HEIGHT = 600;
        const char *Title = new char[MAX_WINDOW_TITLE_LENGTH]; //TODO : VERY unsafe, there needs to be safeguards put in place

        

};