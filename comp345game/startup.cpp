#include "startup.h"
#include "gameStart.h"
#include "phaseObserver.h"
#include <iostream>
#include <algorithm>

using namespace std;
vector<player> players;


startup::startup() {
	players = gameStart::playersInGame;
	currMap = gameStart::map;
	decidePlayerOrder();
	chooseStartingRegion();
}

void startup::decidePlayerOrder() {
	int max = -1;
	int result = -1;
	int indexOfFirstPlayer = -1;

	cout << "\n Roll the dice to see who goes first\n" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << "\n" << players[i].getName() + " rolled:\n" << endl;
		result = players[i].firstRoll();
		if (result > max) {
			max = result;
			indexOfFirstPlayer = i;
		}
	}

	// put players in clockwise order
	for (int i = 0; i < players.size(); i++) {
		if (i == indexOfFirstPlayer) {
			
			playerOrder.push_back(players[i]); //push first player

			//push players after first
			for (int j = i+1; j < players.size(); j++) {
				playerOrder.push_back(players[j]);
			}
			//push players before first
			for (int k = 0; k < i; k++) {
				playerOrder.push_back(players[k]);
			}
		}
	}

	cout << "Player order is: " << endl;
	for (int i = 0; i < playerOrder.size(); i++) {
		cout << i+1 << ". " << playerOrder[i].getName() << endl;
	}

	gameStart::playersInGame = playerOrder;
}

void startup::chooseStartingRegion() {
	for (int i = 0; i < gameStart::playersInGame.size(); i++) {
		gameStart::playersInGame[i].chooseStartingRegion();
		//gameStart::playersInGame[i].notifyAll("phase", "actions");
	}
}


