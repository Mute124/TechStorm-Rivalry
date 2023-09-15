#include "Console.h"

void ConsoleGUI::Draw() const {

    if (m_triggerkey != NULL) {
        if (IsKeyDown(m_triggerkey) && !m_isopen) {
            DrawRectangle(GetMonitorHeight(GetCurrentMonitor()) - 10, GetMonitorHeight(GetCurrentMonitor()) - 10, this->m_width, this->m_height, GRAY);
            
    
        } else if (m_isopen) {
            DrawRectangle(GetMonitorHeight(GetCurrentMonitor()) - 10, GetMonitorHeight(GetCurrentMonitor()) - 10, this->m_width, this->m_height, GRAY);
            
        }
    } else if (m_triggerkey == NULL) {
        throw "TriggerKey not set. It cannot equal null";
    } else {
        throw "Error in console class. ";
    }
}

ConsoleGUI::ConsoleGUI(const int width, const int height, KeyboardKey Trigger) : m_width(width), m_height(height), m_triggerkey(Trigger), m_isopen(NULL)  {

}

void ConsoleGUI::OnUpdate() const {
    
}

void ConsoleGUI::SetTriggerKey(KeyboardKey key) const {
    
}

void ConsoleGUI::ParseInput(char *input) {

}