#include "aggressiveStrat.h"
#include <string>
using namespace std;

aggressiveStrat::aggressiveStrat() : player() {
	playDice = diceRoller::diceRoller();
}
aggressiveStrat::~aggressiveStrat() {

}
aggressiveStrat::aggressiveStrat(string n) : player(n) {
	playDice = diceRoller::diceRoller();
}
void aggressiveStrat::rollDice() {//void diceRoller::botRollDice(array of dice effects you want to not reroll)
	const int size = playDice.size();
	for (int index = 0; index < size; index++) {
		playDice.rollNDice(index); // has no value
		//cout << "Top: " << diceContainer[index]->getDiceTop() << endl;
	}
	
	int numberOfMaxRerolls = 2;
	//first roll
	for (int index = 0; index < playDice.size(); index++) {
		playDice.rollNDice(index); //populate your dice roller
	}
	playDice.displayDiceContainer();
	

	int roll = 0; // bot rolls twice without input

	while (roll < 2)
	{
		cout << "Rerolling..." << endl;
		roll++;
		
		//rerolling desired dices
		for (int i = 0; i < playDice.size(); i++)
		{
			
			if (playDice.getDiceContainerTop(i).compare("Attack") != 0 && playDice.getDiceContainerTop(i).compare("Destruction") != 0) {
				playDice.rollNDice(i);
			}

		}
		playDice.displayDiceContainer();
	}
}

void aggressiveStrat::resolveDice(Deck deck) {
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
	
	while (resolving)
	{
		int diceOptions[] = { 2,4 };//focus on attack and destruction
		int result = 1 + rand() % ((6 + 1) - 1); 
		int num = -1;
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
			cout << "playDice.getDiceContainerTop(i).compare(ability[(int)num - 1]) == 0 " << (playDice.getDiceContainerTop(i).compare(ability[(int)num - 1]) == 0) << endl;
			cout << "playDice.getDiceResolve(i) == tru " << (playDice.getDiceResolve(i) == true) << endl;
			if (playDice.getDiceContainerTop(i).compare(ability[(int)num - 1]) == 0
				&& playDice.getDiceResolve(i) == true)
			{
				//call a resolve function
				numOfResolves[(int)num - 1]++;
				//cout << "Dice number " << i + 1 << " with type " << playDice.getDiceContainerTop(i) << " has been resolved " << endl;
				playDice.setDiceResolve(i, false);
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
				" has been rolled " << numOfResolves[resolveOrder[i] - 1] << " times " << endl;
			applyDiceEffect(resolveOrder[i], numOfResolves[resolveOrder[i] - 1], deck); //replace deck with gameStart::deck
		}
	}
}
void aggressiveStrat::move() {
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

	for (int i = 0; i < regions.size(); i++) {
		for (int j = 0; j < players.size(); j++) {
			if (regions[i] == players[j].getRegion()) {
				regions[i].increasePlayerCount();
			}
		}
	}

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
	gameStart::map.update(regions);
}
void aggressiveStrat::buyCards() {

}