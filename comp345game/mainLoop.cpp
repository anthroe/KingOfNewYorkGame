#include "startup.h"
#include "gameStart.h"
#include "mainLoop.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

mainLoop::mainLoop() {
	turn = 0;
	GameStatsObserver* statObs = new GameStatsObserver(this);
	observers.push_back(statObs);
	play();
}

/*
	1. Roll the Dice (up to 3 times)
	2. Resolve the Dice (mandatory) someone can get 20vp and win
	if(player.monster.vp... = 20 then gameInPlay false and message player won etc
	3. Move (generally optional, but sometimes mandatory)
	4. Buy Cards (optional)
	5. End Your Turn
*/
int mainLoop::play(){
	bool gameInPlay = true;
	int playerWinnerId = -1;
	while (gameInPlay)
	{
		system("CLS");
		std::cout << "It is now turn " << turn << endl;
		notify();

		//conditions
		if (gameStart::playersInGame.size() == 1) {
			std::cout << gameStart::playersInGame[0]->getName() + " is the last player remaining." << endl;
			gameInPlay = false;
		}
		else if (gameStart::playersInGame.size() == 0){
			cout << "no players left" << endl;
		}

		for (int i = 0; i < gameStart::playersInGame.size(); i++) {
			std::cout << "It is now " << gameStart::playersInGame[i]->getName() << "'s turn." << endl;
			if (gameStart::playersInGame[i]->getMonsterCard()->getHP() == 0 )
			{
				cout << gameStart::playersInGame[i]->getName() + " lost." << endl;
				delete gameStart::playersInGame[i];
				gameStart::playersInGame[i] = NULL;
				gameStart::playersInGame.erase(gameStart::playersInGame.begin() + i);

				continue;
				
			}
			std::cout << gameStart::playersInGame[i]->getName() + ": " + gameStart::playersInGame[i]->getRegion().getName() << endl;
			
			if (gameStart::playersInGame[i]->getRegion().getName().compare("Manhattan1") == 0 ||
				gameStart::playersInGame[i]->getRegion().getName().compare("Manhattan2") == 0
				) {
				cout << gameStart::playersInGame[i]->getName() << " : " << gameStart::playersInGame[i]->getMonsterCard()->getName()
					<< " awarded 1 VP point for staying in a Manhattan 1 or 2 region" << endl;
				gameStart::playersInGame[i]->getMonsterCard()->changeVP(1);
			}
			else if (gameStart::playersInGame[i]->getRegion().getName().compare("Manhattan3") == 0) {
				cout << gameStart::playersInGame[i]->getName() << " : " << gameStart::playersInGame[i]->getMonsterCard()->getName()
					<< " awarded 2 VP points for staying in Manhattan 3 region" << endl;
				gameStart::playersInGame[i]->getMonsterCard()->changeVP(2);
			}
			
			std::cout << "Rolling dice: " << endl;
			gameStart::playersInGame[i]->rollDice();
			notify();
			gameStart::playersInGame[i]->resolveDice();
			notify();
		
			if (gameStart::playersInGame[i]->getMonsterCard()->getHP() == 0)
			{
				cout << gameStart::playersInGame[i]->getName() + " lost." << endl;
				delete gameStart::playersInGame[i];
				gameStart::playersInGame[i] = NULL;
				gameStart::playersInGame.erase(gameStart::playersInGame.begin() + i);
				notify();
				continue;
			}
			else if (gameStart::playersInGame[i]->getMonsterCard()->getVP() == 20 || turn == 3)
			{
				std::cout << "Player " << gameStart::playersInGame[i]->getName() << " has won the game! Round of applause!";
				playerWinnerId = gameStart::playersInGame[i]->getId();
				gameInPlay = false;
				break;
			}

			gameStart::playersInGame[i]->move();
			notify();
			gameStart::playersInGame[i]->buyCards();
			notify();
			turn++;
			system("pause");
		}
	}
	std::cout << "\nGame over\n" << endl;
	return playerWinnerId;
}

void mainLoop::notify() {
	for (GameStatsObserver* gso : observers) {
		gso->update();
	}
}
