#pragma once

namespace TechStormRivalry {
	namespace Faction {
		class FactionTrait {
		protected:

			// how much does this trait affect it's parent trait? The delta
			float m_traitAffect = 0.0f;
			FactionTrait* m_parentTrait = nullptr;
			const bool isParent = false;
		public:
			FactionTrait(float affect, FactionTrait* parent) : m_traitAffect(affect), m_parentTrait(parent) {
			}
			FactionTrait(float affect) : m_traitAffect(affect), isParent(true) {
			}
		};
	}
}
