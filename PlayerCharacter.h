#pragma once
#include "Character.h"
#include "IScriptable.h"
#include "Game.h"

class PlayerCharacter : public Character {
public:

	class PlayerCharacterScriptable : public IScriptable {
	public:
		PlayerCharacterScriptable() {
		}

		// todo : add player specific scriptable functions
		void onUpdate() {}

		void onEnd() {
			delete this;
		}
	};

	// todo : add player specific initialization
	PlayerCharacter(int characterID, EFaction faction) : Character(characterID, true, faction) {
		
		playerScriptable = new PlayerCharacterScriptable();


		Game::scriptManager->addScript(this->getScriptable());
	}

	~PlayerCharacter() {
		Game::scriptManager->removeScript(this->getScriptable()->ID);
	}
	// todo : add player specific functions
	PlayerCharacterScriptable* getScriptable() {
		return playerScriptable;
	}
	

	//todo : add player specific scriptable functions

private:
	PlayerCharacterScriptable* playerScriptable;
};

