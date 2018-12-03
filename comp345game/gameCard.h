#pragma once
#ifndef DECKCARD_H
#define DECKCARD_H
#include "card.h"
#include "CardObserver.h"
#include <string>

class GameCard : public Card {
	private:
		std::string playType;
		std::string effect;
		int cost;

	public:
		GameCard(std::string n, int t, std::string pt, std::string eff, int c):
			Card::Card(n, t), playType(pt), effect(eff), cost(c), observer(nullptr) {};
		std::string getPlayType() { return playType; };
		std::string getEffect() { return effect; };
		int getCost() { return cost; };

	// |--------------------------------------------------------------------------|
	// |The following section is methods that have to do with the observer pattern|
	// |--------------------------------------------------------------------------|
	private:
		cardObserver* observer;

	public:
		void attach(cardObserver* obs) { observer = obs; };
		void notify();
};

#endif