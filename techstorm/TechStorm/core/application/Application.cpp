#include "../../pch.h"
#include "Application.h"

#include "../rendering/Renderer.h"
#include "../ui/UIMan.h"
#include "../window/Display.h"
#include "../obj/Gameobject.h"
#include "../logging/Logman.h"
#include "../rendering/Renderer.h"
#include "../assets/AssetLoader.h"

namespace TechStorm {
	class Application : public Display, public LuaManager, public ConfigMan, public Logman, public PBRRenderer {
	protected:

	public:

		AssetLoader* assets;
		Font defaultFont;
		int targetFPS = 60;
		static inline Application* appInstance = nullptr;

		Application() {}

		// loads config man BEFORE anything else
		virtual void preInitialize() {
			SetTraceLogCallback(Logman::customLog);
			this->initConfigMan();
		}

		virtual void initApplication(int winWidth, int winHeight, const char* winTitle, unsigned int flags) {
			this->initLua();
			this->initPBR(uDimension(winWidth, winHeight));
			assets = new AssetLoader();
			InitAudioDevice(); // starts the audio driver(s).
		}

	protected:
		chrono::high_resolution_clock::time_point lastUpdate;
	};
}
