#pragma once

#include "../../lib/raylib.h"

template <typename T>
class Component
{
public:
    Component(T Component) : comp(Component) {}



private:
    T comp;
};
