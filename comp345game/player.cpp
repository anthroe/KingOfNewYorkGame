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

using namespace std;

int player::playerId = 1;

//create a default player with an empty string as a name and an automatically assigned id
player::player(){
	name = "";
	id = playerId; playerId++;
	playDice = diceRoller::diceRoller();
	region = Region();
	
}
//create a player with an a name and an automatically assigned id
player::player(string name){
	this->name = name;
	id = playerId; playerId++;
	region = Region();
	playDice = diceRoller::diceRoller();
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
		ownedCards.push_back(card);
		for (int i = 0; i < gameStart::playersInGame.size(); i++) {
			if (gameStart::playersInGame[i] == (*this)) {
				gameStart::playersInGame[i] = (*this);
			}
		}
	}
	else {
		return false;
	}

	return true;
}

void player::setOwnedCards(vector<GameCard> cards) {
	this->ownedCards = cards;
}

bool player::transferSpecialCard(string cardName) {
	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		if (gameStart::playersInGame[i].getName().compare(getName()) != 0){
			vector<GameCard> otherOwnedCards = gameStart::playersInGame[i].getOwnedCards();
			for (int i = 0; i < otherOwnedCards.size(); i++) {
				if (otherOwnedCards[i].getName().compare("Superstar") == 0) {
					addOwnedCard(otherOwnedCards[i]);
					gameStart::playersInGame[i].ownedCards.erase(gameStart::playersInGame[i].ownedCards.begin() + i);
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

void player::applyDiceEffect(int effect, int numberOfResolves, Deck deck)
{
	vector<player> players = gameStart::playersInGame;
	vector<Region> regions = gameStart::mapRegions;

	if (effect == 1 && numberOfResolves > 0)
	{
		addEnergy(numberOfResolves);
		cout << "Energy of quantity " << this->getEnergy() << " has been added to player"<< endl;
	}
	else if (effect == 2 && numberOfResolves > 0)
	{
		getMonsterCard()->changeHP(numberOfResolves);
		cout << "Monster health updated to " << getMonsterCard()->getHP() << " using + " << numberOfResolves << " hp" << endl;
		//monster underfined thus cannot work
	}
	else if (effect == 3 && numberOfResolves > 0)
	{
		//get the static player vector, iterate through the vector, checking the region
		//if the corresponding region is inside or outside manhattan
		//damage according to the dice effect rule

		for (int i = 0; i < players.size(); i++) {

			if (players[i].getName().compare(getName()) != 0) {
				if (getRegion().getName() == "Manhattan1" || getRegion().getName() == "Manhattan2" || (getRegion().getName() == "Manhattan3")) {
					if (players[i].getRegion().getName() != "Manhattan1" && players[i].getRegion().getName() != "Manhattan2" && (players[i].getRegion().getName()
						!= "Manhattan3"))
					{
						players[i].getMonsterCard()->changeHP(-numberOfResolves);
						cout << players[i].getMonsterCard()->getName() << "'s hp is now " << players[i].getMonsterCard()->getHP() << " damage dealt " << numberOfResolves << endl;
					}
				}
				else
				{
					if (getRegion().getName() != "Manhattan1" && getRegion().getName() != "Manhattan2" && getRegion().getName() != "Manhattan3")
					{
						if (players[i].getRegion().getName() == "Manhattan1" || players[i].getRegion().getName() == "Manhattan2" || players[i].getRegion().getName() == "Manhattan3")
						{
							players[i].getMonsterCard()->changeHP(-numberOfResolves);
							cout << players[i].getMonsterCard()->getName() << "'s hp is now " << players[i].getMonsterCard()->getHP() << " damage dealt " << numberOfResolves << endl;

							//player in manhattan gets prompted to move
							players[i].setDamage(true);
							players[i].move();
							regions = gameStart::mapRegions;
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
			if (!(deck.getSpecialCards()[0].getName().compare("Superstar") == 0 || deck.getSpecialCards()[1].getName().compare("Superstar") == 0)) {
				//find the player that has the Superstar card
				transferSpecialCard("Superstar");
			}
			//set superstar card infront of you
			else {
				if (deck.getSpecialCards()[0].getName().compare("Superstar") == 0)
					addOwnedCard(deck.getSpecialCards()[0]);
				else
					addOwnedCard(deck.getSpecialCards()[1]);
			}
			getMonsterCard()->changeVP(1);
			if (numberOfResolves > 3)
			{
				getMonsterCard()->changeVP(numberOfResolves - 3);
			}
		}
	}
	else if (effect == 5 && numberOfResolves > 0)
	{
		vector<vector<int>> buildings = region.getBuildings();
		for (int i = 0; i < buildings.size(); i++) {
			if (buildings[i][0] <= numberOfResolves)
				// Add whatever the tile gives you
				region.flipTile(buildings[i][0], i);
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

				for (int i = 0; i < players.size(); i++) {
					if (players[i].getRegion().getName().compare(region.getName()) == 0) {
						players[i].getMonsterCard()->changeHP(numOfUnitsInRegion * -1);
					}
				}

			}
		}
		else if (numberOfResolves > 3)
		{
			// All monsters suffer 1 damage per unit tile in their respective bourough
			// Loop through all regions
			for (Region reg : regions) {
				int numOfUnitsInRegion = 0;
				for (vector<int> unit : region.getUnits()) {
					if (!unit.empty())
						numOfUnitsInRegion++;
				}

				// Deal damage to all the players in the region
				for (int i = 0; i < players.size(); i++) {
					if (players[i].getRegion().getName().compare(reg.getName()) == 0) {
						players[i].getMonsterCard()->changeHP(numOfUnitsInRegion * -1);
					}
				}

			}
			//place status of liberty infront
		}
	}

	gameStart::playersInGame = players;
	gameStart::mapRegions = regions;
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

void player::notifyAll() {
	for (phaseObserver* obs : observers) {
		obs->update();
	}
}