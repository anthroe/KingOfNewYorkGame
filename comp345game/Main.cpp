//#include "cardtest.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Region.h"
#include "Maploader.h"
#include "cardtest.h"
#include "player.h"
#include "gameStart.h"
#include "startup.h"
#include "mainLoop.h"
#include "phaseObserver.h"
#include "Tournament.h"

using namespace std;

int main() {
	cout << "Welcome To King of New York Virtual Game!" << endl;
	cout << "Select the game mode that you would like to play:" << endl;
	cout << "[0] Regular game \t [1] Tournament \t [2] Quit" << endl << "Choice: ";
	int choice;
	cin >> choice;
	while (!isdigit(choice) && (choice < 0 || choice > 2)) {
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Please enter a valid amount choice." << endl;
		cin >> choice;
	}
	if (choice == 0) {
		cout << "You chose to play a regular game!\n" << endl;
		gameStart();
		startup();
		mainLoop();
	}
	else if (choice == 1){
		cout << "You chose to play a tournament!\n" << endl;
		Tournament t;
		t.tournamentInitialization();
		t.startTournament();
	}
	else if (choice == 2){
		cout << "Exiting...\n" << endl;
		system("pause");
		exit(0);
	}
	system("pause");
	cout << "End of test." << endl;
 	return 0;
}