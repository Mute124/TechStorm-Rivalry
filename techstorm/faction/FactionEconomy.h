#pragma once

namespace TechStormRivalry {
	namespace Faction {
		class FactionIndustry {
		protected:
			int m_industryUpkeep;
			int m_industryOutput;
		};

		class FactionEconomy : private FactionIndustry {
		protected:
			int m_balance;
		public:

			// update the economic status
			void tickEconomy() {
			}
		};
	}
}
