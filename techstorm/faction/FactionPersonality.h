#pragma once

namespace TechStormRivalry {
	namespace Faction {
		/*
		* Faction personality is one of the many things that are taken in account when making decisions. This defines what path they will choose.
		*
		* Malevolent : The faction is self interested and does not care about others. Will choose the option that benefits them the most. Even if it is evil
		*	They prefer	the "evil" option.
		*
		* Pragmatic : The faction is practical, they make decisions based on practicality, their benifits, etc. Switches between evil and good decisions.
		*	They prefer the profitable action, and will do what ever is profitable
		*
		* Benevolent : The faction will always do the "good" thing.
		*	They prefer diplomacy, unity, and freedom
		*
		*/
		typedef enum EFactionPersonality {
			EPERSONALITY_MALEVOLENT = 0,
			EPERSONALITY_PRAGMATIC,
			EPERSONALITY_BENEVOLENT
		};

		class FactionPersonality {
		public:
			EFactionPersonality personality;
		};
	}
}
