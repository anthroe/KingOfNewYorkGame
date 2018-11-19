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
	// turn = 0;
	bool gameInPlay = true;

	while (gameInPlay)
	{
		vector<player>* players = &gameStart::playersInGame;

		system("CLS");
		std::cout << "It is now turn " << turn << endl;

		notify();

		/*cout << "___PLAYER INFO___" << endl;
		for (player player :  gameStart::playersInGame) {
			cout << player.getName() + ", " + player.getRegion().getName() + ", HP: " << player.getMonsterCard()->getHP() << ", VP: " << player.getMonsterCard()->getVP() << endl;
		}
		cout << "______________________" << endl;*/


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
				// gameStart::playersInGame = (*players);
				continue;
				
			}
			std::cout << (*players)[i].getName() + ": " + (*players)[i].getRegion().getName() << endl;

			
			std::cout << "Rolling dice: " << endl;
			(*players)[i].rollDice();

			notify();

			(*players)[i].resolveDice();

			notify();

			//players[i].resolveDice(gameStart::deck);
			if ((*players)[i].getMonsterCard()->getHP() == 0)
			{
				(*players).erase((*players).begin() + i);
				// gameStart::playersInGame = (*players);

				notify();

				continue;
			}
			else if ((*players)[i].getMonsterCard()->getVP() == 20)
			{
				std::cout << "Player " << (*players)[i].getName() << " has won the game! Round of applause!";
				gameInPlay = false;
				break;
			}

			// (*players) = gameStart::playersInGame;
			//players[i].move_kony();
			(*players)[i].move();
			// (*players) = gameStart::playersInGame;

			// (*players)[i].addEnergy(50);
			// gameStart::playersInGame = (*players);

			notify();

			//players[i].buyCards(gameStart::deck);
			(*players)[i].buyCards();

			notify();

			(*players)[i].getMonsterCard()->changeHP(-12);

			notify();

			turn++;
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
}

void mainLoop::notify() {
	for (GameStatsObserver* gso : observers) {
		gso->update();
	}
}