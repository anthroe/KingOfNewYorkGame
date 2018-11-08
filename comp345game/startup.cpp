#include "startup.h"
#include "gameStart.h"
#include <iostream>;
#include <algorithm>;

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
}

void startup::chooseStartingRegion() {
	float input;
	cout << "Regions: " << endl;
	
	for (int i = 0; i < playerOrder.size(); i++) {

		vector<Region> regions = currMap.getRegions();
		vector<Region> moveableAreas;

		for (Region region : regions) {
			if (!(region.getName() == "Manhattan1" || region.getName() == "Manhattan2" || region.getName() == "Manhattan3")) {
				if (region.getPlayerCount() < 2) {
					moveableAreas.push_back(region);
				}
			}
		}

		cout << "It is " + playerOrder[i].getName() + "'s turn to move. Choose Destination:" << endl;

		for (int i = 0; i < moveableAreas.size(); i++) {
			cout << i << ". " + moveableAreas[i].getName() + "	";
		}

		cin >> input;
		while (cin.fail() || input != (int)input || (input < 0 || input > moveableAreas.size()-1) ) {
			cin.clear();
			cin.ignore(256, '\n');
			cin >> input;
		}

		input = (int)input;

		playerOrder[i].setRegion(moveableAreas[input]);

		cout << playerOrder[i].getName() + " moved to " + playerOrder[i].getRegion().getName() + ". " << endl << endl;

		//update map
		for (int j = 0; j < regions.size(); j++) {
			if (regions[j] == moveableAreas[input]) {
				regions[j].increasePlayerCount();
				playerOrder[i].setRegion(regions[j]);
			}
		}

		gameStart::playersInGame = playerOrder;
		currMap.update(regions);

	}

	gameStart::map = currMap;
	gameStart::playersInGame = playerOrder;
}


