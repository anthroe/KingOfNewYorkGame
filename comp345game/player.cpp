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
	region = NULL;
	
}
//create a player with an a name and an automatically assigned id
player::player(string name){
	this->name = name;
	id = playerId; playerId++;
	region = NULL;
	
}

//giving a monsterCard to a player
void player::setMonsterCard(MonsterCard monst) {
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
	if (region == NULL) {
		cout << "Cannot move " + name + ". This player's region has not been set yet." << endl;
		return;
	}

	vector<Region*> zones = region->getNeighbours();
	float input;

	cout << "It is " + name + "'s turn to move." << endl;
	cout << "Current location: " + region->getName() << endl;
	cout << "Choose destination: " << endl;

	for (int i = 0; i < zones.size(); i++) {
		cout << i << ". " + zones[i]->getName() + "	";
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

void player::setRegion(Region* region) {
	if (this->region != NULL) {
		this->region->reducePlayerCount();
	}

	(*region).increasePlayerCount();
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

void player::resolveDice()
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
				cout << "All dices have been resolved succesfully, you may begone thot" << endl;
			}
		}
		
	}
	for (int i = 0; i < 6; i++)
	{
		if (resolveOrder[i] > 0 && resolveOrder[i] < 7)
		{
			cout << "The resolve number " << resolveOrder[i] << " of the name " << ability[resolveOrder[i] - 1] <<
				" has this number of dices " << numOfResolves[resolveOrder[i] - 1] << endl;
			applyDiceEffect(resolveOrder[i], numOfResolves[resolveOrder[i] - 1]);
		}
	}
	cout << "I have reached the end of the file " << endl;
}
void player::applyDiceEffect(int effect, int numberOfResolves)
{
	if (effect == 1 && numberOfResolves > 0)
	{
		addEnergy(numberOfResolves);
		cout << "I added energy and this is how much I added " << this->getEnergy() << endl;
	}
	else if (effect == 2 && numberOfResolves > 0)
	{
		getMonsterCard().changeHP(numberOfResolves);
		cout << "I added health to monster and this is how much I added " << this->getMonsterCard().getHP() << endl;
		//monster underfined thus cannot work
	}
	else if (effect == 3 && numberOfResolves > 0)
	{
		//get the static player vector, iterate through the vector, checking the region
		//if the corresponding region is inside or outside manhattan
		//damage according to the dice effect rule
	}
	else if (effect == 4 && numberOfResolves > 0) //we need to keep track of superstar card
	{
		//if superstar card is infront of you +1 vp for every numberOfResolves
		if (numberOfResolves > 2)
		{
			//remove superstar card from infront of the previous holder
			//set superstar card infront of you
			getMonsterCard().changeVP(1);
			if (numberOfResolves > 3)
			{
				getMonsterCard().changeVP(numberOfResolves - 3);
			}
		}
	}
	else if (effect == 5 && numberOfResolves > 0)
	{
		//wait till military buildings and units to be implemented
	}
	else if (effect == 6 && numberOfResolves > 0)
	{
		if (numberOfResolves == 1)
		{
			//self damage 1 * unit tiles in borough
		}	
		else if (numberOfResolves == 2)
		{
			//all monsters in your borough suffer 1 damage per unit tile of bourough
		}
		else if (numberOfResolves > 3)
		{
			//all monsters in the borough suffer 1 damage per unit tile of the entire city 
			//place status of liberty infront
		}
		//has to do with unit tiles
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
	return count;
}

