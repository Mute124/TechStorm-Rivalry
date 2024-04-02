#pragma once
#include "../inventory/Item.h"
#include <map>

namespace TechStormRivalry::Economy {
	static inline int economyUpdateInterval = 300; // how many frames before a new update needs to happen.

	/*
	* This is a product that can be found within the system's market. It's sell and buy price are the base, and each merchant can add onto the base price.
	*
	* Value of the product is determined by supply and demand.
	*
	* Supply represents how much exists within the game simulation, the demand is representative of how often and how much is bought within each update cycle
	*/
	typedef struct MarketProduct {
		int sellPrice;
		int buyPrice;
		int supply;
		int demand;
	};

	class SystemMarket {
	private:
		static inline std::map<int, MarketProduct> m_market;
	public:
		
		// returns true IF buy order went through.
		bool buy(unsigned int product, unsigned int amount) {

		}


	};
}
