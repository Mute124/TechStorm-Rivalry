#pragma once
#include "../../util/Modifier.h"

namespace TechStormRivalry {
	namespace Faction {
		class FactionGovernmentModifier {
		protected:
			virtual void setupModifier() {
			}

			Modifierf m_govModifier = 0.0f;
		public:

			void changeBy(float delta) {
				this->m_govModifier += (delta / 100.0f);
			}

			float getModifier() {
				return this->m_govModifier;
			}

			bool isAtMax() {
			}
		};
	}
}
