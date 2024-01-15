//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
|                                *                                      *                                 |
|  Program Buttons               *       BottonP Class Definitions      *                                 |
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

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ButtonP.hpp"


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
ButtonP::ButtonP()
{
    imgPath = "resources/images/button1.png";
    buildBtn();
}

//--------------------------------------------------------------------- Constructor-1
/*---------------------------------------------------

    constructor-1
    - raylib default font
    text, position. image path

 ----------------------------------------------------*/
ButtonP::ButtonP(string text, float x, float y, string imgPath)
{
    this->imgPath = imgPath;
    this->text = text;
    rect.x = x;
    rect.y = y;

    buildBtn();
}

//--------------------------------------------------------------------- Constructor-2
/*------------------------------------------------------------

    Constructor-2
    - raylib default font
    text, position, image path, font size

    Note: the font size will modify the size of the button

 -------------------------------------------------------------*/
ButtonP::ButtonP(string text, float x, float y, string imgPath, float fontSize)
{
    this->imgPath = imgPath;
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->fontSize = fontSize;

    buildBtn();
}

//--------------------------------------------------------------------- Constructor-3
/*---------------------------------------------------

    constructor-3
    - raylib default font
    text, position, image path, font size, font color

 ----------------------------------------------------*/
ButtonP::ButtonP(string text, float x, float y, string imgPath, float fontSize, Color fontColor)
{
    this->imgPath = imgPath;
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->fontSize = fontSize;
    this->fontColor = fontColor;

    buildBtn();
}

//--------------------------------------------------------------------- Constructor-4
/*---------------------------------------------------

    constructor-4
    - loaded font
    text, position, image path, font

 ----------------------------------------------------*/
ButtonP::ButtonP(string text, float x, float y, string imgPath, Font &font)
{
    this->imgPath = imgPath;
    this->text = text;
    rect.x = x;
    rect.y = y;
    this->font = font;

    isRayFont = false;

    buildBtn();
}

//--------------------------------------------------------------------- Constructor-5
/*---------------------------------------------------

    constructor-5
    - loaded font
    text, font, font size

 ----------------------------------------------------*/
ButtonP::ButtonP(string text, Font &font, float fontSize)
{
    this->text = text;
    this->font = font;
    this->fontSize = fontSize;

    isRayFont = false;

    buildBtn();
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Destructor
//---------------------------------------------------------------------------------
ButtonP::~ButtonP() 
{
    //----------------------------------------------------------------------------------

    // De-Initialization Textures
    //----------------------------------------------------------------------------------
    UnloadTexture(btnIdle);
    UnloadTexture(btnHover);
    UnloadTexture(btnPressed);
    UnloadTexture(textIdle);
    UnloadTexture(textHover);
    UnloadTexture(textPressed);
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Accessors Functions
//----------------------------------------------------------------------------------


//--------------------------------------------------------------------- Method draw()
/*----------------------------------------------------

    Draws button

 -----------------------------------------------------*/
void ButtonP::draw()
{
   update();
   DrawTexturePro( *btnLive, originalRect, rect, { 0, 0 }, 0.0f, WHITE);
   DrawTexturePro( *textLive, originalRectText, rectText, { 0, 0 }, 0.0f, fontColor);
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Mutators Functions
//---------------------------------------------------------------------------------


//--------------------------------------------------------------------- Method update()
/*----------------------------------------------------

    Updates button

 -----------------------------------------------------*/
int ButtonP::update()
{
    int result = -1;

    // Mouse position
    Vector2 mousePos = GetMousePosition();

    if (IsWindowResized())
    {
        // window scale
        windowScale = { (float)GetScreenWidth() / windowWidth, (float)GetScreenHeight() / windowHeight };

        rect = 
        {
            btnPos.x * windowScale.x,
            btnPos.y * windowScale.y,
            originalRect.width * windowScale.x,
            originalRect.height * windowScale.y
        };

        rectText =
        {
            textPos.x * windowScale.x,
            textPos.y * windowScale.y,
            originalRectText.width * windowScale.x,
            originalRectText.height * windowScale.y
        };

    }

    if (CheckCollisionPointRec(mousePos, rect))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            btnLive = &btnPressed;
            textLive = &textPressed;
            result = MOUSE_BUTTON_LEFT;
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            btnLive = &btnPressed;
            textLive = &textPressed;
            result = MOUSE_BUTTON_RIGHT;
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        {
            btnLive = &btnPressed;
            textLive = &textPressed;
            result = MOUSE_BUTTON_MIDDLE;
        }
        else
        {
            btnLive = &btnHover;
            textLive = &textHover;
        }
    }
    else
    {
        // state idle
        btnLive = &btnIdle;
        textLive = &textIdle;
    }

    return result;

} // update()


//--------------------------------------------------------------------- Method setFontSize()
/*----------------------------------------------------

    Sets font size and
    Resizes button to fit text
    Takes a string

 -----------------------------------------------------*/
void ButtonP::setFontSize(float fontSize) 
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
void ButtonP::setFontSizeNoResize(float fontSize)
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
void ButtonP::setText(string text)
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
void ButtonP::setTextNoResize(string text)
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
void ButtonP::setTextPosition(float x, float y)
{
    textPos.x = x;
    textPos.y = y;
}

//--------------------------------------------------------------------- Method setHoverColor()
/*----------------------------------------------------

     Sets the hover color for button and text

 -----------------------------------------------------*/
void ButtonP::setHoverColor(Color btnHoverColor)
{
    this->btnHoverColor = btnHoverColor;
    buildBtn();
}

//--------------------------------------------------------------------- Method setPressedColor()
/*----------------------------------------------------

     Sets the pressed color for button and text

 -----------------------------------------------------*/
void ButtonP::setPressedColor(Color btnPressedColor)
{
    this->btnPressedColor = btnPressedColor;
    buildBtn();
}

//--------------------------------------------------------------------- Method setBtnPosition()
/*----------------------------------------------------

     Sets the button position in the screen

 -----------------------------------------------------*/
void ButtonP::setBtnPosition(float btnX, float btnY)
{
    rect.x = btnX;
    rect.y = btnY;
    buildBtn();
}

//--------------------------------------------------------------------- Method setBtnSize()
/*----------------------------------------------------

    Sets sizes of the button,
    does not resise fonts

 -----------------------------------------------------*/
void ButtonP::setBtnSize(float btnWidth, float btnHeight)
{
    rect.width = btnWidth;
    rect.height = btnHeight;
    txtResizeBtn = false;
    buildBtn();
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Class Methods Operations (private)
//---------------------------------------------------------------------------------


//--------------------------------------------------------------------- Method buildBtn()
/*----------------------------------------------------------

    Builds the botton,
    computes size from the font size and length of the text

 -----------------------------------------------------------*/
void ButtonP::buildBtn()
{

    //--- Button size
    /*
        The button size is computed from the font size and length of the text
        See mutators to modify the button’s position,
        the text’s position in the button, and the button’s size.
    */

    float ratioWidth = (isRayFont) ? 3.4f : 4.0f,
          ratioHeight = (isRayFont) ? 2.2f : 2.0f;
    textSize = MeasureTextEx(font, text.c_str(), fontSize, fontSpacing);
    oneCharSize = MeasureTextEx(font, "C", fontSize, fontSpacing);

    if (txtResizeBtn)
    {
        //--- Button size
        rect.width = (textSize.x + ratioWidth * oneCharSize.x);
        rect.height = textSize.y * (float)(ratioHeight * (textSize.y / fontSize));
        // Init original rectangle
        btnPos = { rect.x, rect.y };
        originalRect = rect; // for width and height
        originalRect.x = 0;
        originalRect.y = 0;
    }
    else 
    {
        btnPos = { rect.x, rect.y };
        originalRect = rect; // for width and height
        originalRect.x = 0;
        originalRect.y = 0;
    }
    //--- Centers text in button
    textPos =
    {
        rect.x + (rect.width - textSize.x) / 2,
        rect.y + (rect.height - textSize.y) / 2
    };

    // Text position and size
    rectText = { textPos.x, textPos.y, textSize.x, textSize.y },
               // Init original rectangle text
              originalRectText = rectText; // for width and height
              originalRectText.x = 0;
              originalRectText.y = 0;

    //---- Image
    // Button image
    img = LoadImage(imgPath.c_str()); // Load image in CPU memory (RAM)
    ImageResize(&img, (int)rect.width + 1, (int)rect.height + 1); // Resize image (Bicubic scaling algorithm)
    // Text image
    textImg = ImageTextEx(font, text.c_str(), fontSize, fontSpacing, fontColor);
    ImageResize(&textImg, (int)rectText.width, (int)rectText.height);

    //---- Button state, idle, hover, pressed, Shades button image
    Image tintImg = ImageCopy(img);
    // Idle
    btnIdle = LoadTextureFromImage(img);  // Image converted to texture, uploaded to GPU memory (VRAM)
    // Hover
    ImageColorTint(&tintImg, btnHoverColor);
    Color *pixels = LoadImageColors(tintImg);    // Load pixel data from image (RGBA 32bit)
    // Update button texture
    btnHover = LoadTextureFromImage(img);
    UpdateTexture(btnHover, pixels);
    // Pressed
    tintImg = ImageCopy(img);
    ImageColorTint(&tintImg, btnPressedColor);
    pixels = LoadImageColors(tintImg);
    // Update button texture
    btnPressed = LoadTextureFromImage(img);
    UpdateTexture(btnPressed, pixels);

    //---- Text state, idle, hover, pressed, Shades button image
    tintImg = ImageCopy(textImg);
    // Idle
    textIdle = LoadTextureFromImage(textImg);  // Image converted to texture, uploaded to GPU memory (VRAM)
    // Hover
    ImageColorTint(&tintImg, btnHoverColor);
    pixels = LoadImageColors(tintImg);    // Load pixel data from image (RGBA 32bit)
    // Update button texture
    textHover = LoadTextureFromImage(textImg);
    UpdateTexture(textHover, pixels);
    // Pressed
    tintImg = ImageCopy(textImg);
    ImageColorTint(&tintImg, btnPressedColor);
    pixels = LoadImageColors(tintImg);
    // Update button texture
    textPressed = LoadTextureFromImage(textImg);
    UpdateTexture(textPressed, pixels);

    //--------------------------------------------------------------------------------------

    // De-Initialization Images
    //--------------------------------------------------------------------------------------

    UnloadImage(img); // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
    UnloadImage(textImg);
    UnloadImage(tintImg);
    UnloadImageColors(pixels);

} // buildBtn()



