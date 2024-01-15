#include "ButtonR.h"

ButtonR::ButtonR(string text, float x, float y)
{
    this->text = text;
    rect.x = x;
    rect.y = y;

    buildBtn();
}

void ButtonR::draw()
{
    update();

    if (isShadow)
        DrawRectangleRec(shadow, shadowColor);
    DrawRectangleRec(rect, btnLiveColor);
    if (isBorder)
        DrawRectangleLinesEx(border, borderThickness, borderLiveColor);
    DrawTextEx(font, text.c_str(), textPos, fontSize, fontSpacing, fontColor);
}

int ButtonR::update()
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

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Mutators Methods
//---------------------------------------------------------------------------------

//--------------------------------------------------------------------- Method buildBtn()
/*----------------------------------------------------------

    Builds the botton,
    computes size from the font size and length of the text

 -----------------------------------------------------------*/
void ButtonR::buildBtn()
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
            rect.y + (rect.height - textSize.y) / 2};

    //---- Button border
    border = rect;
    borderThickness = (rect.width + rect.height) / 150;

    //---- Button shadow
    shadow = {rect.x + 5, rect.y + 5, rect.width, rect.height};

} // build_btn()

//--------------------------------------------------------------------- Method setFontSize()
/*----------------------------------------------------

     Sets font size and
     Resizes button to fit text
     Takes a string

 -----------------------------------------------------*/
void ButtonR::setFontSize(float fontSize)
{
    this->fontSize = fontSize;
    txtResizeBtn = true;
    buildBtn();
}

//--------------------------------------------------------------------- Method setFontSizeNoResize()
/*----------------------------------------------------

     Sets font size and
     does NOT resizes button to fit text
     Takes a string

 -----------------------------------------------------*/
void ButtonR::setFontSizeNoResize(float fontSize)
{
    this->fontSize = fontSize;
    txtResizeBtn = false;
    buildBtn();
}

//--------------------------------------------------------------------- Method setText()
/*----------------------------------------------------

     Sets text and
     Resizes button to fit text
     Takes a string

 -----------------------------------------------------*/
void ButtonR::setText(string text)
{
    this->text = text;
    txtResizeBtn = true;
    buildBtn();
}

//--------------------------------------------------------------------- Method setTextNoResize()
/*----------------------------------------------------

     Sets text and
     does NOT resizes button to fit text
     Takes a string

 -----------------------------------------------------*/
void ButtonR::setTextNoResize(string text)
{
    this->text = text;
    txtResizeBtn = false;
    buildBtn();
}

//--------------------------------------------------------------------- Method setTextPosition()
/*----------------------------------------------------

     Sets text position
     does NOT resizes button to fit text

 -----------------------------------------------------*/
void ButtonR::setTextPosition(float x, float y)
{
    textPos.x = x;
    textPos.y = y;
}

void ButtonR::setBtnPosition(float btnX, float btnY)
{
    rect.x = btnX;
    rect.y = btnY;
    buildBtn();
}

void ButtonR::setBtnSize(float btnWidth, float btnHeight)
{
    rect.width = btnWidth;
    rect.height = btnHeight;
    txtResizeBtn = false;
    buildBtn();
}

bool ButtonR::IsClicked()
{

    int result = update();

        Vector2 Mouse = GetMousePosition();
        this->position.x = this->rect.x;
        this->position.y = this->rect.y;

        int Xmargin = rect.width + rect.x;
        int YMargin = rect.height + rect.y;

        int MaxMarginX = Xmargin - (rect.width / 2);
        int MaxMarginY = YMargin -(rect.height / 2);

        if (Mouse.x <= MaxMarginX && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (Mouse.y <= MaxMarginY)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
        return false;
}
