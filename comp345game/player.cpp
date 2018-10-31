#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#include "player.h"
#include "diceRoller.h"

using namespace std;

int player::playerId = 1;
//create a default player with an empty string as a name and an automatically assigned id
player::player(){
	name = "";
	id = playerId; playerId++;
	playDice = diceRoller::diceRoller();
	
}
//create a player with an a name and an automatically assigned id
player::player(string name){
	this->name = name;
	id = playerId; playerId++;
	
	
}
//create a player with an a name and an automatically assigned id, starting at a specific region
player::player(string name, Region region){
	this->name = name;
	id = playerId; playerId++;
	this->region = region;
	
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
void player::move(Region region) {
	this->region = region;

}

void player::buyCards(Deck deck) {
	// Store the response in a character
	char response;
	// Ask the player if they want to buy a card, and repeat until they answer properly
	do {
		cout << "Would you like to buy a card? (Y/N)" << endl;;
		cin >> response;
		if (response != 'Y' || response != 'y' || response != 'N' || response != 'n')
			cout << "Invalid response. Try again." << endl;
	} while (response != 'Y' || response != 'y' || response != 'N' || response != 'n');

	// If they want to buy a card, show them what they can buy
	if (response == 'Y' || response == 'y') {
		bool cont = false; // continuation condition
		do {
			// Ask which card they want to buy, and repeat until they answer properly
			do {
				cout << "Which card would you like to buy? (Enter the row number)" << endl;
				// Give a list of cards
				for (int i = 0; i < deck.getPurchaseableCards().size(); i++) {
					GameCard card = deck.getPurchaseableCards()[i];
					cout << i + 1 << ". " << card.getName() << " (Cost: " << card.getCost() << ")" << endl;
				}
				cin >> response;
			} while (response > deck.getPurchaseableCards().size());

			// Ensure that they have enough money
			if (energy >= deck.getPurchaseableCards()[response].getCost()) {
				addOwnedCard(deck.purchaseCard(deck.getPurchaseableCards()[response]));
				energy -= deck.getPurchaseableCards()[response].getCost();
			}

			// Ask the player if they want to buy another card, and repeat until they answer properly
			do {
				cout << "Would you like to buy another card? (Y/N)" << endl;;
				cin >> response;
				if (response != 'Y' || response != 'y' || response != 'N' || response != 'n')
					cout << "Invalid response. Try again." << endl;
			} while (response != 'Y' || response != 'y' || response != 'N' || response != 'n');

			// If they want to buy another card set cont to true
			if (response == 'Y' || response == 'y')
				cont = true;

		} while (cont);
	}
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
		if(resolveOrder[i] > 0 && resolveOrder[i] < 7)
		cout << "The resolve number " << resolveOrder[i] << " of the name " << ability[resolveOrder[i] -1] << 
			" has this number of dices " << numOfResolves[resolveOrder[i] - 1] << endl; 
	}
	cout << "I have reached the end of the file " << endl;
}


