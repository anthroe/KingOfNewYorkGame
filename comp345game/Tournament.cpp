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
	while (!isdigit(gamesToPlay) && gamesToPlay < 1 && gamesToPlay > 5) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid number. Try again:" << endl;
		cin >> gamesToPlay;
	}
	
}
void Tournament::startTournament() {
	GameTournament* g;
	int gamesIterator = 0;
	
	for (int i = 0; i < gamesToPlay; i++) {
		cout << "Playing KONY Game #" << i+1 << endl;
		g = new GameTournament(cleanUpMap(map), players, (i + 1));
		gamesIterator++;
		games.push_back(g);
		g->startGame();
	}
	
	printReport();
}

void Tournament::printReport() {
	int gamesIterator = 0;
	cout << "TOURNAMENT RESULTS:" << endl;
	for (int i = 0; i < gamesToPlay; i++) {
		cout << "Game" + to_string(i + 1) << ": ";
		cout << games[gamesIterator]->getWinnerName() << endl;
		gamesIterator++;	
	}
	cout << endl;	
}

Map Tournament::cleanUpMap(Map m) {
	for (int playerIndex = 0; playerIndex < players.size(); playerIndex++) {
		if (players[playerIndex]->getMonsterCard()->getVP() != 0) {
			players[playerIndex]->getMonsterCard()->changeVP(-100);
		}
		if (players[playerIndex]->getMonsterCard()->getHP() != 10) {
			players[playerIndex]->getMonsterCard()->changeHP(+100);
		}
	}

	for (int regionIndex = 0; regionIndex < m.getRegions().size(); regionIndex++) {
		Region currRegion = m.getRegions()[regionIndex];
		currRegion.setPlayerCount(0);
	}
	
	return m;
}
