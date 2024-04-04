#pragma once

namespace TechStormRivalry::Economy {
	/*
* This is a product that can be found within the system's market. It's sell and buy price are the base, and each merchant can add onto the base price.
*
* Value of the product is determined by supply and demand.
*
* Supply represents how much exists within the game simulation, the demand is representative of how often and how much is bought within each update cycle
*/
	typedef struct MarketProduct {
		int baseValue;
		float sellPrice;
		float buyPrice;

		int supply;
		int demand;
	};
}
