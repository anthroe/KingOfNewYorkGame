#include <sstream>
#include <iostream>
#include <string>
#include <filesystem>
#include "gameStart.h"
#include "dirent.h"
#include "player.h"
#include "deck.h"
#include "phaseObserver.h"
#include "./libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

Map gameStart::map;
vector<Region> gameStart::mapRegions;
vector<player> gameStart::playersInGame;
Deck gameStart::deck;

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
	mapRegions = map.getRegions();
}
void gameStart::createPlayers() {
	phaseObserver* obs = new phaseObserver();
	Deck deck;
	float inputPlayers;
	cout << endl << "How many players will play? (0 - 6)" << endl;
	cin >> inputPlayers;

	while (cin.fail() || inputPlayers != (int) inputPlayers|| (inputPlayers < 0 || inputPlayers > 6)) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please select a valid amount of players (0 - 6): " << endl;		
		cin >> inputPlayers;
	}

	numberOfPlayers = (int)inputPlayers;

	// Create a new deck and the players
	for (int i = 1; i <= inputPlayers; i++) {
		string playerName;
		cout << "Enter player " << (i) << "'s name:" << endl;
		cin >> playerName;
		player currPlayer = player(playerName);
		currPlayer.setPlayerType(new client());
		selectMonster(&currPlayer);
		currPlayer.attach(obs);
		currPlayer.notifyAll("phase", "action");
		playersInGame.push_back(currPlayer);

	}
	// ============================ Strategy Pattern	Adding Bots		=====================================
	// Choose to add bots if there's room for more players.
	if ((int) inputPlayers < 6) {
		float inputBots;
		cout << "How many bots would you like to add? (0 - " << 6 - (int) inputPlayers << ")" << endl;
		cin >> inputBots;

		while (cin.fail() || inputBots != (int)inputBots || (inputBots < 0 || inputBots >(6 - (int)inputPlayers))) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Please enter a valid amount of bots." << endl;
			cin >> inputBots;
		}

		for (int i = 1; i <= inputBots; i++) {
			string botName;
			float inputBotType;

			cout << "Enter bot " << i << "'s name" << endl;
			cin >> botName;
			player currBot = player(botName);

			//Select bot type (aggressive or moderate)
			cout << "What type of bot will this be?" << endl;
			cout << "[0]. Aggressive \t [1]. Moderate" << endl;
			cin >> inputBotType;

			while (cin.fail() || inputBotType != (int) inputBotType || ((int) inputBotType < 0 || (int) inputBotType > 1)) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Please enter 0 or 1 to select a type." << endl;
				cin >> inputBotType;
			}

			if ((int) inputBotType == 0) {
				currBot.setPlayerType(new aggressiveBot());
			}
			else {
				currBot.setPlayerType(new moderateBot());
			}

			selectMonster(&currBot); //remove from list
			currBot.attach(obs);
			currBot.notifyAll("phase", "action");
			playersInGame.push_back(currBot);
		}
	}
	//=======================================================================================================

	//Display players
	cout << "\nPlayers playing: " << endl;

	for (player player : playersInGame) {
		cout << player.getName() + " playing as: " + player.getMonsterCard()->getName() << endl;
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
void gameStart::selectMonster(player *currPlayer) {
	//print list of available monsters to choose from
	cout << "\nMonsters available: " << endl;

	cout << ListOfMonsterCards.size() << endl;

	for (int i = 0; i < ListOfMonsterCards.size(); i++) {
		cout << "[" << i <<"] " + ListOfMonsterCards[i] << endl;
	}
	float choice;
	cout << "\nSelect a monster card: " << endl; 
	cin >> choice;

	while (cin.fail() || choice != (int) choice || (choice < 0 || choice >= ListOfMonsterCards.size())) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please select a valid monster: " << endl;
		cin >> choice;
	}
	
	MonsterCard *monst = new MonsterCard(ListOfMonsterCards[choice]);
	currPlayer->setMonsterCard(monst);
	ListOfMonsterCards.erase(remove(ListOfMonsterCards.begin(), ListOfMonsterCards.end(), ListOfMonsterCards[choice]), ListOfMonsterCards.end());
}

bool gameStart::checkMonsterExists(string choice) {
	bool selectValid;
	for (int i = 0; i < ListOfMonsterCards.size(); i++) {
	
		if (choice.compare(ListOfMonsterCards[i]) == 0) {
			selectValid = true;
			
			break;
		}
		else {
			selectValid = false;
		}
	}
	return selectValid;
}