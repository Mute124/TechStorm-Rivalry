#pragma once
/*

    The ButtonR class creates a rectangle-shaped static-size button, window-resized-not-responsive button.

    The button size is computed from the font size and length of the text;
    the text is automatically centered on the button.
    See mutators to modify the button’s position, the text’s position in the button, and the button’s size.

    The button's border can be turned on and off.
    the border's size is computed from the font size and length of the text;
    modifying the button's size will also modify the border's size.

    The button's shadow can be turned on and off.
    The shadow size is computed from the font size and length of the text;
    modifying the button's size will also modify the shadow's size.

    The default font is raylib font.

    Parent class to the ButtonO class

    Requirement
    c and c++ 20 or later
    Raylib library: https://www.raylib.com

*/

#ifndef BUTTON_R_HPP
#define BUTTON_R_HPP

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER


#include "Common.h"

#include <string>

#include <vector>

using namespace std;

class ButtonR
{

public:
    Font font = GetFontDefault();
    float fontSize = 32,
        fontSpacing = 3.0f;
    Color fontColor = BLACK;
    bool isRayFont = true;

    //---- Text
    string text = "Button";
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, fontSpacing),
        oneCharSize = MeasureTextEx(font, "C", fontSize, fontSpacing);

    //--- Button position, size, color
    /*
        The button size is computed from the font size and length of the text
        See mutators to modify the button’s position,
        the text’s position in the button, and the button’s size.
    */
    bool txtResizeBtn = true;
    float btnWidth = (textSize.x + 3.5f * oneCharSize.x),
        btnHeight = textSize.y * (float)(2.0f * (textSize.y / fontSize));
    Rectangle rect = { 100, 100, btnWidth, btnHeight };

    // colors
    Color btnLiveColor = { 222, 214, 202, 255 },
        // Botton state
        btnHover = { 135, 195, 74, 100 },
        btnPressed = { 66, 165, 245, 100 },
        btnIdle = btnLiveColor; // idle state

    //---- Button border  position, size, color, thickness
    /*
        The boder size is computed from the font size and length of the text
        modifying the button's size, we also modify the border's size.
        See mutators for modifying specifically the shadow's size.
    */
    Rectangle border{ rect.x, rect.y, btnWidth, btnHeight };
    // color
    Color borderLiveColor = BLACK,
        // Botton state
        borderHover = { 57, 73, 171, 100 },
        borderPressed = { 0, 105, 92, 100 },
        borderIdle = borderLiveColor;
    float borderThickness = (rect.width + rect.height) / 150;
    bool isBorder = true;

    //---- Shaddow
    /*
        The shadow size is computed from the font size andlength of the text
        modifying the button's size, we also modify the shadow's size.
        See mutators for modifying specifically the shadow's size and position.
    */
    double shadowOffset = 0.05;
    Rectangle shadow{ rect.x + 5, rect.y + 5, btnWidth, btnHeight };
    Color shadowColor = GRAY;
    bool isShadow = true;

    //--- Centers text in button
    Vector2 textPos =
    {
        rect.x + (rect.width - textSize.x) / 2,
        rect.y + (rect.height - textSize.y) / 2 };

    ButtonR(string text, float x, float y)
    {
        this->text = text;
        this->rect.x = x;
        this->rect.y = y;

        buildBtn();
    }


    void draw()
    {
        update();

        if (isShadow)
            DrawRectangleRec(shadow, shadowColor);
        DrawRectangleRec(rect, btnLiveColor);
        if (isBorder)
            DrawRectangleLinesEx(border, borderThickness, borderLiveColor);
        DrawTextEx(font, text.c_str(), textPos, fontSize, fontSpacing, fontColor);
    }

    int update()
    {
        int result = -1;

        // Mouse position
        Vector2 mouse_pos = GetMousePosition();

        if (CheckCollisionPointRec(mouse_pos, rect))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                btnLiveColor = btnPressed;
                borderLiveColor = borderPressed;
                result = MOUSE_BUTTON_LEFT;
            }
            else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                btnLiveColor = btnPressed;
                borderLiveColor = borderPressed;
                result = MOUSE_BUTTON_RIGHT;
            }
            else if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
            {
                btnLiveColor = btnPressed;
                borderLiveColor = borderPressed;
                result = MOUSE_BUTTON_MIDDLE;
            }
            else
            {
                btnLiveColor = btnHover;
                borderLiveColor = borderHover;
            }
        }
        else
        {
            // state idle
            btnLiveColor = btnIdle;
            borderLiveColor = borderIdle;
        }

        return result;

    } // update()

    void buildBtn()
    {
        //--- Button size
        /*
            The button size is computed from the font size and length of the text
            See mutators to modify the button’s position,
            the text’s position in the button, and the button’s size.
        */
        float ratioWidth = (isRayFont) ? 3.5f : 4.0f,
            ratioHeight = (isRayFont) ? 2.0f : 1.4f;
        textSize = MeasureTextEx(font, text.c_str(), fontSize, fontSpacing);
        oneCharSize = MeasureTextEx(font, "C", fontSize, fontSpacing);

        if (txtResizeBtn)
        {
            //--- Button size
            rect.width = (textSize.x + ratioWidth * oneCharSize.x);
            rect.height = textSize.y * (float)(ratioHeight * (textSize.y / fontSize));
        }

        //--- Centers text in button
        textPos =
        {
            rect.x + (rect.width - textSize.x) / 2,
            rect.y + (rect.height - textSize.y) / 2 };

        //---- Button border
        border = rect;
        borderThickness = (rect.width + rect.height) / 150;

        //---- Button shadow
        shadow = { rect.x + 5, rect.y + 5, rect.width, rect.height };

    } // build_btn()

    void setFontSize(float fontSize)
    {
        this->fontSize = fontSize;
        txtResizeBtn = true;
        buildBtn();
    }

    void setFontSizeNoResize(float fontSize)
    {
        this->fontSize = fontSize;
        txtResizeBtn = false;
        buildBtn();
    }

    void setText(string text)
    {
        this->text = text;
        txtResizeBtn = true;
        buildBtn();
    }

    void setTextNoResize(string text)
    {
        this->text = text;
        txtResizeBtn = false;
        buildBtn();
    }

    void setTextPosition(float x, float y)
    {
        textPos.x = x;
        textPos.y = y;
    }

    void setBtnPosition(float btnX, float btnY)
    {
        rect.x = btnX;
        rect.y = btnY;
        buildBtn();
    }

    void setBtnSize(float btnWidth, float btnHeight)
    {
        rect.width = btnWidth;
        rect.height = btnHeight;
        txtResizeBtn = false;
        buildBtn();
    }

    bool IsClicked()
    {
        int result = update();

        Vector2 Mouse = GetMousePosition();
        this->position.x = this->rect.x;
        this->position.y = this->rect.y;


        Vector2 Boundries = { position.x + rect.width,
                             position.y + rect.height
        };

        int Xmargin = rect.width + rect.x;
        int YMargin = rect.height + rect.y;

        int MaxMarginX = Vector2Distance(Vector2Zero(), this->position);
        int MaxMarginY = Vector2Distance(Vector2Zero(), this->position);






        const int ButtonRadiusX = rect.x + rect.width / 2;
        const int ButtonRadiusY = rect.y + rect.height / 2;

        const int MinButtonRadiusX = position.x - (rect.width / 2);
        const int MinButtonRadiusY = position.y - (rect.height / 2);


        float MouseDistanceFromButtonCenter = Vector2Distance(position, Mouse);

        if (Mouse.x >= MinButtonRadiusX && Mouse.x <= ButtonRadiusX && Mouse.y >= MinButtonRadiusY && Mouse.y <= ButtonRadiusY && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }
    bool m_IsClicked;
    Vector2 position;
private:

};
#endif
