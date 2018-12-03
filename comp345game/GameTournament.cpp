#include "GameTournament.h"
#include "mainLoop.h"
#include "startup.h"
#include "Deck.h"

GameTournament::GameTournament(Map m, vector<player*> p, int n) {
	map = m;
	players = p;
	gameNumber = n;
}
void GameTournament::startGame() {
	int  results = -1;
	startup startup;
	mainLoop Loop;
	results = Loop.play();
	if (results == -1) {
		win = NULL;
	}
	else {
		for (auto player : players) {
			if (player->getId() == results) {
				win = player;
			}
		}
	}
}

string GameTournament::getWinnerName() {
	if (win == NULL)
		return "DRAW";
	else
		return win->getName();
}