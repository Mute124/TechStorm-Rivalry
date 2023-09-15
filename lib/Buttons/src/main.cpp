/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------*****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *		      My Button Classes          *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************----------------------------------*/
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Alejandro (Alex) Ricciardi
created date: 01/03/ 2023


                                            My button classes


This project is my button classes in c++ with the raylib library.

Requirement
c and c++ 20 or later
Raylib library: https://www.raylib.com

****** Please see the README.txt file for more information about this project **********

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------*****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *		          Headers                *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************---------------------------------*/
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ButtonR.hpp"
#include "ButtonO.hpp"
#include "ButtonP.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *	            Classes                  *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************---------------------------------*/
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*
   
    ------------------------------------------------------------------------------------------------------------

    -- ButtonR --

    The ButtonR class creates a rectangle-shaped static-size button, window-resized-not-responsive button.

    The button size is computed from the font size and length of the text;
    the text is automatically centered on the button.
    See mutators to modify the button’s position, the text’s position in the button, and the button’s size.

    The button's border can be turned on and off.
    the border's size is computed from the font size and length of the text;
    modifying the button's size, we also modify the border's size.

    The button's shadow can be turned on and off.
    The shadow size is computed from the font size and length of the text;
    modifying the button's size, we also modify the shadow's size..

    The default font is raylib font.

    Parent class to the ButtonO class

    ------------------------------------------------------------------------------------------------------------

    -- ButtonO --

    The ButtonO class creates a rounded edges rectangle shaped static-size button, window-resized-not-responsive button.

    The button size is computed from the font size and length of the text;
    the text is automatically centered on the button.
    See mutators to  modify the button’s position, the text’s position in the button, and the button’s size.

    The button's border can be turn on and off.
    the border's size is computed from the font size and length of the text;
    modifying the button's size, we also modify the border's size.

    The button's shadow can be turn on and off.
    The shadow size is computed from the font size and length of the text;
    modifying the button's size, we also modify the shadow's size.
    See mutators for modifying specifically the shadow's size and position.

    The default font is raylib font.

    Child class of ButtonR class

    ------------------------------------------------------------------------------------------------------------

    -- ButtonP --

    The ButtonP class creates a responsive button from an image.
    (The button resizes with the window)

    The button size is computed from the font size and length of the text;
    the text is automatically centered on the button.
    See mutators to modify the button’s position, the text’s position in the button, and the button’s size.

    The default font is raylib font.

    ------------------------------------------------------------------------------------------------------------

 */


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*--------------------------------****************************************----------------------------------
  |                                *                                      *                                 |
  |                                *	     Function Declarations        *                                 |
  |                                *                                      *                                 |
  ---------------------------------****************************************---------------------------------*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /*
    
    

  */

  /*--------------------------------------------------------------------

     Function descrption header comment

  --------------------------------------------------------------------*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------****************************************----------------------------------
 |                                *                                      *                                 |
 |                                *		           Main                  *                                 |
 |                                *                                      *                                 |
 ---------------------------------****************************************---------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    //--------------------------------------------------------------------------------------

    // variables
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1100;
    const int screenHeight = 450;

    //--------------------------------------------------------------------------------------

    // Initialization Window, OpenGL context, Texture Loads need to be call after this point 
    //--------------------------------------------------------------------------------------
    // 
    // Enable config flags for resizable window and vertical synchro
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "My Button Classes");


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    // Initialize audio device and context
    //--------------------------------------------------------------------------------------
    InitAudioDevice();

    //--------------------------------------------------------------------------------------

    // 2D textures/ 3D textures / models
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------

    // Sounds
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------

    // Font
    //--------------------------------------------------------------------------------------
    // 
    Font font1 = LoadFont("resources/fonts/monofonto.otf");
    Font font2 = LoadFont("resources/fonts/segoeui.ttf");

                                     
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------- comment type-1 -------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //----------------------------------------------------------------------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------------------------------------------------------------------------
    //                                               comment type-2 
    //--------------------------------------------------------------------------------------------------------------- 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //---------------------------------------------- comment type-2 -------------------------------------------------
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //------ Rectangle buttons
    ButtonR btn1;
    //btn1.isShadow = false;
    //btn1.btnIdle = PURPLE; // button idle
    //btn1. borderThickness = 4;
    //btn1.isBorder = false;
    //btn1.setText("Continue");
    //btn1.setTextNoResize("up");
    //btn1.setTextPosition(btn1.rect.x, btn1.rect.y);
    //btn1.setFontSize(24);
    //btn1.setFontSizeNoResize(34);

    ButtonR btn2("Continue", 100, 225, font1);
    //btn2.isShadow = false;
    ButtonR btn3("Button", 100, 300, font2);


    //------- Rounded rectangle buttons
    ButtonO btn4("Button", 450, 100);
    //btn4.isShadow = false;
    //btn4.btnIdle = PURPLE; // button idle
    //btn4.borderThickness = 4;
    //btn4.isBorder = false;
    //btn4.setText("Continue");
    //btn4.setTextNoResize("up");
    //btn4.setTextPosition(btn1.rect.x, btn1.rect.y);
    //btn4.setFontSize(64);
    //btn4.setFontSizeNoResize(34);

    ButtonO btn5("Button",450, 225, font1);
    ButtonO btn6("Button", 450, 300, font2);
    //btn6.setBtnSize(150, 100);

    //------- Images buttons
    ButtonP btn7;
    //btn7.setHoverColor(PURPLE);
    //btn7.setTextNoResize("up");
    //btn7.setTextPosition(btn1.rect.x, btn1.rect.y);
    //btn7.setFontSize(24);
    //btn7.setFontSizeNoResize(34);
    ButtonP btn8("Button", 750, 225, "resources/images/button1.png", font1);
    //btn8.setFontSize(34);
    ButtonP btn9("Button", 750, 325, "resources/images/button1.png", font2);
    //btn9.setBtnSize(150, 100);
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //--------------------------------------------------------------------------------------

        // Update
        //-------------------------------------------------------------------------------------- 
        
        
                                         
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------

        BeginDrawing();

            ClearBackground(BLACK);

            btn1.draw();
            btn2.draw();
            btn3.draw();

            btn4.draw();
            btn5.draw();
            btn6.draw();

            btn7.draw();
            btn8.draw();
            btn9.draw();

        EndDrawing();

        //----------------------------------------------------------------------------------
    }

    //--------------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    
    CloseWindow();        // Close window and OpenGL context

    //--------------------------------------------------------------------------------------

    return 0;
}