#include "cardtest.h"
#include "deck.h"
#include "tokens.h"
#include "unitTiles.h"
#include <iostream>
#include <fstream>
#include <list>
#include "libraries/json.hpp"
using json = nlohmann::json;

int cardDriver() {
	json monsterCardListJson;
	Deck::getCardList("resources/kony-monster-card-list.json") >> monsterCardListJson;

	// Build a list of MonsterCard objects listing monsters cards
	vector<MonsterCard> ListOfMonsterCards;
	for (json card : monsterCardListJson) {
		string cname = card["name"];
		ListOfMonsterCards.push_back(MonsterCard(cname));
	}

	// Testing Monster Card Functions
	for (MonsterCard card : ListOfMonsterCards) {
		cout << "Monster card name: " << card.getName() << endl;
		cout << "Monster card type: " << card.getTypeName() << endl;
		cout << "Monster card HP: " << card.getHP() << endl;
		cout << "Monster card effect: " << card.getVP() << "\n" << endl;
	}

	// Testing Monster Card Functions
	if (!ListOfMonsterCards[0].changeHP(-1))
		cout << "HP could not decrease" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;
	if (!ListOfMonsterCards[0].changeHP(1))
		cout << "HP could not increase" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;
	if (!ListOfMonsterCards[0].changeHP(1))
		cout << "HP is at max" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;
	if (!ListOfMonsterCards[0].changeHP(-10))
		cout << "HP could not decrease" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;
	if (!ListOfMonsterCards[0].changeHP(-1))
		cout << "HP is at min" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;

	if (!ListOfMonsterCards[0].changeVP(-1))
		cout << "VP is at minimum" << endl;
	cout << "VP: " << ListOfMonsterCards[0].getVP() << endl;
	if (!ListOfMonsterCards[0].changeVP(1))
		cout << "VP could not increase" << endl;
	cout << "VP: " << ListOfMonsterCards[0].getVP() << endl;
	if (!ListOfMonsterCards[0].changeVP(-1))
		cout << "VP could not decrease" << endl;
	cout << "VP: " << ListOfMonsterCards[0].getVP() << endl;
	if (!ListOfMonsterCards[0].changeVP(20))
		cout << "VP could not increase (20)" << endl;
	cout << "VP: " << ListOfMonsterCards[0].getVP() << endl;
	if (!ListOfMonsterCards[0].changeVP(1))
		cout << "VP is at max" << endl;
	cout << "VP: " << ListOfMonsterCards[0].getVP() << endl;

	// Testing Deck Fucntions
	Deck d;
	cout << "Before Delete:" << endl;
	for (GameCard gc : d.getPurchaseableCards()) {
		cout << "Deck card name: " << gc.getName() << endl;
		cout << "Deck card type: " << gc.getTypeName() << endl;
		cout << "Deck card HP: " << gc.getCost() << endl;
		cout << "Deck card effect: " << gc.getEffect() << "\n" << endl;
	}

	cout << "\n\n\nAfter Delete:" << endl;
	if (d.discardCard(d.getPurchaseableCards()[1])) {
		d.shuffle();
		for (GameCard gc : d.getPurchaseableCards()) {
			cout << "Deck card name: " << gc.getName() << endl;
			cout << "Deck card type: " << gc.getTypeName() << endl;
			cout << "Deck card HP: " << gc.getCost() << endl;
			cout << "Deck card effect: " << gc.getEffect() << "\n" << endl;
		}
	}
	else
		cout << "Could not delete from Purchaseable Cards." << endl;

	cout << "\n\n\nDeck Delete:" << endl;
	if (d.discardCard(d.getDeck()[5])) {
		d.shuffle();
		for (GameCard gc : d.getPurchaseableCards()) {
			cout << "Deck card name: " << gc.getName() << endl;
			cout << "Deck card type: " << gc.getTypeName() << endl;
			cout << "Deck card HP: " << gc.getCost() << endl;
			cout << "Deck card effect: " << gc.getEffect() << "\n" << endl;
		}
	}
	else
		cout << "Could not delete from Deck." << endl;

	// Test Token Functions
	Tokens tok;

	// Carapace functions
	if (!tok.setCarapace(-1))
		cout << "Carapace could not decrease" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;
	if (!tok.setCarapace(1))
		cout << "Carapace could not increase" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;
	if (!tok.setCarapace(1))
		cout << "Carapace is at max" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;
	if (!tok.setCarapace(-15))
		cout << "Carapace could not decrease" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;
	if (!tok.setCarapace(-1))
		cout << "Carapace is at min" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;

	// Jinx functions
	if (!tok.setJinx(-1))
		cout << "Jinx could not decrease" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;
	if (!tok.setJinx(1))
		cout << "Jinx could not increase" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;
	if (!tok.setJinx(1))
		cout << "Jinx is at max" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;
	if (!tok.setJinx(-13))
		cout << "Jinx could not decrease" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;
	if (!tok.setJinx(-1))
		cout << "Jinx is at min" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;

	// Souvenir functions
	if (!tok.setSouvenir(-1))
		cout << "Souvenir could not decrease" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;
	if (!tok.setSouvenir(1))
		cout << "Souvenir could not increase" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;
	if (!tok.setSouvenir(1))
		cout << "Souvenir is at max" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;
	if (!tok.setSouvenir(-5))
		cout << "Souvenir could not decrease" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;
	if (!tok.setSouvenir(-1))
		cout << "Souvenir is at min" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;

	// Web functions
	if (!tok.setWeb(-1))
		cout << "Web could not decrease" << endl;
	cout << "Web: " << tok.getWeb() << endl;
	if (!tok.setWeb(1))
		cout << "Web could not increase" << endl;
	cout << "Web: " << tok.getWeb() << endl;
	if (!tok.setWeb(1))
		cout << "Web is at max" << endl;
	cout << "Web: " << tok.getWeb() << endl;
	if (!tok.setWeb(-13))
		cout << "Web could not decrease" << endl;
	cout << "Web: " << tok.getWeb() << endl;
	if (!tok.setWeb(-1))
		cout << "Web is at min" << endl;
	cout << "Web: " << tok.getWeb() << endl;

	// Unit Tiles Functions
	UnitTiles ut;
	vector<int> tiles = ut.getTiles();

	cout << "\nBefore shuffle:" << endl;
	for (int i = 0; i < 45; i++) {
		cout << tiles[i] << ' ';
	}

	ut.shuffle();
	tiles = ut.getTiles();

	cout << endl << "\nAfter shuffle:" << endl;
	for (int i = 0; i < 45; i++) {
		cout << tiles[i] << ' ';
	}

	cin.get();

	return 0;
}