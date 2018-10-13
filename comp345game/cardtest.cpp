#include "cardtest.h"
#include "deck.h"
#include "tokens.h"
#include "unitTiles.h"
#include <ctime>
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
	cout << "Testing Monster Card Functions" << endl;
	for (MonsterCard card : ListOfMonsterCards) {
		cout << "Monster card name: " << card.getName() << endl;
		cout << "Monster card HP: " << card.getHP() << endl;
		cout << "Monster card effect: " << card.getVP() << "\n" << endl;
	}

	// Testing Monster Card HP and VP Functions
	cout << "Testing Monster Card HP Function" << endl;
	if (!ListOfMonsterCards[0].changeHP(-1))
		cout << "HP could not decrease" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;
	if (!ListOfMonsterCards[0].changeHP(1))
		cout << "HP could not increase" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;
	if (!ListOfMonsterCards[0].changeHP(1))
		cout << "HP is at maximum; did not increase" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;
	if (!ListOfMonsterCards[0].changeHP(-10))
		cout << "HP could not decrease" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;
	if (!ListOfMonsterCards[0].changeHP(-1))
		cout << "HP is at min; did not decrease" << endl;
	cout << "HP: " << ListOfMonsterCards[0].getHP() << endl;

	cout << "\nTesting Monster Card VP Functions" << endl;
	if (!ListOfMonsterCards[0].changeVP(-1))
		cout << "VP is at minimum; did not decrease" << endl;
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
		cout << "VP is at maximum; did not increase" << endl;
	cout << "VP: " << ListOfMonsterCards[0].getVP() << endl;

	// Testing Deck Fucntions
	cout << "\nTesting Deck Functions" << endl;
	Deck d;
	cout << "Current Purchaseable Cards:" << endl;
	for (GameCard gc : d.getPurchaseableCards()) {
		cout << gc.getName() << endl;
	}

	cout << "\nAfter Delete:" << endl;
	if (d.discardCard(d.getPurchaseableCards()[1])) {
		d.shuffle();
		for (GameCard gc : d.getPurchaseableCards()) {
			cout << gc.getName() << endl;
		}
	} else
		cout << "Could not delete from Purchaseable Cards." << endl;

	cout << "\nAfter Deleting from Deck (should not alter purchaseable cards):\nPurchaseable Cards:" << endl;
	if (d.discardCard(d.getDeck()[5])) {
		d.shuffle();
		for (GameCard gc : d.getPurchaseableCards()) {
			cout << gc.getName() << endl;
		}
	}
	else
		cout << "Could not delete from Deck." << endl;

	// Test Token Functions
	cout << "\nTesting Token Functions" << endl;
	Tokens tok;

	// Carapace functions
	cout << "Testing Carapace Token Functions" << endl;
	if (!tok.setCarapace(-1))
		cout << "Carapace could not decrease" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;
	if (!tok.setCarapace(1))
		cout << "Carapace could not increase" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;
	if (!tok.setCarapace(1))
		cout << "Carapace is at maximum; did not increase" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;
	if (!tok.setCarapace(-15))
		cout << "Carapace could not decrease" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;
	if (!tok.setCarapace(-1))
		cout << "Carapace is at min; did not decrease" << endl;
	cout << "Carapace: " << tok.getCarapace() << endl;

	// Jinx functions
	cout << "\nTesting Jinx Token Functions" << endl;
	if (!tok.setJinx(-1))
		cout << "Jinx could not decrease" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;
	if (!tok.setJinx(1))
		cout << "Jinx could not increase" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;
	if (!tok.setJinx(1))
		cout << "Jinx is at maximum; did not increase" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;
	if (!tok.setJinx(-13))
		cout << "Jinx could not decrease" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;
	if (!tok.setJinx(-1))
		cout << "Jinx is at min; did not decrease" << endl;
	cout << "Jinx: " << tok.getJinx() << endl;

	// Souvenir functions
	cout << "\nTesting Souvenir Token Functions" << endl;
	if (!tok.setSouvenir(-1))
		cout << "Souvenir could not decrease" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;
	if (!tok.setSouvenir(1))
		cout << "Souvenir could not increase" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;
	if (!tok.setSouvenir(1))
		cout << "Souvenir is at maximum; did not increase" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;
	if (!tok.setSouvenir(-5))
		cout << "Souvenir could not decrease" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;
	if (!tok.setSouvenir(-1))
		cout << "Souvenir is at min; did not decrease" << endl;
	cout << "Souvenir: " << tok.getSouvenir() << endl;

	// Web functions
	cout << "\nTesting Web Token Functions" << endl;
	if (!tok.setWeb(-1))
		cout << "Web could not decrease" << endl;
	cout << "Web: " << tok.getWeb() << endl;
	if (!tok.setWeb(1))
		cout << "Web could not increase" << endl;
	cout << "Web: " << tok.getWeb() << endl;
	if (!tok.setWeb(1))
		cout << "Web is at maximum; did not increase" << endl;
	cout << "Web: " << tok.getWeb() << endl;
	if (!tok.setWeb(-13))
		cout << "Web could not decrease" << endl;
	cout << "Web: " << tok.getWeb() << endl;
	if (!tok.setWeb(-1))
		cout << "Web is at min; did not decrease" << endl;
	cout << "Web: " << tok.getWeb() << endl;

	// Unit Tiles Functions
	cout << "\nTesting Unit Tiles Functions" << endl;
	UnitTiles ut;
	vector<int> tiles = ut.getTiles();

	cout << "Before shuffle:" << endl;
	for (int i = 0; i < 45; i++) {
		cout << tiles[i] << ' ';
	}

	ut.shuffle();
	tiles = ut.getTiles();

	cout << endl << "\nAfter shuffle:" << endl;
	for (int i = 0; i < 45; i++) {
		cout << tiles[i] << ' ';
	}

	cout << "\n" << endl;

	return 0;
}