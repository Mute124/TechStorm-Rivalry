#pragma once
#include "lib/raylib.h"
#include "Gui.h"

#include <stdio.h>

class ConsoleGUI : public GUI
{
public:
    void Draw() const override
    {
        if (m_triggerkey != NULL)
        {
            if (IsKeyDown(m_triggerkey) && !m_isopen)
            {
                DrawRectangle(GetMonitorHeight(GetCurrentMonitor()) - 10, GetMonitorHeight(GetCurrentMonitor()) - 10, this->m_width, this->m_height, GRAY);
            }
            else if (m_isopen)
            {
                DrawRectangle(GetMonitorHeight(GetCurrentMonitor()) - 10, GetMonitorHeight(GetCurrentMonitor()) - 10, this->m_width, this->m_height, GRAY);
            }
        }
        else if (m_triggerkey == NULL)
        {
            throw "TriggerKey not set. It cannot equal null";
        }
        else
        {
            throw "Error in console class. ";
        }
    }

    void OnUpdate() const override {}
    ConsoleGUI(const int width, const int height, KeyboardKey Trigger) : m_width(width), m_height(height), m_triggerkey(Trigger), m_isopen(NULL) {}

    void SetTriggerKey(KeyboardKey key) const override {}

    void ParseInput(char *input) {}

private:
    const int m_width;
    const int m_height;


    Camera3D CameratoUse;

    // Console guts
    bool m_isopen;



protected:
};