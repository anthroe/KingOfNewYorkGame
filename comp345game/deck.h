#pragma once
#ifndef DECK_H
#define DECK_H
#include "card.h"
#include "gameCard.h"
#include "monsterCard.h"
#include "cardTypes.h"
#include <vector>

using namespace std;

class Deck {
	private:
		vector<GameCard> deck;
		vector<GameCard> purchaseableCards;
		vector<GameCard> specialCards;
		vector<GameCard> discard;

	public:
		static ifstream getCardList(string fileName, bool verbose = false);
		Deck(string deckFile = "resources/kony-card-list.json", string specialFile = "resources/kony-special-card-list.json");
		vector<GameCard> getPurchaseableCards() { return purchaseableCards; };
		vector<GameCard> getDeck() { return deck; };
		vector<GameCard> getSpecialCards() { return specialCards; };
		void shuffle();
		bool discardCard(GameCard card);
		GameCard purchaseCard(GameCard card);
};

#endif