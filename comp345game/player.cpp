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

	float input;
	int lowManIndex = -1;
	int midManIndex = -1;
	int uppManIndex = -1;

	vector<Region> regions = gameStart::mapRegions;
	vector<player> players = gameStart::playersInGame;
	vector<Region> zones = region.getNeighbours();
	vector<Region> moveableAreas;
	vector<string> neighbourNames;
	Region priorRegion = region;

	/*for (int i = 0; i < regions.size(); i++) {
		for (int j = 0; j < players.size(); j++) {
			if (regions[i] == players[j].getRegion()) {
				regions[i].increasePlayerCount();
			}
		}
	}*/

	for (int i = 0; i < regions.size(); i++) {
		if (regions[i].getName() == "Manhattan1") {
			lowManIndex = i;
		}
		else if (regions[i].getName() == "Manhattan2") {
			midManIndex = i;
		}
		else if (regions[i].getName() == "Manhattan3") {
			uppManIndex = i;
		}
	}

	for (int i = 0; i < zones.size(); i++) {
		if (zones[i].getPlayerCount() < 2) {
			if (zones[i].getName() != "Manhattan1" && zones[i].getName() != "Manhattan2" && zones[i].getName() != "Manhattan3") {
				neighbourNames.push_back(zones[i].getName());
			}
		}
	}

	for (Region region : regions) {
		for (string neighbourName : neighbourNames) {
			if (region.getName() == neighbourName) {
				moveableAreas.push_back(region);
			}
		}
	}

	if (!damaged) {
		cout << "It is " + name + "'s turn to move." << endl;
		cout << "Current location: " + region.getName() << endl;
	}

	if (region.getName() == "Manhattan3" && !damaged) {
		//if the player is in upper manhattan, he cannot move.

		cout << name + " cannot move." << endl << endl;
	}
	else if (region.getName() == "Manhattan1" && !damaged) {
		//if the player is in lower or middle manhattan, he advances to the next zone.
		//this player can only move anywhere other than manhattan if attacked.
		region = regions[midManIndex];

		cout << name + " was moved to middle manhattan." << endl << endl;
	}
	else if (region.getName() == "Manhattan2" && !damaged) {
		//if the player is in middle manhattan, he advances to upper manhattan.
		region = regions[uppManIndex];

		cout << name + " was moved to upper Manhattan." << endl << endl;
	}
	else if (regions[lowManIndex].getPlayerCount() == 0 && regions[midManIndex].getPlayerCount() == 0 && regions[uppManIndex].getPlayerCount() == 0 && !damaged) {
		//if no one is in Manhattan. the player moves to lower Manhattan
		region = regions[lowManIndex];

		cout << "Manhattan is empty. " + name + " was moved to lower manhattan." << endl << endl;
	}
	else {

		if (!damaged) {
			//manhattan is occupied, the player to neighbouring areas.
			cout << "Manhattan is occupied. Choose destination: " << endl;
		}
		else {
			cout << name + " is in Manhattan and has been damaged. Move or remain in place." << endl;
			damaged = false;
		}

		for (int i = 0; i < moveableAreas.size(); i++) {
			cout << i << ". " + moveableAreas[i].getName() + "	";
		}

		cout << moveableAreas.size() << ". Remain in place.";

		cin >> input;

		while (cin.fail() || input != (int)input || (input < 0 || input > moveableAreas.size())) {
			cin.clear();
			cin.ignore(256, '\n');
			cin >> input;
		}

		input = (int)input;

		if (input == moveableAreas.size()) {
			return;
		}

		region = moveableAreas[input];

		cout << name + " moved to " + region.getName() + ". " << endl << endl;
	}

	for (int i = 0; i < regions.size(); i++) {
		if (regions[i] == priorRegion) {
			priorRegion.decreasePlayerCount();
			regions[i] = priorRegion;
		}

		if (regions[i] == region) {
			region.increasePlayerCount();
			regions[i] = region;
		}
	}

	for (int i = 0; i < players.size(); i++) {
		if (name == players[i].getName() && id == players[i].getId()) {
			players[i].region = region;
		}
	}

	gameStart::playersInGame = players;
	gameStart::mapRegions = regions;
	gameStart::map.update(regions);
}

void player::setRegion(Region region) {
	this->region = region;
}

// Takes a response Y, y, N, or n and turns it into a bool
bool player::responseToBool(string response) {
	return (response.compare("Y") == 0 || response.compare("y") == 0);
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
				}
				else {
					energy -= 2;
					for (int i = 0; i < deck.getPurchaseableCards().size(); i++) {
						if (!deck.discardCard(deck.getPurchaseableCards()[0]))
							cout << "Error getting new cards";
						else
							deck.shuffle();
					}
				}
				// Else the player chose to buy a card
			}
			else {
				// Ensure that the player has enough energy for the transaction
				if (energy >= deck.getPurchaseableCards()[i - 1].getCost()) {
					energy -= deck.getPurchaseableCards()[i - 1].getCost();
					addOwnedCard(deck.purchaseCard(deck.getPurchaseableCards()[i - 1]));
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

	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		if (gameStart::playersInGame[i] == (*this)) {
			gameStart::playersInGame[i] = (*this);
		}
	}
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
		float num = -1;
		while (num > NUMOFSYMBOLS || num < 0)
		{
			cout << "Which type of dices would you like to resolve?" << endl;
			cin >> num;

			while (cin.fail() || num != (int)num || (num < 1 || num > 6)) {
				cin.clear();
				cin.ignore(256, '\n');
				cin >> num;
			}

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
			
			if (playDice.getDiceContainerTop(i).compare(ability[(int) num - 1]) == 0
				&& playDice.getDiceResolve(i) == true)
			{
				//call a resolve function
				numOfResolves[(int) num - 1]++;
				//cout << "Dice number " << i + 1 << " with type " << playDice.getDiceContainerTop(i) << " has been resolved " << endl;
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
			cout << "The dice of the type " << ability[resolveOrder[i] - 1] <<
				" has been rolled " << numOfResolves[resolveOrder[i] - 1] <<  " times " <<endl;
			applyDiceEffect(resolveOrder[i], numOfResolves[resolveOrder[i] - 1], deck);
		}
	}
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
							players[i].move_kony();
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