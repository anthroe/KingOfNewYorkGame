#include "gameStart.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "dirent.h"
#include "player.h"
using namespace std;

gameStart::gameStart() {
	//numberOfPlayers = setNumberOfPlayers;
	
	cout << "Select a map from the list of maps:" << endl;
	listMaps();
	string mapName;
	cout << "Enter the map name:" << endl;
	cin >> mapName;
	
	Maploader mapLoaded(mapName);
	cout << "You are now playing on " + mapName.substr(0, mapName.size() - 4)  << endl;
	system("pause");
	
	createPlayers();

}
gameStart::~gameStart() {
	delete map;
}
void gameStart::createPlayers() {
	int inputPlayers;
	cout << endl << "How many players will play? (2 - 6)" << endl;
	cin >> inputPlayers;
	while ((inputPlayers < 2 || inputPlayers > 6)) {
		cout << "Please select a valid amount of players (2 - 6): " << endl;
		cin >> inputPlayers;
	}
	cout << "Creating players..." << endl;

	// Create a new deck and the players
	//currentDeck = new Deck(loadedMap->getMap()->getCountries().size());
	for (int i = 1; i <= inputPlayers; i++) {
		string playerName;
		cout << "Enter player " << (i) << "'s name:" << endl;
		cin >> playerName;
		player* currPlayer = new player(playerName);
		playersInGame.push_back(currPlayer);
	}
}


int gameStart::listMaps() {

	DIR*     dir;
	dirent*  pdir;

	dir = opendir("./maps");     // open map directory

	while (pdir = readdir(dir)) {
		cout << pdir->d_name << endl;
	}
	closedir(dir);
	cout << "\n" << endl;
	return 0;
}

vector<player*> gameStart::getPlayers() {
	return playersInGame;
}