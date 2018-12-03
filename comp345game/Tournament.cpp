#include "Tournament.h"
#include "IPlayerType.h"
#include "gameStart.h"
#include <limits>


 
void Tournament::tournamentInitialization() {
	gameStart start;
	map= start.getMap();
	players = start.getPlayers();
	
	cout << "Select the number of games to play (1 to 5): " << endl;
	cin >> gamesToPlay;
	while (!isdigit(gamesToPlay) && (gamesToPlay < 1 || gamesToPlay > 5)) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Invalid number. Try again:" << endl;
		cin >> gamesToPlay;
	}
	
}
void Tournament::startTournament() {
	GameTournament* g;
	int gamesIterator = 0;

	for (int i = 0; i < gamesToPlay; i++) {
		cout << "Playing KONY Game #" << i + 1 << endl;
		cleanUpMap();
		g = new GameTournament(map, players, (i + 1));
		gamesIterator++;
		games.push_back(g);

		g->startGame();
	}

	printReport();
}

void Tournament::printReport() {
	cout << "TOURNAMENT RESULTS:" << endl;
	for (int i = 0; i < gamesToPlay; i++) {
		cout << "Game" + to_string(i + 1) << ": ";
		cout << games[i]->getWinnerName() << endl;
	}
	cout << endl;	
}

void Tournament::cleanUpMap() {
	for (int i = 0; i < players.size(); i++) {
		players[i]->getMonsterCard()->changeVP(-100);
		players[i]->getMonsterCard()->changeHP(10);
		players[i]->setEnergy(0);
	}

	for (int i = 0; i < map.getRegions().size(); i++) {
		map.getRegions()[i].setPlayerCount(0);
	}

	// update global game info
	gameStart::playersInGame = players;
	gameStart::map = map;
	gameStart::mapRegions = map.getRegions();
}
