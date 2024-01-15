///////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |  Program Button Class          *       ButtonP Class Declarations     *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************----------------------------------*/
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

    The ButtonP class creates a responsive button from an image.
    (The button resizes with the window)

    The button size is computed from the font size and length of the text;
    the text is automatically centered on the button.
    See mutators to modify the button’s position, the text’s position in the button, and the button’s size.

    The default font is raylib font.

    Requirement
    c and c++ 20 or later
    Raylib library: https://www.raylib.com

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BUTTON_P_HPP
#define BUTTON_P_HPP

#ifdef _MSC_VER
#pragma once
#endif  // _MSC_VER

#include "raylib.h"

#include <iostream>	// For debugging purposes
#include <string>
#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------- Class <name> ---------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class ButtonP
{


    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // variables (Private)
    //----------------------------------------------------------------------------------



public:



    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // variables (Public)
    //----------------------------------------------------------------------------------
    
   
    //---- Font 
    Font font = GetFontDefault(); // Raylib default font
    float fontSize = 32,
          fontSpacing = 2.0f;
    Color fontColor = RAYWHITE;
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
    Vector2 btnPos = { 750, 100 };
    Rectangle rect{ btnPos.x, btnPos.y, btnWidth, btnHeight },
              originalRect = rect;
    //--- Centers text in button
    Vector2 textPos =
    {
        rect.x + (rect.width - textSize.x) / 2,
        rect.y + (rect.height - textSize.y) / 2
    };
    // Text position and size
    Rectangle rectText{ textPos.x, textPos.y, textSize.x, textSize.y },
              originalRectText = rectText;

    //---- Button state
    // Button and text image Shading Colors
    Color btnHoverColor = GRAY,
          btnPressedColor = DARKGRAY;
    //---- Button Image
    string imgPath; // Image path in secondary memory
    Image img;                                    
    // Button textures
    Texture2D btnIdle = LoadTextureFromImage(img);  // Image converted to texture, uploaded to GPU memory (VRAM)
    Texture2D btnHover = btnIdle;
    Texture2D btnPressed = btnIdle;
    Texture2D *btnLive = &btnIdle;
    //---- Text Image
    Image textImg;
    Texture2D textIdle = LoadTextureFromImage(textImg);
    Texture2D textHover = textIdle;
    Texture2D textPressed = textIdle;
    Texture2D *textLive = &textIdle;

    // window
    int windowWidth = GetScreenWidth();
    int windowHeight = GetScreenHeight();
    Vector2 windowScale = { (float)GetScreenWidth() / windowWidth, (float)GetScreenHeight() / windowHeight };


    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // Constructors
    //---------------------------------------------------------------------------------


    /*---------------------------------------------------

        Default construtor (empty)
        - raylib default font

     ----------------------------------------------------*/
    ButtonP();

    /*---------------------------------------------------

        Constructor-1
        - raylib default font
        text, position, image path

     ----------------------------------------------------*/
    ButtonP(string text, float x, float y, string imgPath);

    /*------------------------------------------------------------

        Constructor-2
        - raylib default font
        text, position, image path, font size

        Note: the font size will modify the size of the button

     -------------------------------------------------------------*/
    ButtonP(string text, float x, float y, string imgPath, float fontSize);

    /*---------------------------------------------------

        Constructor-3
        - raylib default font
        text, position, font size, font color,

     ----------------------------------------------------*/
    ButtonP(string text, float x, float y, string imgPath, float fontSize, Color fontColor);


    /*---------------------------------------------------

        Constructor-4
        - loaded font
        text, position, image path, font

     ----------------------------------------------------*/
    ButtonP(string text, float x, float y, string imgPath, Font &font);

    /*---------------------------------------------------

        constructor-5
        - loaded font
        text, font, font size

     ----------------------------------------------------*/
    ButtonP(string text, Font &font, float fontSize);

    
    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // Destructor
    //---------------------------------------------------------------------------------
    ~ButtonP();


    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // Accessors Methods
    //----------------------------------------------------------------------------------


    /*----------------------------------------------------

        draw button

     -----------------------------------------------------*/
    void draw();


    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // Mutators Methods
    //---------------------------------------------------------------------------------


    /*----------------------------------------------------

        Updates button

     -----------------------------------------------------*/
    int update();


    /*----------------------------------------------------

        Sets font size and
        Resizes button to fit text
        Takes a string

     -----------------------------------------------------*/
    void setFontSize(float fontSize);

    /*----------------------------------------------------

        Sets font size and
        does NOT resizes button to fit text
        Takes a string

     -----------------------------------------------------*/
    void setFontSizeNoResize(float fontSize);

    /*----------------------------------------------------

         Sets text and
         Resizes button to fit text
         Takes a string

     -----------------------------------------------------*/
    void setText(string text);

    /*----------------------------------------------------

         Sets text and
         does NOT resizes button to fit text
         Takes a string

     -----------------------------------------------------*/
    void setTextNoResize(string text);

    /*----------------------------------------------------

         Sets text position
         does NOT resizes button to fit text

     -----------------------------------------------------*/
    void setTextPosition(float x, float y);   

    /*----------------------------------------------------

        Sets the hover color for button and text

     -----------------------------------------------------*/
    void setHoverColor(Color btnHoverColor);

    /*----------------------------------------------------

        Sets the pressed color for button and text

     -----------------------------------------------------*/
    void setPressedColor(Color btnPressedColor);

    /*----------------------------------------------------

       Sets the button position in the screen

     -----------------------------------------------------*/
    void ButtonP::setBtnPosition(float btnX, float btnY);

    /*----------------------------------------------------

        Sets sizes of the button,
        does not resise fonts

     -----------------------------------------------------*/
    void setBtnSize(float btnWidth, float btnHeight);

private:


    //----------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------

    // Classe Operation Methods (private)
    //---------------------------------------------------------------------------------


    /*----------------------------------------------------------

        Builds the botton,
        computes size from the font size and length of the text

     -----------------------------------------------------------*/
    void buildBtn();

};
#endif