#include "MainMenu.hpp"

MainMenu::MainMenu() {
    // If SkipMainMenu is false then it goes ahead with creation.
    if (!Main::SkipMainMenu) {
        this->mmen_start = new ButtonR("start", Game::middlex, Game::middley);
        this->Draw();
    }
}

void MainMenu::Draw() const
{
    // checks to see if the main menu should just skip, if yes then well, skip
    if (!Main::SkipMainMenu)
    {
        Logman::CustomLog(LOG_INFO, "Main loading done, Main menu drawing", NULL);

        // Main menu Loop
        while (Main::currentGameScreen == Main && !WindowShouldClose())
        {

            BeginDrawing(); //Begins the drawing mode

            ClearBackground(WHITE); // Clears background and replaces it with white. Very important

            this->mmen_start->draw(); // draws the start button
            EndDrawing();

            // key to go to the game incase button kaput
            if (IsKeyPressed(KEY_DELETE))
            {
                Main::currentGameScreen = Gameplay;
            }

            // Main Menu Start Button
            if (mmen_start->IsClicked())
            {
                Main::currentGameScreen = Gameplay;
            }
        }
    }
    
}