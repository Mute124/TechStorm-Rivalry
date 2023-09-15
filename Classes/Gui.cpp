#include "Gui.h"

void GUI::SetTriggerKey(KeyboardKey key) const {}

void GUI::SetPosition(Vector2 position)
{
    this->position = position;
}

void GUI::SetGUISize(int Width, int Height)
{
    this->width = Width;
    this->height = Height;
}

void GUI::Draw() const {}
