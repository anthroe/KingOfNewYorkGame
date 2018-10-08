#pragma once
#include <string>
using namespace std;
class dice
{
	public:
		//burrito(string name);
		string diceSymbols[6] = { "Energy", "Heal", "Attack", "Celebrity", "Destruction", "Ouch" };
		void setDiceTop(string top);
		void printTop();
		string getDiceTop();
		void rollDice();
		string getStatus();
		void setStatus(string str);
		dice();
		
	private:
		string topOfDice;
		string status;

};
