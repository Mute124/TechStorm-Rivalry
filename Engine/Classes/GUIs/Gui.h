#pragma once
#include "lib/raylib.h"

typedef enum types
{
    HOTBAR = 0,
    MAINMENU,
    CONSOLE

};
// broad class for GUIs
class GUI
{
public:
    virtual void Draw() const = 0;

    virtual void OnUpdate() const = 0;

    virtual ~GUI() {}

    virtual void SetTriggerKey(KeyboardKey key) const = 0;

    virtual void SetGUISize(int Width, int Height)
    {
        width = Width;
        height = Height;
    }

    virtual void SetPosition(Vector2 position)
    {

        position = position;
    }

private:
    KeyboardKey triggerkey;
    int width;        // width of GUI window
    int height;       // height of GUI window
    Vector2 position; // position on screen
    bool is_open;     // variable to store if the screen is open
    Color background; // what color the background of the GUI should be, it will be all the way on the back
};