//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
|                                *                                      *                                 |
|  Program Buttons               *       BottonO Class Definitions      *                                 |
|                                *                                      *                                 |
---------------------------------****************************************----------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

   The ButtonO class creates a rounded edges rectangle shaped static-size button, 
    window-resized-not-responsive button.

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
      
    Child class of ButtonR class

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ButtonO.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------- Class ButtonR ---------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Constructors
//----------------------------------------------------------------------------------


//--------------------------------------------------------------------- Default constructor
/*---------------------------------------------------

    Default construtor
    - raylib default font

 ----------------------------------------------------*/
ButtonO::ButtonO()
{
   
}

//--------------------------------------------------------------------- Constructor-1
/*---------------------------------------------------

    constructor-1
    text, position

 ----------------------------------------------------*/
ButtonO::ButtonO(string text, float x, float y)
{
    this->text = text;
    rect.x = x;
    rect.y = y;

    ButtonR::buildBtn();
}

//--------------------------------------------------------------------- Constructor-2
/*------------------------------------------------------------

    Constructor-2
    - raylib default font
    text, position, font size

    Note: the font size will modify the size of the button

 -------------------------------------------------------------*/
ButtonO::ButtonO(string text, float x, float y, float fontSize)
{
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->fontSize = fontSize;
    
    ButtonR::buildBtn();
}

//--------------------------------------------------------------------- Constructor-3
/*---------------------------------------------------

    constructor-3
    - raylib default font
    text, position, font size, font color,
    button color

 ----------------------------------------------------*/
ButtonO::ButtonO(string text, float x, float y, float fontSize, Color fontColor, Color btnColor)
{
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
    btnIdle = btnColor;

    ButtonR::buildBtn();
}

//--------------------------------------------------------------------- Constructor-4
/*---------------------------------------------------

    constructor-4
    - raylib default font
    text, position, font size, font color,
    button color, border color

 ----------------------------------------------------*/
ButtonO::ButtonO(string text, float x, float y, float fontSize, Color font_color, Color btnColor, Color borderColor)
{
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->fontSize = fontSize;
    this->fontColor = font_color;
    btnIdle = btnColor;
    borderIdle = borderColor;

    ButtonR::buildBtn();
}

//--------------------------------------------------------------------- Constructor-5
/*---------------------------------------------------

    constructor-5
    - loaded font
    text, position, font

 ----------------------------------------------------*/
ButtonO::ButtonO(string text, float x, float y, Font &font)
{
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->font = font;

    isRayFont = false;

    ButtonR::buildBtn();
}

//--------------------------------------------------------------------- Constructor-6
/*---------------------------------------------------

    constructor-6
    - loaded font
    text, position, font, font size

 ----------------------------------------------------*/
ButtonO::ButtonO(string text, float x, float y, Font &font, float fontSize)
{
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->font = font;
    this->fontSize = fontSize;

    isRayFont = false;

    ButtonR::buildBtn();
}

//--------------------------------------------------------------------- Constructor-7
/*---------------------------------------------------

    constructor-7
    - loaded font
    text, position, font, font size, font color,
    button color

 ----------------------------------------------------*/
ButtonO::ButtonO(string text, float x, float y, Font &font, float fontSize, Color fontColor, Color btnColor)
{
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->font = font;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
    btnIdle = btnColor;

    isRayFont = false;

    ButtonR::buildBtn();
}

//--------------------------------------------------------------------- Constructor-8
/*---------------------------------------------------

    constructor-8
    - loaded font
    text, position, font, font size, font color,
    button color, border color

 ----------------------------------------------------*/
ButtonO::ButtonO(string text, float x, float y, Font &font, float fontSize, Color fontColor, Color btnColor, Color borderColor)
{
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->font = font;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
    btnIdle = btnColor;
    borderIdle = borderColor;

    isRayFont = false;

    ButtonR::buildBtn();
}

//--------------------------------------------------------------------- Constructor-9
/*---------------------------------------------------

    constructor-9
    - loaded font
    text, font, font size

 ----------------------------------------------------*/
ButtonO::ButtonO(string text, Font &font, float fontSize)
{
    this->text = text;
    this->font = font;
    this->fontSize = fontSize;

    isRayFont = false;

    buildBtn();
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Accessors Functions
//----------------------------------------------------------------------------------


//--------------------------------------------------------------------- Function draw()
/*----------------------------------------------------

    Draws button

 -----------------------------------------------------*/
void ButtonO::draw()
{
    ButtonR::update();

    if (isShadow) DrawRectangleRounded(shadow, roundness, 4, shadowColor);
    DrawRectangleRounded(rect, roundness, 1, btnLiveColor);
    if (isBorder)  DrawRectangleRoundedLines(border, roundness, 4, borderThickness, borderLiveColor);
    DrawTextEx(font, text.c_str(), textPos, fontSize, fontSpacing, fontColor);
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Mutators Functions
//---------------------------------------------------------------------------------



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Class Methods Operations (private)
//---------------------------------------------------------------------------------



