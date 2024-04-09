#include "DiscordAPI.h"
#include <discord-game-sdk/discord.h>
#include <string>

typedef struct discordData {
	const discord::ClientId clientID = 1225493782707834975;
	discord::Core* core = { 0 };
	discord::Activity activity{};
	discord::Presence presence{};
};

static discordData data = { 0 };

void logMSG(discord::LogLevel level, const char* msg) {
	printf(msg);
}

void TechStormRivalry::DiscordAPI::initAPI() {

	//data.core->SetLogHook(discord::LogLevel::Info, &logMSG);

	auto result = discord::Core::Create(1225493782707834975, DiscordCreateFlags_NoRequireDiscord, &data.core);

	data.activity.SetType(discord::ActivityType::Playing);
	data.activity.SetApplicationId(1225493782707834975);
	data.activity.GetAssets().SetLargeText("Test");
	data.activity.SetDetails("Owo?");
	this->update();

	//activity.SetState("Testing");
	//activity.SetDetails("Fruit Loops");
}

void TechStormRivalry::DiscordAPI::update() {
	data.core->RunCallbacks();

	data.core->ActivityManager().UpdateActivity(data.activity, [](discord::Result result) {

		//printf("\nresult = %i\n", result);
		});
}
