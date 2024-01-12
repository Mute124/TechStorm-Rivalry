/*******************************************************************************************
*
*   Options v1.0.0 - Tool Description
*
*   MODULE USAGE:
*       #define GUI_OPTIONS_IMPLEMENTATION
*       #include "gui_Options.h"
*
*       INIT: GuiOptionsState state = InitGuiOptions();
*       DRAW: GuiOptions(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 MutedTea. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "../../build/_deps/raylib-src/src/raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "../raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_OPTIONS_H
#define GUI_OPTIONS_H

typedef struct {
    // Define anchors
    Vector2 anchor01;            // ANCHOR ID:1
    
    // Define controls variables
    bool WindowBox000Active;            // WindowBox: WindowBox000

    // Define rectangles
    Rectangle layoutRecs[4];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiOptionsState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiOptionsState InitGuiOptions(void);
void GuiOptions(GuiOptionsState *state);
static void Button001();                // Button: Button001 logic
static void Button002();                // Button: Button002 logic
static void Button003();                // Button: Button003 logic

#ifdef __cplusplus
}
#endif

#endif // GUI_OPTIONS_H

/***********************************************************************************
*
*   GUI_OPTIONS IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_OPTIONS_IMPLEMENTATION)

#include "../raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiOptionsState InitGuiOptions(void)
{
    GuiOptionsState state = { 0 };

    // Init anchors
    state.anchor01 = Vector2{ 0, 0 };            // ANCHOR ID:1
    
    // Initilize controls variables
    state.WindowBox000Active = true;            // WindowBox: WindowBox000

    // Init controls rectangles
    state.layoutRecs[0] = Rectangle{ state.anchor01.x + 0, state.anchor01.y + 0, 240, 240 };// WindowBox: WindowBox000
    state.layoutRecs[1] = Rectangle{ state.anchor01.x + 64, state.anchor01.y + 56, 120, 24 };// Button: Button001
    state.layoutRecs[2] = Rectangle{ state.anchor01.x + 64, state.anchor01.y + 112, 120, 24 };// Button: Button002
    state.layoutRecs[3] = Rectangle{ state.anchor01.x + 64, state.anchor01.y + 168, 120, 24 };// Button: Button003

    // Custom variables initialization

    return state;
}
// Button: Button001 logic
static void Button001()
{
    // TODO: Implement control logic
}
// Button: Button002 logic
static void Button002()
{
    // TODO: Implement control logic
}
// Button: Button003 logic
static void Button003()
{
    // TODO: Implement control logic
}


void GuiOptions(GuiOptionsState *state)
{
    // Const text
    const char *WindowBox000Text = "Options";    // WINDOWBOX: WindowBox000
    const char *Button001Text = "Game";    // BUTTON: Button001
    const char *Button002Text = "Audio";    // BUTTON: Button002
    const char *Button003Text = "Video";    // BUTTON: Button003
    
    // Draw controls
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], WindowBox000Text);
        if (GuiButton(state->layoutRecs[1], Button001Text)) Button001(); 
        if (GuiButton(state->layoutRecs[2], Button002Text)) Button002(); 
        if (GuiButton(state->layoutRecs[3], Button003Text)) Button003(); 
    }
}

#endif // GUI_OPTIONS_IMPLEMENTATION
