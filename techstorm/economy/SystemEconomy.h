#pragma once
#include "../faction/CharacterFaction.h"
#include "MarketProduct.h"
#include "../inventory/Item.h"
#include <map>

namespace TechStormRivalry::Economy {
	static inline int economyUpdateInterval = 300; // how many frames before a new update needs to happen.

	typedef struct MarketPurchase {
		int value = 0; // Make negative if it cost the faction money, if not then it is positive
		bool wasSuccessful = false;
	};

	class Merchant {
	private:

	public:
		static inline std::map<unsigned int, MarketProduct> m_market;

		void m_updateMarketValue(MarketProduct& item) {
			float modifier = 1;

			// if the demand is higher than the supply, we know this is scarce! meaning the price skyrockets!
			if (item.demand > item.supply) {
				modifier = (item.demand - item.supply) / item.baseValue;
			}
			item.buyPrice = (abs(item.baseValue * (item.supply - item.demand)) * modifier) + (item.buyPrice * m_priceUptick);
			item.sellPrice = abs(item.baseValue * (item.supply - item.demand)) / modifier;
		}

		// Normalized value, 0 to 1. 1 is 100%
		float m_priceUptick;

		// Who owns this merchant.
		Faction::CharacterFaction* m_owner = nullptr;
		static inline bool canBuy(unsigned int product, unsigned int amount) {
			int supply = m_market[product].supply;
			return supply >= amount;
		}

		// returns true IF buy order went through.
		MarketPurchase buy(unsigned int product, unsigned int amount, Faction::CharacterFaction& buyer) {
			MarketProduct& item = m_market[product];
			MarketPurchase purchase = { 0 };

			purchase.wasSuccessful = false;
			if (canBuy(product, amount) && (!m_owner->hasEmbargoOn(buyer))) {
				item.demand += amount;
				item.supply -= amount;

				purchase.value = -((item.buyPrice + (item.buyPrice * m_priceUptick)) * amount);
				purchase.wasSuccessful = true;
				m_updateMarketValue(item);
			}

			return purchase;
		}

		MarketPurchase sell(unsigned int product, unsigned int amount, Faction::CharacterFaction& seller) {
			MarketProduct& item = m_market[product];
			MarketPurchase purchase = { 0 };

			if (!m_owner->hasEmbargoOn(seller)) {
				item.demand = item.demand - amount;
				if (item.demand < 0) {
					item.demand = 0;
				}
				item.supply += amount;

				purchase.wasSuccessful = true;
				purchase.value = item.sellPrice * amount;

				m_updateMarketValue(item);
			}

			return purchase;
		}
	};
}
