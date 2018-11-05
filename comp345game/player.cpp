#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <algorithm>
#include "player.h"
#include "diceRoller.h"
#include "gameStart.h"

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
	

	if (cardNotOwned)
		ownedCards.push_back(card);
	else
		return false;

	return true;
}

bool player::transferSpecialCard(string cardName) {
	for (player otherPlayer : gameStart::playersInGame) {
		if (otherPlayer.getName().compare(getName()) != 0){
			vector<GameCard> otherOwnedCards = otherPlayer.getOwnedCards();
			for (int i = 0; i < otherOwnedCards.size(); i++) {
				if (otherOwnedCards[i].getName().compare("Superstar") == 0) {
					addOwnedCard(otherOwnedCards[i]);
					otherPlayer.ownedCards.erase(otherPlayer.ownedCards.begin() + i);
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
//creating a diceRoller object for the player and rolling the dice
void player::rollDice() {
	playDice.playerRoll();
}

//player moves to a different region
void player::move() {
	if (region == Region()) {
		cout << "Cannot move " + name + ". This player's region has not been set yet." << endl;
		return;
	}

	vector<Region> zones = region.getNeighbours();
	float input;

	cout << "It is " + name + "'s turn to move." << endl;
	cout << "Current location: " + region.getName() << endl;
	cout << "Choose destination: " << endl;

	for (int i = 0; i < zones.size(); i++) {
		cout << i << ". " + zones[i].getName() + "	";
	}

	cin >> input;

	while (cin.fail() || input != (int)input || (input < 0 || input > zones.size() - 1)) {
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input;
	}

	input = (int)input;
	setRegion(zones[input]);
}

void player::move_kony() {
	if (region == Region()) {
		cout << "Cannot move " + name + ". This player's region has not been set yet." << endl;
		return;
	}

	vector<Region> zones = region.getNeighbours();
	vector<Region> moveableAreas;
	float input;
	int lowManIndex = -1;
	int midManIndex = -1;
	int uppManIndex = -1;

	for (int i = 0; i < zones.size(); i++) {
		if (zones[i].getName() == "Manhattan1") {
			lowManIndex = i;
		}
		else if (zones[i].getName() == "Manhattan2") {
			midManIndex = i;
		}
		else if (zones[i].getName() == "Manhattan3") {
			uppManIndex = i;
		}
		else if (zones[i].getPlayerCount() < 2) {
			moveableAreas.push_back(zones[i]);
		}
	}

	cout << "It is " + name + "'s turn to move." << endl;
	cout << "Current location: " + region.getName() << endl;

	//=================================================================================================
	//if the player is in upper manhattan, he cannot move.
	if (region.getName() == "Manhattan2") {
		cout << name + " cannot move." << endl << endl;
		return;
	}

	//=================================================================================================
	//if the player is in lower or middle manhattan, he advances to the next zone.
	//this player can only move anywhere other than manhattan if attacked.
	if (region.getName() == "Manhattan1") {
		setRegion(zones[midManIndex]);
		cout << name + " was moved to middle manhattan." << endl << endl;
		return;
	}

	if (region.getName() == "Manhattan2") {
		setRegion(zones[uppManIndex]);
		cout << name + " was moved to upper Manhattan." << endl << endl;
		return;
	}

	//=================================================================================================
	//if no one is in Manhattan. the player moves to lower Manhattan
	if (zones[lowManIndex].getPlayerCount() == 0 && zones[uppManIndex].getPlayerCount() == 0) {
		setRegion(zones[lowManIndex]);
		cout << "Manhattan is empty. " + name + " was moved to lower manhattan." << endl << endl;
		return;
	}

	//=================================================================================================
	//manhattan is occupied, the player may move elsewhere.

	cout << "Manhattan is occupied. Choose destination: " << endl;

	for (int i = 0; i < moveableAreas.size(); i++) {
		cout << i << ". " + moveableAreas[i].getName() + "	";
	}

	cin >> input;

	while (cin.fail() || input != (int)input || (input < 0 || input > zones.size() - 1)) {
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input;
	}

	input = (int)input;
	setRegion(moveableAreas[input]);

	cout << name + " moved to " + region.getName() + ". " << endl << endl;
}

void player::setRegion(Region region) {
	if (this->region != Region()) {
		this->region.reducePlayerCount();
	}

	region.increasePlayerCount();
	this->region = region;
}

void player::buyCards(Deck deck) {
	// Store the response in a character
	string response;
	response = buyCardPrompt("Would you like to buy a card ? (Y / N)");

	// If they want to buy a card, show them what they can buy
	if (responseToBool(response)) {
		do {
			// Ask which card they want to buy, and repeat until they answer properly
			int i = deck.getPurchaseableCards().size();
			do {
				cout << "\nYou have " << energy << " energy." << endl;
				cout << "Which card would you like to buy? (Enter the row number)" << endl;

				// Give a list of cards
				for (int i = 0; i < deck.getPurchaseableCards().size(); i++) {
					GameCard card = deck.getPurchaseableCards()[i];
					cout << i + 1 << ". " << card.getName() << " (Cost: " << card.getCost() << ")" << endl;
				}
				cout << deck.getPurchaseableCards().size() + 1 << ". " << "Get new cards" << " (Cost: " << 2 << ")" << endl;

				cin >> response;
				istringstream iss(response);
				iss >> i;
			} while (i > deck.getPurchaseableCards().size() + 1);

			// If the player chose to get new cards
			if (i == deck.getPurchaseableCards().size() + 1) {
				// Ensure that the player has enough energy for the transaction
				if (energy < 2) {
					cout << "\nYou don't have enough energy for that card" << endl;
				} else {
					energy -= 2;
					for (int i = 0; i < deck.getPurchaseableCards().size(); i++) {
						if (!deck.discardCard(deck.getPurchaseableCards()[0]))
							cout << "Error getting new cards";
						else
							deck.shuffle();
					}
				}
			// Else the player chose to buy a card
			} else {
				// Ensure that the player has enough energy for the transaction
				if (energy >= deck.getPurchaseableCards()[i-1].getCost()) {
					energy -= deck.getPurchaseableCards()[i-1].getCost();
					addOwnedCard(deck.purchaseCard(deck.getPurchaseableCards()[i-1]));
				}
				else
					cout << "\nYou don't have enough energy for that card" << endl;
			}

			cout << "\n" << endl;
			response = buyCardPrompt("Would you like to buy another card ? (Y / N)");

			// Add a new purchaseable card
			deck.shuffle();

		} while (responseToBool(response));
	}
}

// Takes a response Y, y, N, or n and turns it into a bool
bool player::responseToBool(string response) {
	return (response.compare("Y") == 0 || response.compare("y") == 0);
}

// Ask the player if they want to buy a card, and repeat until they answer properly
string inline player::buyCardPrompt(string prompt) {
	string response = "";

	do {
		cout << prompt << endl;;
		cin >> response;
		if (!(response.compare("Y") == 0 || response.compare("y") == 0 || response.compare("N") == 0 || response.compare("n") == 0))
			cout << "Invalid response. Try again.\n" << endl;
	} while (!(response.compare("Y") == 0 || response.compare("y") == 0 || response.compare("N") == 0 || response.compare("n") == 0));
	
	return response;
}

void player::resolveDice(Deck deck)
{
	bool resolving = true;
	const int NUMOFSYMBOLS = 6;
	int* resolveOrder = new int[NUMOFSYMBOLS];
	int* numOfResolves = new int[NUMOFSYMBOLS];
	for (int i = 0; i < NUMOFSYMBOLS; i++)
	{
		numOfResolves[i] = 0;
		resolveOrder[i] = 0;
	}
	int j = 0;
	string ability[NUMOFSYMBOLS] = { "Energy", "Heal", "Attack", "Celebrity", "Destruction", "Ouch" };
	for (int i = 0; i < NUMOFSYMBOLS; i++)
	{
		cout << "Press " << i + 1 << " to resolve " << ability[i] << " dices." << endl;
	}
	while (resolving)
	{
		int num = -1;
		while (num > NUMOFSYMBOLS || num < 0)
		{
			cout << "Which type of dices would you like to resolve?" << endl;
			cin >> num;
			int *end = resolveOrder + NUMOFSYMBOLS;
			// does not allow duplicate values to be placed in the resolveOrder array
			int *result = std::find(resolveOrder, end, num);
			if (result != end) {
				num = -1;
			}
		}
		resolveOrder[j] = num;
		j++;
		int count = 0;
		for (int i = 0; i < playDice.size(); i++)
		{
			
			if (playDice.getDiceContainerTop(i).compare(ability[num - 1]) == 0
				&& playDice.getDiceResolve(i) == true)
			{
				//call a resolve function
				numOfResolves[num - 1]++;
				cout << "Dice number " << i + 1 << " with type " << playDice.getDiceContainerTop(i) << " has been resolved " << endl;
				playDice.setDiceResolve(i,false);
			}
			if (playDice.getDiceResolve(i) == false)
			{
				count++;
			}
				
			if (count == playDice.size())
			{
				resolving = false;
				cout << "All dices have been resolved succesfully" << endl;
			}
		}
		
	}
	for (int i = 0; i < 6; i++)
	{
		if (resolveOrder[i] > 0 && resolveOrder[i] < 7)
		{
			cout << "The resolve number " << resolveOrder[i] << " of the name " << ability[resolveOrder[i] - 1] <<
				" has this number of dices " << numOfResolves[resolveOrder[i] - 1] << endl;
			applyDiceEffect(resolveOrder[i], numOfResolves[resolveOrder[i] - 1], deck);
		}
	}
	cout << "I have reached the end of the file " << endl;
}

void player::applyDiceEffect(int effect, int numberOfResolves, Deck deck)
{
	if (effect == 1 && numberOfResolves > 0)
	{
		addEnergy(numberOfResolves);
		cout << "I added energy and this is how much I added " << this->getEnergy() << endl;
	}
	else if (effect == 2 && numberOfResolves > 0)
	{
		getMonsterCard()->changeHP(numberOfResolves);
		cout << "I added health to monster and this is how much I added " << getMonsterCard()->getHP() << endl;
		//monster underfined thus cannot work
	}
	else if (effect == 3 && numberOfResolves > 0)
	{
		//get the static player vector, iterate through the vector, checking the region
		//if the corresponding region is inside or outside manhattan
		//damage according to the dice effect rule
		for (player otherPlayer : gameStart::playersInGame) {
			//if (player.getRegion().getName() == "Manhattan1" || player.getRegion().getName() == "Manhattan2" || (player.getRegion().getName() == "Manhattan3")) {
			if(otherPlayer.getName().compare(getName()) != 0)
			{
				
				otherPlayer.getMonsterCard()->changeHP(-numberOfResolves);
				cout << otherPlayer.getMonsterCard()->getName() << "'s hp is now " << otherPlayer.getMonsterCard()->getHP() << " damage dealt " << numberOfResolves<< endl;
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
					numOfUnitsInRegion++;
				}

				vector<player> playersInRegion;
				for (player plr : gameStart::playersInGame) {
					// If the player is in the same region, add them to the vector
					if (plr.getRegion().getName().compare(region.getName()) == 0) {
						playersInRegion.push_back(plr);
					}
				}

				// Deal damage to all the players in the region
				for (player plr : playersInRegion) {
					plr.getMonsterCard()->changeHP(numOfUnitsInRegion * -1);
				}
			}
		}
		else if (numberOfResolves > 3)
		{
			// All monsters suffer 1 damage per unit tile in their respective bourough
			// Loop through all regions
			for (Region reg : gameStart::mapRegions) {
				int numOfUnitsInRegion = 0;
				vector<player> playersInRegion;

				// Loop through players
				for (player plr : gameStart::playersInGame) {
					// If the player is in the current region, add them to the vector
					if (plr.getRegion().getName().compare(reg.getName()) == 0) {
						playersInRegion.push_back(plr);
					}
				}

				// Deal damage to all the players in the region
				for (player plr : playersInRegion) {
					plr.getMonsterCard()->changeHP(numOfUnitsInRegion * -1);
				}
			}
			//place status of liberty infront
		}
	}
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

