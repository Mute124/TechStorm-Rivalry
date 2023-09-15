///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
|                                *                                      *                                 |
|  Program Buttons               *         MenuR Class Definition       *                                 |
|                                *                                      *                                 |
---------------------------------****************************************----------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

    The MenuR class creates static-size menu objects,
    window-resized-not-responsive menus.

    The menu object can contain one menu bar or several menu bars,
    the menu can be automatically positioned on the left, center, or right side of the screen.
    See mutators to modify the menu position.

    The bars’ sizes are computed from the font size and length of the bar text longest;
    the texts can be positioned on the left, center, or right side of the bars.
    See mutators to modify each individual bar position, the text’s position in each individual bar,
    and the each individual bar’s size.

    The bars’ borders can be turned on and off.
    The sizes of the borders are computed from the font size and length of the bar text longest bar;
    modifying the bars’ sizes will also modify the borders’ sizes.

    The button's shadows can be turned on and off.
    The sizes of the shadows are computed from the font size and length of the nar text longest;
    modifying the bars’ sizes will also modify the shadows’ sizes.

    The default font is raylib font.

    The menu bars are untilizing the ButtonR class


*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MenuR.hpp"

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
MenuR::MenuR()
{
    for (unsigned i = 0; i < 5; i++) texts.push_back("Menu");

    buildMenu();
}

//--------------------------------------------------------------------- Constructor-1
/*---------------------------------------------------

    Constructor-1
    - raylib default font
    texts

 ----------------------------------------------------*/
MenuR::MenuR(vector<string> texts)
{
    this->texts = texts;
    buildMenu();
}

//--------------------------------------------------------------------- Constructor-2
/*---------------------------------------------------

    Constructor-2
    - raylib default font
    texts, menu position

    CENTER, CENTER_TOP, CENTER_BOTTOM,
    LEFT, LEFT_TOP, LEFT_BOTTOM,
    RIGHT, RIGHT_TOP, RIGHT_BOTTOM

 ----------------------------------------------------*/
MenuR::MenuR(vector<string> texts, unsigned menuPos)
{
    this->texts = texts;
    this->menuPos = menuPos;
    buildMenu();
}


//--------------------------------------------------------------------- Constructor-2
/*---------------------------------------------------

    constructor-1
    - raylib default font
    texts, font, font size

 ----------------------------------------------------*/
MenuR::MenuR(vector<string> texts, Font &font, float fontSize)
{
    this->texts = texts;
    this->font = font;
    this->fontSize = fontSize;
    isRayFont = false;
    buildMenu();
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Accessors Methods
//----------------------------------------------------------------------------------

//--------------------------------------------------------------------- Function draw()
/*----------------------------------------------------

    Draws button

 -----------------------------------------------------*/
void MenuR::draw()
{
    for (ButtonR &bar : bars) bar.draw();
}


//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Mutators Methods
//---------------------------------------------------------------------------------



//--------------------------------------------------------------------- Method buildMenu()
/*----------------------------------------------------------

    Builds the Menu,
    computes size from the font size and length of the texts
    
 -----------------------------------------------------------*/
void MenuR::buildMenu()
{
    //---- Builds Bar
    numBars =(unsigned)texts.size(); // the number of bars is computed from the size of the vector texts
    //-- Bars' texts
    if (isRayFont) // Default font
    {
        ButtonR bar; // empty bar, Default ButtonR
        for (unsigned i = 0; i < numBars; i++) bars.push_back(bar); 
        for (unsigned i = 0; i < numBars; i++) bars[i].setText(texts[i]); 
    }
    else // Loaded font
    {
        ButtonR bar("Empty", font, fontSize);
        for (unsigned i = 0; i < numBars; i++) bars.push_back(bar);
        for (unsigned i = 0; i < numBars; i++) bars[i].setText(texts[i]);
    }
    
    // Computes the bars width and menu width
    // The bars’ sizes are computed from the font size and length of the longest text
    float barsWidth = 0;
    for (ButtonR &bar : bars) if (bar.rect.width > barsWidth) barsWidth = bar.rect.width + 50;
    //-- Menu size
    menuWidth = barsWidth;
    menuHeight = numBars * bars[0].btnHeight + barSpacing * (numBars - 1);
    //-- sets bars size
    for (ButtonR &bar : bars) bar.setBtnSize(barsWidth, bar.rect.height);

    //---- Menu position
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float screenMargin = 50.0f;
    try // Error handler
    {
        switch (menuPos) // Computes menu x and y position
        {
        case CENTER:
            menuX = (float)(screenWidth / 2) - (menuWidth / 2);
            menuY = (float)(screenHeight / 2) - (menuHeight / 2);
            break;
        case CENTER_TOP:
            menuX = (float)(screenWidth / 2) - (menuWidth / 2);
            menuY = screenMargin;
            break;
        case CENTER_BOTTOM:
            menuX = (float)(screenWidth / 2) - (menuWidth / 2);
            menuY = (float)(screenHeight - menuHeight - screenMargin);
            break;
        case LEFT:
            menuX = screenMargin;
            menuY = (float)(screenHeight / 2) - (menuHeight / 2);
            break;
        case LEFT_TOP:
            menuX = screenMargin;
            menuY = screenMargin;
            break;
        case LEFT_BOTTOM:
            menuX = screenMargin;
            menuY = (float)(screenHeight - menuHeight - screenMargin);
            break;
        case RIGHT:
            menuX = (float)(screenWidth - menuWidth - 2 * screenMargin);
            menuY = (float)(screenHeight / 2) - (menuHeight / 2);
            break;
        case RIGHT_TOP:
            menuX = (float)(screenWidth - menuWidth - 2 * screenMargin);
            menuY = screenMargin;
            break;
        case RIGHT_BOTTOM:
            menuX = (float)(screenWidth - menuWidth - 2 * screenMargin);
            menuY = (float)(screenHeight - menuHeight - screenMargin);
            break;
        case NONE:
            // The menu was repositioned using setMenuPosition()
            break;
        default:
            throw "   -- Error --\n   The entered menu position is not valid a valid entry.\n";
            break;
        }
    } catch (char const *ERROR) { cout << "\n " << ERROR; }// Catches the exception if it occurs

    //---- Bars positions
    float tempBarY = menuY;
    for (ButtonR &bar : bars)
    {
        bar.setBtnPosition(menuX, tempBarY);
        tempBarY += bar.btnHeight + barSpacing;
    }

    //---- Texts position
    for (ButtonR &bar : bars)
    {  
        try // Error handler
        {
            switch (textsPos)
            {
            case TXT_CENTER:
                // The ButtonR class centers the texts by default
                break;
            case TXT_LEFT:
                bar.setTextPosition(bar.rect.x + 10, bar.textPos.y);
                break;
            case TXT_RIGHT:
                bar.setTextPosition(bar.rect.x - 10 + (bar.rect.width - bar.textSize.x), bar.textPos.y);
                break;
            case TXT_NONE:
                // The texts were repositioned using setTextPos()
                break;
            default:
                throw "   -- Error --\n   The entered texts' position in menu is not a valid entry.\n";
                break;
            }
        } catch (char const *ERROR) { cout << "\n " << ERROR; }// Catches the exception if it occurs
    }
    
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

// Class Methods Operations (private)
//---------------------------------------------------------------------------------

