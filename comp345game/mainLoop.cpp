#include "startup.h"
#include "gameStart.h"
#include "mainLoop.h"
#include <iostream>;
#include <algorithm>;

using namespace std;

mainLoop::mainLoop() {
	
	play();
}

void mainLoop::play(){

	turn = 0;
	bool gameInPlay = true;

	while (gameInPlay)
	{
		vector<player> players = gameStart::playersInGame;

		system("CLS");
		cout << "It is now turn " << turn << endl;
		cout << "___PLAYER INFO___" << endl;
		for (player player :  gameStart::playersInGame) {
			gameStart::playersInGame = players;
			cout << player.getName() + ", " + player.getRegion().getName() + ", HP: " << player.getMonsterCard()->getHP() << ", VP: " << player.getMonsterCard()->getVP() << endl;
		}
		cout << "______________________" << endl;


		//conditions
		if (players.size() <= 1) {
			gameInPlay = false;
		}

		players = gameStart::playersInGame;
		for (int i = 0; i < players.size(); i++) {
			players = gameStart::playersInGame;
			player currPlayer = players[i];
			cout << "It is now " << currPlayer.getName() << "'s turn." << endl;
			if (currPlayer.getMonsterCard()->getHP() == 0)
			{
				players.erase(players.begin() + i); 
				gameStart::playersInGame = players;
				continue;
				
			}
			cout << currPlayer.getName() + ": " + currPlayer.getRegion().getName() << endl;

			
			cout << "Rolling dice: " << endl;
			currPlayer.rollDice();

			currPlayer.resolveDice(gameStart::deck);
			gameStart::playersInGame = players;
			if (currPlayer.getMonsterCard()->getHP() == 0)
			{
				players.erase(players.begin() + i);
				continue;
				
			}
			else if (currPlayer.getMonsterCard()->getVP() == 20)
			{
				cout << "Player " << currPlayer.getName() << " has won the game! Round of applause!";
				gameInPlay = false;
				break;
			}

			gameStart::playersInGame = players;
			currPlayer.move_kony();
			gameStart::playersInGame = players;
			currPlayer.buyCards(gameStart::deck);
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
	cout << "Game over" << endl;
}
