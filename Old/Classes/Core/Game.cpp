#include "Game.hpp"

void Game::CreateWindow(const int Width, const int Height, const char *Title)
{

    // Error handling
    try
    {
        gameWindow = new Window(screenWidth, screenHeight, "Minero");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

Window Game::GetGameWindow()
{
    return *gameWindow;
}