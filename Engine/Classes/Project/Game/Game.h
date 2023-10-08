// the spring board for the game using the engine.
#pragma once

#include "../../ConfigMan/ConfigMan.h"
#include "Components/GameWindowFactory.h"

#include "../../Logging/Logman.h"

#include "../../../../lib/raylib.h"

class Game
{
public:
    Game() {}

    ~Game()
    {
        delete this;
    }

    void StartGame()
    {
        Logman::CustomLog(LOG_INFO, "Starting Game", NULL);

        // Read config to decide what to set for the game
        Logman::CustomLog(LOG_INFO, "Initiating Config Manager", NULL);
        optionsConfig = toml::parse_file("Config/options.toml");
        Logman::CustomLog(LOG_INFO, "OptionsConfig file registered", NULL);

        isFullscreen = optionsConfig["Window"]["isFullScreen"].as_boolean();
        Logman::CustomLog(LOG_INFO, TextFormat("IsFullscreen = %i", isFullscreen), NULL);

        if (!isFullscreen)
        {
            windowWidth = ConfigTypeConverter::StrToInt(&optionsConfig["Window"]["windowWidth"].as_string()->operator std::string &());
            Logman::CustomLog(LOG_INFO, TextFormat("Setting window width to %i", windowWidth), NULL);

            windowHeight = ConfigTypeConverter::StrToInt(&optionsConfig["Window"]["windowHeight"].as_string()->operator std::string &());
            Logman::CustomLog(LOG_INFO, TextFormat("Setting window height to %i", windowHeight), NULL);

            // since it isnt full screen, the window is resizeable
            windowfactory->StampFlag(FLAG_WINDOW_RESIZABLE);
        }
        else
        {
            windowWidth = GetScreenWidth();
            windowHeight = GetScreenHeight();
        }

        if (windowHeight == 0 || windowWidth == 0)
        {
            Logman::CustomLog(LOG_ERROR, "WINDOW WIDTH/HEIGHT CANT BE 0! Setting to config data.", NULL);

            windowWidth = ConfigTypeConverter::StrToInt(&optionsConfig["Window"]["windowWidth"].as_string()->operator std::string &());
            Logman::CustomLog(LOG_INFO, TextFormat("Setting window width to %i", windowWidth), NULL);

            windowHeight = ConfigTypeConverter::StrToInt(&optionsConfig["Window"]["windowHeight"].as_string()->operator std::string &());
            Logman::CustomLog(LOG_INFO, TextFormat("Setting window height to %i", windowHeight), NULL);

            // since it isnt full screen, the window is resizeable
            windowfactory->StampFlag(FLAG_WINDOW_RESIZABLE);
        }

        windowfactory->StampFlag(FLAG_MSAA_4X_HINT);
        windowfactory->ManufactureWindow(windowWidth, windowHeight, "Minero");

        // Setting the window icon in task bar
        Image icon = LoadImage("resources/images/icon.png");
        ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        SetWindowIcon(icon);
    }

    void EndGame()
    {
        delete this;

    }

    int windowWidth;
    int windowHeight;

    bool isFullscreen = false;

    ConfigMan *configman = new ConfigMan();

    
private:
    toml::v3::parse_result optionsConfig;
    GameWindowFactory *windowfactory = new GameWindowFactory();
};