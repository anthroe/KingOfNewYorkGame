#include "startup.h"
#include "gameStart.h"
#include "mainLoop.h"
#include <iostream>;
#include <algorithm>;

using namespace std;

mainLoop::mainLoop() {
	
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
			cout << player.getName() + ", " + player.getRegion().getName() + ", HP: " << player.getMonsterCard()->getHP() << ", VP: " << player.getMonsterCard()->getVP() << endl;
		}
		cout << "__________________" << endl;

		//conditions
		if (players.size() <= 1) {
			gameInPlay = false;
		}

		for (int i = 0; i < players.size(); i++) {
			cout << "It is now " << players[i].getName() << "'s turn." << endl;
			if (players[i].getMonsterCard()->getHP() == 0)
			{
				players.erase(players.begin() + i); 
				gameStart::playersInGame = players;
				continue;
				
			}
			cout << players[i].getName() + ": " + players[i].getRegion().getName() << endl;
			
			cout << "Rolling dice: " << endl;
			players[i].rollDice();

			players[i].resolveDice(gameStart::deck);
			gameStart::playersInGame = players;
			if (players[i].getMonsterCard()->getHP() == 0)
			{
				players.erase(players.begin() + i);
				gameStart::playersInGame = players;
				continue;
				
			}
			else if (players[i].getMonsterCard()->getVP() == 20)
			{
				cout << "Player " << players[i].getName() << " has won the game! Round of applause!";
				gameInPlay = false;
				break;
			}

			players[i].move_kony();
			gameStart::playersInGame = players;

			players[i].buyCards(gameStart::deck);
			gameStart::playersInGame = players;

			turn++;
		}
	}
	cout << "Game over" << endl;
}
