#pragma once

#include <iostream>
#include "IPlayerType.h"
#include "player.h"
#include "gameStart.h"
#include "startup.h"
#include "diceRoller.h"
#include "deck.h"

using namespace std;

void IPlayerType::move(player* player) {
	cout << "default move" << endl;
}

void aggressiveBot::move(player* currentBot) {
	currentBot->notifyAll("Move", "");
	if (currentBot->getRegion() == Region()) {
		cout << "Cannot move " + currentBot->getName() + ". This player's region has not been set yet." << endl;
		return;
	}

	// ====================================== Setup Info ==========================================
	int lowManIndex = -1;
	int midManIndex = -1;
	int uppManIndex = -1;
	int input;

	vector<Region> regions = gameStart::mapRegions;
	vector<Region> zones = currentBot->getRegion().getNeighbours();
	vector<Region> moveableAreas;
	vector<string> neighbourNames;
	Region priorRegion = (*currentBot).getRegion();

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
		for (int j = 0; j < regions.size(); j++) {
			if (zones[i] == regions[j] && regions[j].getPlayerCount() < 2) {
				if (zones[i].getName() != "Manhattan1" && zones[i].getName() != "Manhattan2" && zones[i].getName() != "Manhattan3") {
					neighbourNames.push_back(zones[i].getName());
				}
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

	// ==================================== Manhattan Process =====================================
	if (!currentBot->isDamaged()) {
		cout << "It is " + currentBot->getName() + "'s turn to move." << endl;
		cout << "Current location: " + currentBot->getRegion().getName() << endl;
	}

	if (currentBot->getRegion().getName() == "Manhattan3" && !currentBot->isDamaged()) {
		cout << currentBot->getName() + " cannot move." << endl << endl;
		currentBot->notifyAll("Move", "cannot move");
	}
	else if (currentBot->getRegion().getName() == "Manhattan1" && !currentBot->isDamaged()) {
		currentBot->setRegion(regions[midManIndex]);
		cout << currentBot->getName() + " was moved to middle manhattan." << endl << endl;
		currentBot->notifyAll("Move", "player moved to " + currentBot->getRegion().getName());
	}
	else if (currentBot->getRegion().getName() == "Manhattan2" && !currentBot->isDamaged()) {
		currentBot->setRegion(regions[uppManIndex]);
		currentBot->notifyAll("Move", "player moved to " + currentBot->getRegion().getName());
		cout << currentBot->getName() + " was moved to upper Manhattan." << endl << endl;
	}
	else if (regions[lowManIndex].getPlayerCount() == 0 && regions[midManIndex].getPlayerCount() == 0 && regions[uppManIndex].getPlayerCount() == 0 && !currentBot->isDamaged()) {
		currentBot->setRegion(regions[lowManIndex]);
		currentBot->notifyAll("Move", "player moved to " + currentBot->getRegion().getName());
		cout << "Manhattan is empty. " + currentBot->getName() + " was moved to lower manhattan." << endl << endl;
	}
	else {
		// ==================================== Move Process =====================================
		bool isLowHP = false;

		if (currentBot->isDamaged()) {
			cout << currentBot->getName() + " is in Manhattan and has been damaged. Move or remain in place." << endl;
			if (currentBot->getMonsterCard()->getHP() < 5) {
				isLowHP = true;
			}
			currentBot->setDamage(false);
		}
		else {
			//manhattan is occupied, move the player to neighbouring areas.
			cout << "Choose destination: " << endl;
		}

		for (int i = 0; i < moveableAreas.size(); i++) {
			cout << i << ". " + moveableAreas[i].getName() + "	";
		}

		cout << moveableAreas.size() << ". Remain in place." << endl;

		if (isLowHP) {
			input = rand() % (moveableAreas.size());
		}
		else {
			input = rand() % (moveableAreas.size() + 1);
		}

		if (input == moveableAreas.size()) {
			cout << currentBot->getName() + " remains in place." << endl;
			return;
		}
		else {
			currentBot->setRegion(moveableAreas[(int)input]);
			cout << currentBot->getName() + " moved to " + currentBot->getRegion().getName() + ". " << endl << endl;
		}
	}

	// ======================================= Update Map ========================================
	for (int i = 0; i < regions.size(); i++) {
		if (regions[i] == priorRegion) {
			regions[i].decreasePlayerCount();
			priorRegion.decreasePlayerCount();
		}

		if (regions[i] == currentBot->getRegion()) {
			regions[i].increasePlayerCount();
			currentBot->setRegion(regions[i]);
		}
	}

	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		// update current player
		if (gameStart::playersInGame[i] == currentBot) {
			gameStart::playersInGame[i]->setRegion(currentBot->getRegion());
		}

		//update the playerCount of other players' regions
		else if (gameStart::playersInGame[i]->getRegion() == currentBot->getRegion()) {
			gameStart::playersInGame[i]->setRegion(currentBot->getRegion());
		}
		else if (gameStart::playersInGame[i]->getRegion() == priorRegion) {
			gameStart::playersInGame[i]->setRegion(priorRegion);
		}
	}

	gameStart::mapRegions = regions;
	gameStart::map.update(regions);
	currentBot->notifyAll("Move", "location -> " + currentBot->getRegion().getName());
}

void moderateBot::move(player* currentBot) {
	currentBot->notifyAll("Move", "");
	if (currentBot->getRegion() == Region()) {
		cout << "Cannot move " + currentBot->getName() + ". This player's region has not been set yet." << endl;
		return;
	}

	// ====================================== Setup Info ==========================================
	int lowManIndex = -1;
	int midManIndex = -1;
	int uppManIndex = -1;
	int input;

	vector<Region> regions = gameStart::mapRegions;
	vector<Region> zones = currentBot->getRegion().getNeighbours();
	vector<Region> moveableAreas;
	vector<string> neighbourNames;
	Region priorRegion = (*currentBot).getRegion();

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
		for (int j = 0; j < regions.size(); j++) {
			if (zones[i] == regions[j] && regions[j].getPlayerCount() < 2) {
				if (zones[i].getName() != "Manhattan1" && zones[i].getName() != "Manhattan2" && zones[i].getName() != "Manhattan3") {
					neighbourNames.push_back(zones[i].getName());
				}
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

	// ==================================== Manhattan Process =====================================
	if (!currentBot->isDamaged()) {
		cout << "It is " + currentBot->getName() + "'s turn to move." << endl;
		cout << "Current location: " + currentBot->getRegion().getName() << endl;
	}

	if (currentBot->getRegion().getName() == "Manhattan3" && !currentBot->isDamaged()) {
		cout << currentBot->getName() + " cannot move." << endl << endl;
		currentBot->notifyAll("Move", "cannot move");
	}
	else if (currentBot->getRegion().getName() == "Manhattan1" && !currentBot->isDamaged()) {
		currentBot->setRegion(regions[midManIndex]);
		cout << currentBot->getName() + " was moved to middle manhattan." << endl << endl;
		currentBot->notifyAll("Move", "player moved to " + currentBot->getRegion().getName());
	}
	else if (currentBot->getRegion().getName() == "Manhattan2" && !currentBot->isDamaged()) {
		currentBot->setRegion(regions[uppManIndex]);
		cout << currentBot->getName() + " was moved to upper Manhattan." << endl << endl;
		currentBot->notifyAll("Move", "player moved to " + currentBot->getRegion().getName());
	}
	else if (regions[lowManIndex].getPlayerCount() == 0 && regions[midManIndex].getPlayerCount() == 0 && regions[uppManIndex].getPlayerCount() == 0 && !currentBot->isDamaged()) {
		currentBot->setRegion(regions[lowManIndex]);
		cout << "Manhattan is empty. " + currentBot->getName() + " was moved to lower manhattan." << endl << endl;
		currentBot->notifyAll("Move", "player moved to " + currentBot->getRegion().getName());
	}
	else {
		// ==================================== Move Process =====================================
		bool isLowHP = false;

		if (currentBot->isDamaged()) {
			cout << currentBot->getName() + " is in Manhattan and has been damaged. Move or remain in place." << endl;
			isLowHP = true;
			currentBot->setDamage(false);
		}
		else {
			//manhattan is occupied, move the player to neighbouring areas.
			cout << "Choose destination: " << endl;
		}

		for (int i = 0; i < moveableAreas.size(); i++) {
			cout << i << ". " + moveableAreas[i].getName() + "	";
		}

		if (isLowHP) {
			input = rand() % (moveableAreas.size());
		}
		else {
			input = rand() % (moveableAreas.size() + 1);
		}

		if (input == moveableAreas.size()) {
			cout << currentBot->getName() + " remains in place." << endl;
			return;
		}
		else {
			currentBot->setRegion(moveableAreas[(int)input]);
			cout << currentBot->getName() + " moved to " + currentBot->getRegion().getName() + ". " << endl << endl;
		}
	}

	// ======================================= Update Map ========================================
	for (int i = 0; i < regions.size(); i++) {
		if (regions[i] == priorRegion) {
			regions[i].decreasePlayerCount();
			priorRegion.decreasePlayerCount();
		}

		if (regions[i] == currentBot->getRegion()) {
			regions[i].increasePlayerCount();
			currentBot->setRegion(regions[i]);
		}
	}

	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		// update current player
		if (gameStart::playersInGame[i] == currentBot) {
			gameStart::playersInGame[i]->setRegion(currentBot->getRegion());
		}

		//update the playerCount of other players' regions
		else if (gameStart::playersInGame[i]->getRegion() == currentBot->getRegion()) {
			gameStart::playersInGame[i]->setRegion(currentBot->getRegion());
		}
		else if (gameStart::playersInGame[i]->getRegion() == priorRegion) {
			gameStart::playersInGame[i]->setRegion(priorRegion);
		}
	}

	gameStart::mapRegions = regions;
	gameStart::map.update(regions);
	currentBot->notifyAll("Move", "location -> " + currentBot->getRegion().getName());
}

void client::move(player* currentPlayer) {
	currentPlayer->notifyAll("Move", "");
	if (currentPlayer->getRegion() == Region()) {
		cout << "Cannot move " + currentPlayer->getName() + ". This player's region has not been set yet." << endl;
		return;
	}

	// ====================================== Setup Info ==========================================
	float input;
	int lowManIndex = -1;
	int midManIndex = -1;
	int uppManIndex = -1;

	vector<Region> regions = gameStart::mapRegions;
	vector<Region> zones = currentPlayer->getRegion().getNeighbours();
	vector<Region> moveableAreas;
	vector<string> neighbourNames;
	Region priorRegion = (*currentPlayer).getRegion();

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
		for (int j = 0; j < regions.size(); j++) {
			if (zones[i] == regions[j] && regions[j].getPlayerCount() < 2) {
				if (zones[i].getName() != "Manhattan1" && zones[i].getName() != "Manhattan2" && zones[i].getName() != "Manhattan3") {
					neighbourNames.push_back(zones[i].getName());
				}
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

	// ==================================== Manhattan Process =====================================
	if (!currentPlayer->isDamaged()) {
		cout << "It is " + currentPlayer->getName() + "'s turn to move." << endl;
		cout << "Current location: " + currentPlayer->getRegion().getName() << endl;
	}

	if (currentPlayer->getRegion().getName() == "Manhattan3" && !currentPlayer->isDamaged()) {
		//player in upper manhattan cannot move unless damaged.
		cout << currentPlayer->getName() + " cannot move." << endl << endl;
		currentPlayer->notifyAll("Move", "cannot move");
	}
	else if (currentPlayer->getRegion().getName() == "Manhattan1" && !currentPlayer->isDamaged()) {
		//player in lower manhattan advances to middle manhattan.
		currentPlayer->setRegion(regions[midManIndex]);
		cout << currentPlayer->getName() + " was moved to middle manhattan." << endl << endl;
		currentPlayer->notifyAll("Move", "player moved to " + currentPlayer->getRegion().getName());

	}
	else if (currentPlayer->getRegion().getName() == "Manhattan2" && !currentPlayer->isDamaged()) {
		//player in middle manhattan advances to upper manhattan.
		currentPlayer->setRegion(regions[uppManIndex]);
		cout << currentPlayer->getName() + " was moved to upper Manhattan." << endl << endl;
		currentPlayer->notifyAll("Move", "player moved to " + currentPlayer->getRegion().getName());
	}
	else if (regions[lowManIndex].getPlayerCount() == 0 && regions[midManIndex].getPlayerCount() == 0 && regions[uppManIndex].getPlayerCount() == 0 && !currentPlayer->isDamaged()) {
		//if no one is in Manhattan. the player moves to lower Manhattan
		currentPlayer->setRegion(regions[lowManIndex]);
		cout << "Manhattan is empty. " + currentPlayer->getName() + " was moved to lower manhattan." << endl << endl;
		currentPlayer->notifyAll("Move", "player moved to " + currentPlayer->getRegion().getName());
	}
	else {
		if (!currentPlayer->isDamaged()) {
			//manhattan is occupied, move the player to neighbouring areas.
			cout << "Manhattan is occupied. Choose destination: " << endl;
		}
		else {
			//damaged player in manhattan can move elsewhere.
			cout << currentPlayer->getName() + " is in Manhattan and has been damaged. Move or remain in place." << endl;
			currentPlayer->setDamage(false);
		}

		// ==================================== Move Process ========================================
		for (int i = 0; i < moveableAreas.size(); i++) {
			cout << i << ". " + moveableAreas[i].getName() + "	";
		}

		cout << moveableAreas.size() << ". Remain in place." << endl;
		cin >> input;

		while (cin.fail() || input != (int)input || (input < 0 || input > moveableAreas.size())) {
			cin.clear();
			cin.ignore(256, '\n');
			cin >> input;
		}

		if (input == moveableAreas.size()) {
			cout << currentPlayer->getName() + " remains in place." << endl;
		}
		else {
			currentPlayer->setRegion(moveableAreas[(int)input]);
			cout << currentPlayer->getName() + " moved to " + currentPlayer->getRegion().getName() + ". " << endl << endl;
		}
	}

	// ======================================= Update Map ========================================
	for (int i = 0; i < regions.size(); i++) {
		if (regions[i] == priorRegion) {
			regions[i].decreasePlayerCount();
			priorRegion.decreasePlayerCount();
		}

		if (regions[i] == currentPlayer->getRegion()) {
			regions[i].increasePlayerCount();
			currentPlayer->setRegion(regions[i]);
		}
	}

	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		// update current player
		if (gameStart::playersInGame[i] == currentPlayer) {
			gameStart::playersInGame[i]->setRegion(currentPlayer->getRegion());
		}

		//update the playerCount of other players' regions
		else if (gameStart::playersInGame[i]->getRegion() == currentPlayer->getRegion()) {
			gameStart::playersInGame[i]->setRegion(currentPlayer->getRegion());
		}
		else if (gameStart::playersInGame[i]->getRegion() == priorRegion) {
			gameStart::playersInGame[i]->setRegion(priorRegion);
		}
	}

	gameStart::mapRegions = regions;
	gameStart::map.update(regions);
	currentPlayer->notifyAll("Move", "location -> " + currentPlayer->getRegion().getName());
}

void IPlayerType::chooseStartingRegion(player* currentPlayer) {
	currentPlayer->notifyAll("Move", "");
	cout << "Regions: " << endl;
	vector<Region> regions = gameStart::mapRegions;
	vector<Region> moveableAreas;

	for (int i = 0; i < regions.size(); i++) {
		if (!(regions[i].getName() == "Manhattan1" || regions[i].getName() == "Manhattan2" || regions[i].getName() == "Manhattan3")) {
			if (regions[i].getPlayerCount() < 2) {
				moveableAreas.push_back(regions[i]);
			}
		}
	}

	cout << "It is " + currentPlayer->getName() + "'s turn to move. Choose Destination:" << endl;

	for (int i = 0; i < moveableAreas.size(); i++) {
		cout << i << ". " + moveableAreas[i].getName() + "	" << endl;
	}

	int input = rand() % (moveableAreas.size());
	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		if (gameStart::playersInGame[i] == currentPlayer) {
			moveableAreas[input].increasePlayerCount();
			gameStart::playersInGame[i]->setRegion(moveableAreas[input]);
			break;
		}
	}

	cout << currentPlayer->getName() + " moved to " + currentPlayer->getRegion().getName() + ". " << endl << endl;
	currentPlayer->notifyAll("Move", "player moved to " + currentPlayer->getRegion().getName());
	//update map
	for (int j = 0; j < regions.size(); j++) {
		if (regions[j] == moveableAreas[input]) {
			gameStart::mapRegions[j].increasePlayerCount();
		}
	}

	gameStart::map.update(gameStart::mapRegions);
}

void client::chooseStartingRegion(player* currentPlayer) {
	currentPlayer->notifyAll("Move", "");
	float input;
	cout << "Regions: " << endl;
	vector<Region> regions = gameStart::mapRegions;
	vector<Region> moveableAreas;

	for (int i = 0; i < regions.size(); i++) {
		if (!(regions[i].getName() == "Manhattan1" || regions[i].getName() == "Manhattan2" || regions[i].getName() == "Manhattan3")) {
			if (regions[i].getPlayerCount() < 2) {
				moveableAreas.push_back(regions[i]);
			}
		}
	}

	cout << "It is " + currentPlayer->getName() + "'s turn to move. Choose Destination:" << endl;

	for (int i = 0; i < moveableAreas.size(); i++) {
		cout << i << ". " + moveableAreas[i].getName() + "	" << endl;;
	}

	cin >> input;
	while (cin.fail() || input != (int)input || (input < 0 || input > moveableAreas.size() - 1)) {
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input;
	}

	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		if (gameStart::playersInGame[i] == currentPlayer) {
			moveableAreas[(int)input].increasePlayerCount();
			gameStart::playersInGame[i]->setRegion(moveableAreas[(int)input]);
			break;
		}
	}

	cout << currentPlayer->getName() + " moved to " + currentPlayer->getRegion().getName() + ". " << endl << endl;
	currentPlayer->notifyAll("Move", "player moved to " + currentPlayer->getRegion().getName());

	//update map
	for (int j = 0; j < regions.size(); j++) {
		if (regions[j] == moveableAreas[input]) {
			gameStart::mapRegions[j].increasePlayerCount();
		}
	}

	gameStart::map.update(gameStart::mapRegions);
}

// ============================ Roll Dice =================================
void IPlayerType::rollDice(player* player) {
	cout << "default roll dice" << endl;
}

void client::rollDice(player* currentPlayer) {
	currentPlayer->notifyAll("Roll Dice", "");
	cout << currentPlayer->getName() + ": roll your die." << endl;
	currentPlayer->getDice().playerRoll(currentPlayer);
	currentPlayer->notifyAll("Roll Dice", "dice rolled");
}

void aggressiveBot::rollDice(player* currentPlayer) {
	cout << currentPlayer->getName() + ": roll your die." << endl;
	currentPlayer->notifyAll("Roll Dice", "");
	currentPlayer->getDice().botRoll("agressive", currentPlayer);
	currentPlayer->notifyAll("Roll Dice", "dice rolled");
}

void moderateBot::rollDice(player* currentPlayer) {
	cout << currentPlayer->getName() + ": roll your die." << endl;
	currentPlayer->notifyAll("Roll Dice", "");
	currentPlayer->getDice().botRoll("moderate", currentPlayer);
	currentPlayer->notifyAll("Roll Dice", "dice rolled");
}

// =========================== Resolve Dice ===============================
void IPlayerType::resolveDice(player* currentPlayer) {
	Deck* deck = &gameStart::deck;
	bool resolving = true;
	int numOfResolves[6] = { 0, 0, 0, 0, 0, 0 };
	string ability[6] = { "Energy", "Heal", "Attack", "Celebrity", "Destruction", "Ouch" };
	currentPlayer->notifyAll("roll Dice", "resolve dice");

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < currentPlayer->getDice().size();  j++) {
			if (currentPlayer->getDice().getDiceContainerTop(j).compare(ability[i]) == 0)
				numOfResolves[i]++;
		}
	}
	currentPlayer->notifyAll("roll Dice", "dices have been resolved");
	for (int i = 0; i < 6; i++) {
		if (numOfResolves[i] > 0) {
			cout << "The dice of the type " << ability[i] << " has been rolled " << numOfResolves[i] << " times " << endl;
			currentPlayer->applyDiceEffect(i + 1, numOfResolves[i], deck);
		}
	}
	currentPlayer->notifyAll("roll Dice", "dice effects have been applied");
}

void client::resolveDice(player* currentPlayer) {
	Deck* deck = &gameStart::deck;
	bool resolving = true;
	const int NUMOFSYMBOLS = 6;
	int* resolveOrder = new int[NUMOFSYMBOLS];
	int* numOfResolves = new int[NUMOFSYMBOLS];
	currentPlayer->notifyAll("roll Dice", "resolve dice");
	for (int i = 0; i < NUMOFSYMBOLS; i++)
	{
		numOfResolves[i] = 0;
		resolveOrder[i] = 0;
	}
	int j = 0;
	string ability[NUMOFSYMBOLS] = { "Energy", "Heal", "Attack", "Celebrity", "Destruction", "Ouch" };
	for (int i = 0; i < NUMOFSYMBOLS; i++)
	{
		cout << "Press " << i + 1 << " to resolve " << ability[i] << " dice." << endl;
	}
	while (resolving)
	{
		float num = -1;
		while (num > NUMOFSYMBOLS || num < 0)
		{
			cout << "Which type of dice would you like to resolve?" << endl;
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
		resolveOrder[j] = static_cast<int>(num);
		j++;
		int count = 0;
		for (int i = 0; i < currentPlayer->getDice().size(); i++)
		{
			if (currentPlayer->getDice().getDiceContainerTop(i).compare(ability[(int)num - 1]) == 0 && currentPlayer->getDice().getDiceResolve(i) == true)
			{
				//call a resolve function
				numOfResolves[(int)num - 1]++;
				//cout << "Dice number " << i + 1 << " with type " << playDice.getDiceContainerTop(i) << " has been resolved " << endl;
				currentPlayer->getDice().setDiceResolve(i, false);
			}
			if (currentPlayer->getDice().getDiceResolve(i) == false)
			{
				count++;
			}

			if (count == currentPlayer->getDice().size())
			{
				resolving = false;
				cout << "All dices have been resolved succesfully" << endl;
				currentPlayer->notifyAll("roll Dice", "dices have been resolved");
			}
		}

	}
	for (int i = 0; i < 6; i++)
	{
		if (resolveOrder[i] > 0 && resolveOrder[i] < 6)
		{
			cout << "The dice of the type " << ability[resolveOrder[i] - 1] <<
				" has been rolled " << numOfResolves[resolveOrder[i] - 1] << " times " << endl;
			currentPlayer->applyDiceEffect(resolveOrder[i], numOfResolves[resolveOrder[i] - 1], deck);
		}
	}

	currentPlayer->notifyAll("roll Dice", "dice effects have been applied");
}

//	=========================== Buy Cards =================================
void IPlayerType::buyCards(player* currentPlayer) {
	Deck* deck = &gameStart::deck;
<<<<<<< HEAD
=======
	int input;
>>>>>>> origin/CardOberser
	currentPlayer->notifyAll("buyCards", "");
	cout << "\nIt is " + currentPlayer->getName() + "'s turn to buy a card. " << endl;

	// The bot has more than 2 energy, he can buy something. 
	if (currentPlayer->getEnergy() > 2) {
		// Card to purchase is randomly selected
<<<<<<< HEAD
		int input = rand() % (deck->getPurchaseableCards().size()) + 1;
=======
		input = rand() % (deck->getPurchaseableCards().size()) + 1;
>>>>>>> origin/CardOberser

		// Ask which card they want to buy, and repeat until they answer properly
		cout << "\nYou have " << currentPlayer->getEnergy() << " energy." << endl;
		cout << "Which card would you like to buy? (Enter the row number)" << endl;

		// Give a list of cards
		for (int i = 0; i < deck->getPurchaseableCards().size(); i++) {
			GameCard card = deck->getPurchaseableCards()[i];
			cout << i + 1 << ". " << card.getName() << " (Cost: " << card.getCost() << ")" << endl;
		}
		cout << deck->getPurchaseableCards().size() + 1 << ". " << "Get new cards" << " (Cost: " << 2 << ")" << endl;

		// If the player chose to get new cards
		if (input == deck->getPurchaseableCards().size() + 1) {
			// Ensure that the player has enough energy for the transaction
			if (currentPlayer->getEnergy() < 2) {
				cout << "\nYou don't have enough energy for that card" << endl;
			}
			else {
				currentPlayer->setEnergy(currentPlayer->getEnergy() - 2);
				for (int i = 0; i < deck->getPurchaseableCards().size(); i++) {
					if (!deck->discardCard(deck->getPurchaseableCards()[0]))
						cout << "Error getting new cards";
					else
						deck->shuffle();
				}
			}
		}
		//player chose to buy a card.
		else {
			// Ensure that the player has enough energy for the transaction
			if (currentPlayer->getEnergy() >= deck->getPurchaseableCards()[input - 1].getCost()) {
<<<<<<< HEAD
				string cardName = deck->getPurchaseableCards()[input - 1].getName();
				currentPlayer->setEnergy(currentPlayer->getEnergy() - deck->getPurchaseableCards()[input - 1].getCost());
				currentPlayer->addOwnedCard(deck->purchaseCard(deck->getPurchaseableCards()[input - 1]));
				currentPlayer->notifyAll("buyCards", "card purchased");
				cout << currentPlayer->getName() + " has purchased " + cardName << endl;
				deck->shuffle();
=======
				currentPlayer->setEnergy(currentPlayer->getEnergy() - deck->getPurchaseableCards()[input - 1].getCost());
				currentPlayer->addOwnedCard(deck->purchaseCard(deck->getPurchaseableCards()[input - 1]));

				currentPlayer->notifyAll("buyCards", "card purchased");
				cout << currentPlayer->getName() + " has purchased " + deck->getPurchaseableCards()[input - 1].getName() << endl;
>>>>>>> origin/CardOberser
			}
			else
				cout << "\nYou don't have enough energy for that card" << endl;
		}



		//update player info
		for (int i = 0; i < gameStart::playersInGame.size(); i++) {
			if (gameStart::playersInGame[i]->getName() == currentPlayer->getName() && gameStart::playersInGame[i]->getId() == currentPlayer->getId()) {
				gameStart::playersInGame[i]->setEnergy(currentPlayer->getEnergy());
				gameStart::playersInGame[i]->setOwnedCards(currentPlayer->getOwnedCards());
			}
		}
	}
	else {
		cout << currentPlayer->getName() + " doesn't have enough energy to buy cards. " << endl;
	}
}

void client::buyCards(player* currentPlayer) {
	// Store the response in a character
	string response;
	Deck* deck = &gameStart::deck;
	currentPlayer->notifyAll("buyCards", "");
	cout << currentPlayer->getName() + ", would you like to buy a card ? (Y / N)" << endl;
	cin >> response;

	while (response.compare("Y") != 0 && response.compare("y") != 0 && response.compare("N") != 0 && response.compare("n") != 0) {
		cout << "Invalid response. Try again.\n" << endl;
		cin >> response;
	}

	// If they want to buy a card, show them what they can buy
	if (response.compare("Y") == 0 || response.compare("y") == 0) {
		float input;
		do {
			// Ask which card they want to buy, and repeat until they answer properly
			cout << "\nYou have " << currentPlayer->getEnergy() << " energy." << endl;
			cout << "Which card would you like to buy? (Enter the row number)" << endl;

			// Give a list of cards
			for (int i = 0; i < deck->getPurchaseableCards().size(); i++) {
				GameCard card = deck->getPurchaseableCards()[i];
				cout << i + 1 << ". " << card.getName() << " (Cost: " << card.getCost() << ")" << endl;
			}
			cout << deck->getPurchaseableCards().size() + 1 << ". " << "Get new cards" << " (Cost: " << 2 << ")" << endl;
			cin >> input;

<<<<<<< HEAD
			while (cin.fail() || input != (int)input || (input < 1 || input >(deck->getPurchaseableCards().size() + 1))) {
=======
			while (cin.fail() || input != (int)input || (input < 1 || input > (deck->getPurchaseableCards().size() + 1))) {
>>>>>>> origin/CardOberser
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Please enter the correct row number." << endl;
				cin >> input;
			}

			// If the player chose to get new cards
			if (input == deck->getPurchaseableCards().size() + 1) {
				// Ensure that the player has enough energy for the transaction
				if (currentPlayer->getEnergy() < 2) {
					cout << "\nYou don't have enough energy for that card" << endl;
				}
				else {
					currentPlayer->setEnergy(currentPlayer->getEnergy() - 2);
					for (int i = 0; i < deck->getPurchaseableCards().size(); i++) {
						if (!deck->discardCard(deck->getPurchaseableCards()[0]))
							cout << "Error getting new cards";
						else
							deck->shuffle();
					}
				}
			}
			//player chose to buy a card.
			else {
				// Ensure that the player has enough energy for the transaction
				if (currentPlayer->getEnergy() >= deck->getPurchaseableCards()[input - 1].getCost()) {
<<<<<<< HEAD
					string cardName = deck->getPurchaseableCards()[input - 1].getName();
					currentPlayer->setEnergy(currentPlayer->getEnergy() - deck->getPurchaseableCards()[input - 1].getCost());
					currentPlayer->addOwnedCard(deck->purchaseCard(deck->getPurchaseableCards()[input - 1]));
					cout << currentPlayer->getName() + " has purchased " + cardName << endl;
=======
					currentPlayer->setEnergy(currentPlayer->getEnergy() - deck->getPurchaseableCards()[input - 1].getCost());
					currentPlayer->addOwnedCard(deck->purchaseCard(deck->getPurchaseableCards()[input - 1]));

					cout << currentPlayer->getName() + " has purchased " + deck->getPurchaseableCards()[input - 1].getName() << endl;
>>>>>>> origin/CardOberser
					currentPlayer->notifyAll("buyCards", "card purchased");
					deck->shuffle();
				}
				else
					cout << "\nYou don't have enough energy for that card" << endl;
			}
			cout << "\nWould you like to buy another card ? (Y / N)" << endl;
			cin >> response;
			while (response.compare("Y") != 0 && response.compare("y") != 0 && response.compare("N") != 0 && response.compare("n") != 0) {
				cout << "Invalid response. Try again.\n" << endl;
				cin >> response;
			}
			// Add a new purchaseable card
			deck->shuffle();

		} while (response.compare("Y") == 0 || response.compare("y") == 0);
	}

	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		if (gameStart::playersInGame[i] == currentPlayer) {
			gameStart::playersInGame[i]->setEnergy(currentPlayer->getEnergy());
			gameStart::playersInGame[i]->setOwnedCards(currentPlayer->getOwnedCards());
		}
	}
}