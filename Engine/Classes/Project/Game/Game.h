// the spring board for the game using the engine.
#pragma once
#include "../../../../Common.h"

#include "../../Env/Light/Light.h"

#include "Components/GameWindowFactory.h"
#include "../../Player/Player.h"

#include "../../Env/Environment.h"

class Game
{

    toml::v3::parse_result optionsConfig;
    GameWindowFactory *windowfactory = new GameWindowFactory();

public:
    class Renderer
    {
    public:
        void StartDraw()
        {
            isDrawing = true;
            BeginDrawing();
        }

        void EndDraw()
        {
            isDrawing = false;
            EndDrawing();
        }

        void Start3D(Camera *camera)
        {
            if (!isDrawing)
            {
                StartDraw();
            }
            else
            {
                isIn3DMode = true;
                BeginMode3D(*camera);
            }
        }

        void End3D()
        {
            if (isIn3DMode && isDrawing)
            {
                EndMode3D();
                isIn3DMode = false;
            }
        }

        void StartTexturing()
        {
            // StartDraw();
            BeginTextureMode(fbo);
            ClearBackground(BLACK);
        }

        void StartDepthMode()
        {
            BeginTextureMode(depthMapFBO);
        }

        void StopDepthMode()
        {
            EndTextureMode();
        }

        void StopTexturing()
        {
            // EndDraw();
            EndTextureMode();
        }

        void CreateRenderTexture(int width, int height)
        {
            fbo = LoadRenderTexture(width, height);
            depthMapFBO = LoadRenderTexture(width, height);
        }

        RenderTexture2D fbo;
        RenderTexture2D depthMapFBO; // shadowmap.

        Shader pbrShader;
        Shader bloomShader;


        static inline Environment *env = new Environment();

    private:
        bool isDrawing;
        bool isIn3DMode;
    };

    int windowWidth;
    int windowHeight;

    bool isFullscreen = false;
    bool enableMusic;

    ConfigMan *configman = new ConfigMan();
    static inline Renderer *renderer;

    Game() {}

    ~Game()
    {
        delete this;
    }

    toml::v3::parse_result GetGameConfig()
    {
        return this->optionsConfig;
    }

    void StartGame()
    {

        // Read config to decide what to set for the game
        Logman::CustomLog(LOG_INFO, "Initiating Config Manager", NULL);

        optionsConfig = toml::parse_file("../../Minero-Game/Config/options.toml");
        Logman::CustomLog(LOG_INFO, "OptionsConfig file registered", NULL);

        isFullscreen = optionsConfig["Window"]["isFullScreen"].as_boolean();
        Logman::CustomLog(LOG_INFO, TextFormat("IsFullscreen = %i", isFullscreen), NULL);

        enableMusic = optionsConfig["Sound"]["enableMusic"].as_boolean();
        Logman::CustomLog(LOG_INFO, TextFormat("EnableMusic = %i", enableMusic), NULL);

        if (isFullscreen == true)
        {
            windowWidth = ConfigTypeConverter::StrToInt(&optionsConfig["Window"]["windowWidth"].as_string()->operator std::string &());
            Logman::CustomLog(LOG_INFO, TextFormat("Setting window width to %i", windowWidth), NULL);

            windowHeight = ConfigTypeConverter::StrToInt(&optionsConfig["Window"]["windowHeight"].as_string()->operator std::string &());
            Logman::CustomLog(LOG_INFO, TextFormat("Setting window height to %i", windowHeight), NULL);

            // since it isnt full screen, the window is resizeable
            // windowfactory->StampFlag(FLAG_WINDOW_RESIZABLE);
        }
        else
        {
            windowWidth = GetMonitorWidth(0);
            windowHeight = GetMonitorHeight(0);

            // windowfactory->StampFlag(FLAG_WINDOW_MAXIMIZED);
        }
        if (windowHeight == 0 || windowWidth == 0)
        {
            Logman::CustomLog(LOG_ERROR, "WINDOW WIDTH/HEIGHT CANT BE 0! Setting to config data.", NULL);

            windowWidth = ConfigTypeConverter::StrToInt(&optionsConfig["Window"]["windowWidth"].as_string()->operator std::string &());
            Logman::CustomLog(LOG_INFO, TextFormat("Setting window width to %i", windowWidth), NULL);

            windowHeight = ConfigTypeConverter::StrToInt(&optionsConfig["Window"]["windowHeight"].as_string()->operator std::string &());
            Logman::CustomLog(LOG_INFO, TextFormat("Setting window height to %i", windowHeight), NULL);

            // since it isnt full screen, the window is resizeable
            // windowfactory->StampFlag(FLAG_WINDOW_RESIZABLE);
        }

        // Stamp window config flags & Manufacture
        // windowfactory->StampFlag(FLAG_MSAA_4X_HINT);

        Logman::CustomLog(LOG_INFO, "Starting Game", NULL);
        
        windowfactory->ManufactureWindow(windowWidth, windowHeight, "Minero");
        InitAudioDevice(); // starts the audio driver(s).

        DisableEventWaiting();

        SetExitKey(KEY_BACKSPACE); // In event of your fuck up press this.

        // Setting the window icon in task bar
        Image icon = LoadImage("../../Minero-Game/resources/images/icon.png");
        ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        SetWindowIcon(icon);

        // set up FBO
        rlglInit(windowWidth, windowHeight);

        renderer = new Renderer();

        renderer->CreateRenderTexture(windowWidth, windowHeight);

        renderer->bloomShader = LoadShader(0, "../../Minero-Game/resources/shaders/bloom.fs");

        // rlSetCullFace(RL_CULL_FACE_BACK);
    }

    void EndGame()
    {
        rlglClose();
        delete configman;
        delete windowfactory;
        delete this;
    }

    // GRAPHICS
    //_____________________________________________________

    // Renderer *renderer;
};