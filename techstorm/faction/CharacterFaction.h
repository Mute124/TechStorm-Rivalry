#pragma once
#include "FactionPersonality.h"
#include "FactionGovernment.h"
#include "EFactionAction.h"
#include "../Common.h"
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
		private:
			CharacterFaction* m_otherFaction;
			

			// Important : Minimum value of 0, maximum of 100!
			float m_suspicionLevel = 50.0f;
			float m_hostilityLevel = 0.0f; // when it reaches 75, it can declare war.
			float m_friendlynessLevel = 0.0f;

			bool m_activeEmbargo = false;
		public:

			bool hasActiveTradeEmbargo() {
				return this->m_activeEmbargo;
			}

		

		};

		class CharacterFaction {
		private:
			
			int m_balance;
			FactionGovernment government;
			
			FactionTendencies m_tendencies;
			std::map<CharacterFaction*, FactionRelation> m_relations;

		public:
			const char* name = "null";
			unsigned int factionID = 0;
			bool isPlayerFaction;

			void meetFaction(CharacterFaction& other) {
				m_relations[&other] = FactionRelation();
			}

			

			void embargo(CharacterFaction& other) {
				m_relations[&other];
			}

			bool hasEmbargoOn(CharacterFaction& other) {
				return m_relations[&other].hasActiveTradeEmbargo();
			}

			bool isFriendlyWith(CharacterFaction& other) {
			}

			bool isHostileWith(CharacterFaction& other) {
			}


		};
	}
}
