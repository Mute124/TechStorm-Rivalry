#pragma once

namespace TechStormRivalry {
	namespace Faction {
		class FactionRelation {
		private:

			// Important : Minimum value of 0, maximum of 100!
			float m_suspicionLevel = 50.0f;
			float m_hostilityLevel = 0.0f; // when it reaches 75, it can declare war.
			float m_friendlynessLevel = 0.0f;

			bool m_activeEmbargo = false;
			bool m_atWar = false;
		public:

			bool isAtWar() {
				return this->m_atWar;
			}

			bool hasActiveTradeEmbargo() {
				return this->m_activeEmbargo;
			}
		};
	}
}
