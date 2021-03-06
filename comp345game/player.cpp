#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <algorithm>
#include "player.h"
#include "diceRoller.h"
#include "gameStart.h"
#include "phaseObserver.h"
#include "turnObserver.h"
using namespace std;

int player::playerId = 1;

//create a default player with an empty string as a name and an automatically assigned id
player::player(){
	name = "";
	id = playerId; playerId++;
	playDice = diceRoller::diceRoller();
	region = Region();
	turnObserver* obs = new turnObserver();
	playDice.attachTurnObs(obs);
	
}
//create a player with an a name and an automatically assigned id
player::player(string name){
	this->name = name;
	id = playerId; playerId++;
	region = Region();
	playDice = diceRoller::diceRoller();
	turnObserver* obs = new turnObserver();
	playDice.attachTurnObs(obs);
}

//giving a monsterCard to a player
void player::setMonsterCard(MonsterCard *monst) {
	monsterCard = monst;
}

bool player::addOwnedCard(GameCard card) {
	std::string cardName = card.getName();
	bool cardNotOwned = true;
	// Ensure that the player doesn't already own the card trying to be added
	for (GameCard c : ownedCards) {
		if (c.getName() == cardName) {
			cardNotOwned = false;
		}
	}

	if (cardNotOwned) {
		if (card.getPlayType().compare("Discard") != 0) {
			card.notify();
			useCardEffect(card);
			gameStart::deck.discardCard(card);
		}
		else {
			ownedCards.push_back(card);
			for (int i = 0; i < gameStart::playersInGame.size(); i++) {
				if (gameStart::playersInGame[i] == this) {
					gameStart::playersInGame[i] = this;
				}
			}
		}
	}
	else {
		return false;
	}

	return true;
}

void player::useCardEffect(GameCard card) {
	string cardName = card.getName();

	if (compare(cardName, "Next Stage")) {
		cout << "You have " << monsterCard->getVP() << " Victory Points." << endl;
		cout << "How many would you like to turn into Energy Points?" << endl;
		cout << "(The remaining VP will heal you for 1 point each)" << endl;

		cin.clear();
		cin.ignore(256, '\n');

		int input;
		cin >> input;

		while (cin.fail() || input != (int)input || (input < 0 || input > monsterCard->getVP())) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Please enter a non-negative number that is less than or equal to your VP." << endl;
			cin >> input;
		}

		monsterCard->changeHP(monsterCard->getVP() - (int)input);
		energy += (int)input;
		monsterCard->changeVP(monsterCard->getVP() * -1);

	} else if (compare(cardName, "Power Substation")) {
		monsterCard->changeHP(-3);
		monsterCard->changeVP(1);
		energy += 8;
	} else if(compare(cardName, "Subterranean Cable")) {
		monsterCard->changeHP(-4);
		energy += 4;
	}
}

bool player::compare(string str1, string str2) {
	return str1.compare(str2) == 0;
}

void player::setOwnedCards(vector<GameCard> cards) {
	this->ownedCards = cards;
}

bool player::transferSpecialCard(string cardName) {
	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		if (gameStart::playersInGame[i]->getName().compare(getName()) != 0){
			vector<GameCard> otherOwnedCards = gameStart::playersInGame[i]->getOwnedCards();
			for (int i = 0; i < otherOwnedCards.size(); i++) {
				if (otherOwnedCards[i].getName().compare(cardName) == 0) {
					addOwnedCard(otherOwnedCards[i]);
					gameStart::playersInGame[i]->ownedCards.erase(gameStart::playersInGame[i]->ownedCards.begin() + i);
					
					if (cardName.compare("Statue of Liberty")) {
						gameStart::playersInGame[i]->getMonsterCard()->changeVP(-3);
					}

					return true;
				}
			}
		}
	}

	return false;
}

void player::addEnergy(int n) {
	if (energy + n > 0)
		energy += n;
}

void player::setEnergy(int energy) {
	this->energy = energy;
}

void player::setRegion(Region region) {
	this->region = region;
}

void player::applyDiceEffect(int effect, int numberOfResolves, Deck* deck)
{
	if (effect == 1 && numberOfResolves > 0)
	{
		addEnergy(numberOfResolves);
		cout << "Energy of quantity " << this->getEnergy() << " has been added to player"<< endl;
	}
	else if (effect == 2 && numberOfResolves > 0)
	{
		monsterCard->changeHP(numberOfResolves);
		cout << "Monster health updated to " << monsterCard->getHP() << " using + " << numberOfResolves << " hp" << endl;
		//monster underfined thus cannot work
	}
	else if (effect == 3 && numberOfResolves > 0)
	{
		//get the static player vector, iterate through the vector, checking the region
		//if the corresponding region is inside or outside manhattan
		//damage according to the dice effect rule

		for (int i = 0; i < gameStart::playersInGame.size(); i++) {

			if (gameStart::playersInGame[i]->getName().compare(name) != 0) {
				if (region.getName() == "Manhattan1" || region.getName() == "Manhattan2" || (region.getName() == "Manhattan3")) {
					if (gameStart::playersInGame[i]->getRegion().getName() != "Manhattan1" && gameStart::playersInGame[i]->getRegion().getName() != "Manhattan2" && (gameStart::playersInGame[i]->getRegion().getName() != "Manhattan3"))
					{
						gameStart::playersInGame[i]->getMonsterCard()->changeHP(-numberOfResolves);
						cout << gameStart::playersInGame[i]->getMonsterCard()->getName() << "'s hp is now " << gameStart::playersInGame[i]->getMonsterCard()->getHP() << " damage dealt " << numberOfResolves << endl;
					}
				}
				else
				{
					if (region.getName() != "Manhattan1" && region.getName() != "Manhattan2" && region.getName() != "Manhattan3")
					{
						if (gameStart::playersInGame[i]->getRegion().getName() == "Manhattan1" || gameStart::playersInGame[i]->getRegion().getName() == "Manhattan2" || gameStart::playersInGame[i]->getRegion().getName() == "Manhattan3")
						{
							gameStart::playersInGame[i]->getMonsterCard()->changeHP(-numberOfResolves);
							cout << gameStart::playersInGame[i]->getMonsterCard()->getName() << "'s hp is now " << gameStart::playersInGame[i]->getMonsterCard()->getHP() << " damage dealt " << numberOfResolves << endl;

							//player in manhattan gets prompted to move
							gameStart::playersInGame[i]->setDamage(true);
							gameStart::playersInGame[i]->move();
						}
					}
				}
			}
		}
	}
	else if (effect == 4 && numberOfResolves > 0) //we need to keep track of superstar card
	{
		//if superstar card is infront of you +1 vp for every numberOfResolves
		if (numberOfResolves > 2)
		{
			//remove superstar card from infront of the previous holder
			if (!(deck->getSpecialCards()[0].getName().compare("Superstar") == 0 || deck->getSpecialCards()[1].getName().compare("Superstar") == 0)) {
				//find the player that has the Superstar card
				transferSpecialCard("Superstar");
			}
			//set superstar card infront of you
			else {
				if (deck->getSpecialCards()[0].getName().compare("Superstar") == 0) {
					deck->getSpecialCards()[0].notify();
					addOwnedCard(deck->getSpecialCards()[0]);
				}
				else {
					deck->getSpecialCards()[0].notify();
					addOwnedCard(deck->getSpecialCards()[1]);
				}
			}

			getMonsterCard()->changeVP(1);
			if (numberOfResolves > 3)
				getMonsterCard()->changeVP(numberOfResolves - 3);
		}
	}
	else if (effect == 5 && numberOfResolves > 0)
	{
		vector<vector<int>> buildings = region.getBuildings();
		for (int i = 0; i < buildings.size(); i++) {
			if (buildings.at(i).size() != 0) {
				if (buildings[i][0] <= numberOfResolves) {
					// Add whatever the tile gives you
					region.flipTile(buildings[i][0], i);
				}
			}
		}
	}
	else if (effect == 6 && numberOfResolves > 0)
	{
		if (numberOfResolves == 1)
		{
			// You suffer 1 damage per unit tile in the bourough
			if (!region.getUnits().empty()) {
				int numOfUnitsInRegion = 0;
				for (vector<int> unit : region.getUnits()) {
					if (!unit.empty())
						numOfUnitsInRegion++;
				}
				monsterCard->changeHP(numOfUnitsInRegion * -1);
			}
		}
		else if (numberOfResolves == 2)
		{
			// All monsters in your borough suffer 1 damage per unit tile of bourough
			if (!region.getUnits().empty()) {
				int numOfUnitsInRegion = 0;
				for (vector<int> unit : region.getUnits()) {
					if (!unit.empty())
						numOfUnitsInRegion++;
				}

				for (int i = 0; i < gameStart::playersInGame.size(); i++) {
					if (gameStart::playersInGame[i]->getRegion().getName().compare(region.getName()) == 0) {
						gameStart::playersInGame[i]->getMonsterCard()->changeHP(numOfUnitsInRegion * -1);
					}
				}

			}
		}
		else if (numberOfResolves > 3)
		{
			// All monsters suffer 1 damage per unit tile in their respective borough
			// Loop through all regions
			for (int i = 0; i < gameStart::mapRegions.size(); i++) {
				int numOfUnitsInRegion = 0;
				for (vector<int> unit : region.getUnits()) {
					if (!unit.empty())
						numOfUnitsInRegion++;
				}

				// Deal damage to all the players in the region
				for (int i = 0; i < gameStart::playersInGame.size(); i++) {
					if (gameStart::playersInGame[i]->getRegion().getName().compare(gameStart::playersInGame[i]->getName()) == 0) {
						gameStart::playersInGame[i]->getMonsterCard()->changeHP(numOfUnitsInRegion * -1);
					}
				}

			}
			
			// Remove superstar card from in front of the previous holder
			if (!(deck->getSpecialCards()[0].getName().compare("Statue of Liberty") == 0 || deck->getSpecialCards()[1].getName().compare("Statue of Liberty") == 0)) {
				// Find the player that has the Superstar card
				transferSpecialCard("Statue of Liberty");
			}
			// Set Statue of Liberty card in front of you
			else {
				if (deck->getSpecialCards()[0].getName().compare("Statue of Liberty") == 0) {
					deck->getSpecialCards()[0].notify();
					addOwnedCard(deck->getSpecialCards()[0]);
				} else {
					deck->getSpecialCards()[0].notify();
					addOwnedCard(deck->getSpecialCards()[1]);
				}
			}

			getMonsterCard()->changeVP(3);
		}
	}

	// Update the rest of the map
	for (int i = 0; i < gameStart::mapRegions.size(); i++) {
		if (gameStart::mapRegions[i] == region) {
			gameStart::mapRegions[i] = region;
		}
	}

	gameStart::map.update(gameStart::mapRegions);
}

int player::firstRoll()
{
	playDice.firstRoll();
	playDice.displayDiceContainer();
	int count = 0;
	for (int i = 0; i < playDice.size(); i++)
	{
		if (playDice.getDiceContainerTop(i).compare("Attack") == 0)
		{
			count++;
		}
			
	}
	cout << "Number of attacks: " << count << endl;
	return count;
}

void player::setDamage(bool setting) {
	damaged = setting;
}

bool player::isDamaged() {
	return damaged;
}

bool player::operator==(const player &o) const {
	return (name == o.name && id == o.id);
}

// ========= Strategy Design ==========
void player::move() {
	this->playerType->move(this);
}

void player::chooseStartingRegion() {
	this->playerType->chooseStartingRegion(this);
}

void player::rollDice() {
	this->playerType->rollDice(this);
}

void player::resolveDice() {
	this->playerType->resolveDice(this);
}

void player::buyCards() {
	this->playerType->buyCards(this);
}

// |--------------------------------------------------------------------------|
// |The following section is methods that have to do with the observer pattern|
// |--------------------------------------------------------------------------|
void player::setState(int newState) {
	state = newState;
	notifyAll();
}

void player::notify(Observer* o) {
	o->update();
}

void player::notifyAll(string phase, string action) {
	for (phaseObserver* obs : observers) {
		obs->update(this, phase, action);
	}
}