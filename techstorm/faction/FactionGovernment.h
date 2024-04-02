#pragma once
#include "FactionGovernmentModifier.h"

namespace TechStormRivalry {
	namespace Faction {
		class FactionGovernment {
		public:
			FactionGovernmentModifier* governmentModifier = nullptr;
			const char* government = "unknown";

			// Max of 1, min of 0.

			// Cohesion is how well oiled the government is, A high cohesion government will respond faster to things, whereas a low cohesion is at political
			// unrest!
			float governmentCohesion = 0.0f;
		};
	}
}
