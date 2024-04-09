#pragma once
#include <raylib.h>
namespace TechStormRivalry {

	// since discord conflicts with some raylib stuff, we have to have the implementation AND variables within the .cpp file. However it has been designed to not need anything.
	class DiscordAPI
	{
	public:

		void initAPI();

		void update();
	};
}
