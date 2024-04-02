#pragma once
#include "FactionPersonality.h"
#include "FactionGovernment.h"
#include "EFactionAction.h"
#include <map>
namespace TechStormRivalry {
	namespace Faction
	{
		class CharacterFaction;

		// What the faction's "personality" is like. Are they aggressive? What do they hate? etc
		class FactionTendencies {
		protected:

			float m_hostility = 0.0f;
			float m_suspicion = 0.0f;

			EFactionPersonality m_personality;

		public:

			void precomputeTendencies(EFactionPersonality personality, float suspicion) {
			}
		};

		class FactionRelation {
		protected:
			unsigned int otherFaction = 0;

			// Important : Minimum value of 0, maximum of 100!
			float suspicionLevel = 50.0f;
			float hostilityLevel = 0.0f; // when it reaches 75, it can declare war.
			float friendlynessLevel = 0.0f;

			friend class CharacterFaction;

		public:
		};

		class CharacterFaction {
		private:
			FactionTendencies m_tendencies;
			std::map<CharacterFaction*, FactionRelation> m_relations;

		public:
			const char* name = "null";
			unsigned int power = 0;
			unsigned int factionID = 0;
			bool isPlayerFaction;

			bool isFriendlyWith(CharacterFaction& other) {
			}

			bool isHostileWith(CharacterFaction& other) {
			}
		};
	}
}
