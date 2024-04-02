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
#include "../rendering/Renderer.h"

#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <any>

namespace TechStorm {
	typedef struct ApplicationState;

	class Application : public Display, public LuaManager, public ConfigMan, public ScriptManager, public Logman, public PBRRenderer {
	protected:

		static void p_makeCustomProject(Application* customApp) {
			Application::appInstance = customApp;
			p_usingCustomApplication = true;
		}

		static inline bool p_usingCustomApplication = false;

	public:
		Font defaultFont;
		int targetFPS = 60;
		static inline Application *appInstance = nullptr;
		
		Application()  {}

		// loads config man BEFORE anything else
		virtual void preInitialize() {
			SetTraceLogCallback(Logman::customLog);
			this->initConfigMan();
		}

		virtual void initApplication(int winWidth, int winHeight, const char* winTitle, unsigned int flags) {

			
			this->initLua();
			this->initPBR(uDimension(winWidth, winHeight));
			
			InitAudioDevice(); // starts the audio driver(s).
			
			if (!p_usingCustomApplication) {
				appInstance = this;
			}	
		}

	protected:
		chrono::high_resolution_clock::time_point lastUpdate;
	};
}
