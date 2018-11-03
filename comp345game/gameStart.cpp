#include "gameStart.h"
#include <sstream>
#include <iostream>
#include <string>
#include "dirent.h"
#include "player.h"
#include "deck.h"
#include <filesystem>
#include "./libraries/json.hpp"
using json = nlohmann::json;
using namespace std;

gameStart::gameStart() {
	
	selectMap();
	buildMonster();
	createPlayers();
}

void gameStart::selectMap() {
	string mapName;
	cout << "Select a map from the list of maps:" << endl;
	listMaps();

	cout << "Enter the map name:" << endl;
	cin >> mapName;

	while (!fileExists(mapName)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid map name. Try again:" << endl;
		cin >> mapName;
	}
	Maploader mapLoaded(mapName);
	size_t lastindex = mapName.find_last_of("."); //find "." in file name
	string rawname = mapName.substr(0, lastindex); //return just the filename
	cout << "You are now playing on " + rawname << endl;
	cout << "\n" << endl;

	map = mapLoaded.getMap();
}

void gameStart::createPlayers() {
	float inputPlayers;
	cout << endl << "How many players will play? (2 - 6)" << endl;
	cin >> inputPlayers;

	while (cin.fail() || inputPlayers != (int) inputPlayers|| (inputPlayers < 2 || inputPlayers > 6)) {
		cin.clear();
		cin.ignore(6, '\n');
		cout << "Please select a valid amount of players (2 - 6): " << endl;		
		cin >> inputPlayers;
	}

	numberOfPlayers = (int)inputPlayers;

	// Create a new deck and the players
	Deck deck;
	for (int i = 1; i <= inputPlayers; i++) {
		string playerName;
		cout << "Enter player " << (i) << "'s name:" << endl;
		cin >> playerName;
		player currPlayer = player(playerName);
		currPlayer.setMonsterCard(selectMonster());
		playersInGame.push_back(currPlayer);		
	}

	cout << "\nPlayers playing: " << endl;

	for (player player : playersInGame) {
		cout << player.getName() + " playing as: " + player.getMonsterCard().getName() << endl;
	}
}

inline bool gameStart::fileExists(const std::string& name)
{
	ifstream file(name);
	if (!file)            // If the file was not found, then file is 0, i.e. !file=1 or true.
		return false;    // The file was not found.
	else                 // If the file was found, then file is non-0.
		return true;     // The file was found.
}

int gameStart::listMaps() {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("./maps")) != NULL) {
		/* print all the files and directories within directory */

		vector<string> maps;
		int filecount = 0;
		string mapName;

		//count the files in the directory
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_REG) {
				mapName = ent->d_name;
				filecount++;
				maps.push_back(mapName);
			}
		}
		//print the appropriate files
		for (int i = 0; i < maps.size(); i++) {
			if (maps[i].substr(maps[i].find_last_of(".") + 1) == "map") { //only print files that end in .map
				cout << maps[i] << endl;
			}
		}
		cout << "\n" << endl;
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("Could not open directory");
		return EXIT_FAILURE;
	}
	return 0;
}

void gameStart::buildMonster() {
	json monsterCardListJson;
	Deck::getCardList("resources/kony-monster-card-list.json") >> monsterCardListJson;

	// Build a list of MonsterCard objects listing monsters cards
	for (json card : monsterCardListJson) {
		string cname = card["name"];
		ListOfMonsterCards.push_back(cname);
	}
}
MonsterCard gameStart::selectMonster() {
	//print list of available monsters to choose from
	cout << "\nMonsters available: " << endl;
	for (int i = 0; i < ListOfMonsterCards.size(); i++) {
		cout << ListOfMonsterCards[i] << endl;
	}
	string choice = "";
	bool selectValid = false;
	cout << "\nSelect a monster card: " << endl; 
	cin >> choice;
	checkMonsterExists(choice);

	while (!checkMonsterExists(choice)) {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Please select a valid monster: " << endl;
		cin >> choice;
	}

	ListOfMonsterCards.erase(remove(ListOfMonsterCards.begin(), ListOfMonsterCards.end(), choice), ListOfMonsterCards.end());
	return MonsterCard(choice);
}

bool gameStart::checkMonsterExists(string choice) {
	bool selectValid;
	for (int i = 0; i < ListOfMonsterCards.size(); i++) {
		if (choice != ListOfMonsterCards[i]) {
			selectValid = false;
		}
		else {
			selectValid = true; 
	
			break;
		}
	}
	return selectValid;
}