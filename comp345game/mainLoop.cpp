#include "startup.h"
#include "gameStart.h"
#include "mainLoop.h"
#include <iostream>
#include <algorithm>

using namespace std;

mainLoop::mainLoop() {
	turn = 0;
	GameStatsObserver* statObs = new GameStatsObserver(this);
	observers.push_back(statObs);
	play();
}

void mainLoop::play(){
	bool gameInPlay = true;

	while (gameInPlay)
	{
		vector<player>* players = &gameStart::playersInGame;

		system("CLS");
		std::cout << "It is now turn " << turn << endl;

		notify();

		//conditions
		if ((*players).size() <= 1) {
			std::cout << (*players)[0].getName() + " is the last player remaining." << endl;
			gameInPlay = false;
		}

		for (int i = 0; i < (*players).size(); i++) {
			std::cout << "It is now " << (*players)[i].getName() << "'s turn." << endl;
			if ((*players)[i].getMonsterCard()->getHP() == 0)
			{
				(*players).erase((*players).begin() + i); 
				continue;
				
			}
			std::cout << (*players)[i].getName() + ": " + (*players)[i].getRegion().getName() << endl;
			
			if (gameStart::playersInGame[i].getRegion().getName().compare("Manhattan1") == 0 ||
				gameStart::playersInGame[i].getRegion().getName().compare("Manhattan2") == 0
				) {
				cout << gameStart::playersInGame[i].getName() << " : " << gameStart::playersInGame[i].getMonsterCard()->getName()
					<< " awarded 1 VP point for staying in a Manhattan 1 or 2 region" << endl;
				gameStart::playersInGame[i].getMonsterCard()->changeVP(1);
			}
			else if (gameStart::playersInGame[i].getRegion().getName().compare("Manhattan3") == 0) {
				cout << gameStart::playersInGame[i].getName() << " : " << gameStart::playersInGame[i].getMonsterCard()->getName()
					<< " awarded 2 VP points for staying in Manhattan 3 region" << endl;
				gameStart::playersInGame[i].getMonsterCard()->changeVP(2);
			}
			
			std::cout << "Rolling dice: " << endl;
			(*players)[i].rollDice();

			notify();

			(*players)[i].resolveDice();

			notify();
		
			if ((*players)[i].getMonsterCard()->getHP() == 0)
			{
				(*players).erase((*players).begin() + i);			

				notify();

				continue;
			}
			else if ((*players)[i].getMonsterCard()->getVP() == 20)
			{
				std::cout << "Player " << (*players)[i].getName() << " has won the game! Round of applause!";
				gameInPlay = false;
				break;
			}

			
			(*players)[i].move();
		
			notify();

			(*players)[i].buyCards();

			notify();

			turn++;
			system("pause");
		}
		/*
		1. Roll the Dice (up to 3 times)
		2. Resolve the Dice (mandatory) someone can get 20vp and win
		if(player.monster.vp... = 20 then gameInPlay false and message player won etc
		3. Move (generally optional, but sometimes mandatory)
		4. Buy Cards (optional)
		5. End Your Turn
		*/
	}
	std::cout << "Game over" << endl;
	system("pause");
}

void mainLoop::notify() {
	for (GameStatsObserver* gso : observers) {
		gso->update();
	}
}