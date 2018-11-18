#include "startup.h"
#include "gameStart.h"
#include "mainLoop.h"
#include <iostream>
#include <algorithm>

using namespace std;

mainLoop::mainLoop() {
	
	play();
}

void mainLoop::play(){
	turn = 0;
	bool gameInPlay = true;

	while (gameInPlay)
	{
		system("CLS");
		cout << "It is now turn " << turn << endl;
		cout << "___PLAYER INFO___" << endl;
		for (player player :  gameStart::playersInGame) {
			cout << player.getName() + ", " + player.getRegion().getName() + ", HP: " << player.getMonsterCard()->getHP() << ", VP: " << player.getMonsterCard()->getVP() << endl;
		}
		cout << "______________________" << endl;


		//conditions
		if (gameStart::playersInGame.size() <= 1) {
			cout << gameStart::playersInGame[0].getName() + " is the last player remaining." << endl;
			gameInPlay = false;
		}

		for (int i = 0; i < gameStart::playersInGame.size(); i++) {
			cout << "It is now " << gameStart::playersInGame[i].getName() << "'s turn." << endl;
			if (gameStart::playersInGame[i].getMonsterCard()->getHP() == 0)
			{
				gameStart::playersInGame.erase(gameStart::playersInGame.begin() + i);
				continue;
				
			}
			cout << gameStart::playersInGame[i].getName() + ": " + gameStart::playersInGame[i].getRegion().getName() << endl;

			
			cout << "Rolling dice: " << endl;
			gameStart::playersInGame[i].rollDice();
			gameStart::playersInGame[i].resolveDice();
			if (gameStart::playersInGame[i].getMonsterCard()->getHP() == 0 )
			{
				gameStart::playersInGame.erase(gameStart::playersInGame.begin() + i);
				continue;
				
			}
			else if (gameStart::playersInGame[i].getMonsterCard()->getVP() == 20 || turn == 5)
			{
				cout << "Player " << gameStart::playersInGame[i].getName() << " has won the game! Round of applause!";
				gameInPlay = false;
				break;
			}

			gameStart::playersInGame[i].move();
			gameStart::playersInGame[i].buyCards();
			turn++;
			//system("pause");
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
	cout << "Game over" << endl;
	system("pause");
}
