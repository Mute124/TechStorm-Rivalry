#pragma once

#include "../../common.h"
#include "../rendering/Light.h"
#include "../../player/Player.h"
#include "../scripting/ScriptManager.h"
#include "../rendering/Renderers.h"
#include "../ui/UIMan.h"
#include "../../lua/LuaManager.h"
#include "../window/Display.h"
#include "../obj/Gameobject.h"
#include "../logging/Logman.h"

#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <any>

class Application abstract : public Display, public LuaManager, public UIMan, public ConfigMan, public GameobjectManager, public ScriptManager, public Logman {
public:
	Font defaultFont;
	int targetFPS = 60;

	// loads config man BEFORE anything else
	void preInitialize() {
		this->initConfigMan();
		SetTraceLogCallback(Logman::customLog);
	}
	void initApplication(int winWidth, int winHeight, const char* winTitle, unsigned int flags) {
		
		this->initDisplay(winWidth, winHeight, winTitle, flags);
		this->initConfigMan();
		this->initLua();
		this->initUIMan();
		InitAudioDevice(); // starts the audio driver(s).
	}

protected:
	chrono::high_resolution_clock::time_point lastUpdate;


};
