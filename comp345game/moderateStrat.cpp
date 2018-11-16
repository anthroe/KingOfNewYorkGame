#include "moderateStrat.h"
#include <string>
using namespace std;

moderateStrat::moderateStrat() : player() {
	playDice = diceRoller::diceRoller();
}
moderateStrat::~moderateStrat() {

}
moderateStrat::moderateStrat(string n) : player(n) {
	playDice = diceRoller::diceRoller();
}

void moderateStrat::rollDice() {
		const int size = playDice.size();
		for (int index = 0; index < size; index++) {
			playDice.rollNDice(index); 
			
		}

		int numberOfMaxRerolls = 2;
		//first roll
		for (int index = 0; index < playDice.size(); index++) {
			playDice.rollNDice(index); //populate your dice roller
		}
		playDice.displayDiceContainer();


		int roll = 0; // bot rolls twice without input

		while (roll < 2)
		{
			cout << "Rerolling..." << endl;
			roll++;

			//rerolling desired dices
			for (int i = 0; i < playDice.size(); i++)
			{
				//focuses on heal, energy and celebrity moves
				if (playDice.getDiceContainerTop(i).compare("Heal") != 0 && 
					playDice.getDiceContainerTop(i).compare("Energy") != 0 && 
					playDice.getDiceContainerTop(i).compare("Celebrity") != 0) {

					playDice.rollNDice(i);
				}

			}
			playDice.displayDiceContainer();

		}
	
}
void moderateStrat::resolveDice() {

}
void moderateStrat::move() {

}
void moderateStrat::buyCards() {

}