#pragma once
#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "gameCard.h"
#include "monsterCard.h"
#include "cardTypes.h"
#include <vector>

class Deck {
	private:
		std::vector<GameCard> deck;
		std::vector<GameCard> purchaseableCards;
		std::vector<GameCard> specialCards;
		std::vector<GameCard> discard;

	public:
		static std::ifstream getCardList(std::string fileName, bool verbose = false);
		Deck(std::string deckFile = "resources/kony-card-list.json", std::string specialFile = "resources/kony-special-card-list.json");
		std::vector<GameCard> getPurchaseableCards() { return purchaseableCards; };
		std::vector<GameCard> getDeck() { return deck; };
		void shuffle();
		bool discardCard(GameCard card);
		GameCard purchaseCard(GameCard card);
};

#endif