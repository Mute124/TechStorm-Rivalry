#pragma once

namespace TechStormRivalry {
	namespace Faction {
		typedef enum EFactionActionType {
			EACTION_WAR = 0,
			EACTION_ATROCITY,
			EACTION_GENOCIDE,
			EACTION_ALLIANCE,
			EACTION_TRADE,
			EACTION_TREATY
		};

		class IFactionAction abstract {
		protected:
			EFactionActionType actionType;
			bool m_shouldUpdate = true;
		public:

			// Should the game update this action?
			virtual bool shouldUpdate() {}

			// Commence the action
			virtual bool actOn() {}
		};
	}
}
