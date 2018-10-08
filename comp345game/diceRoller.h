#include <string>
#include "dice.h"
using namespace std;
class diceRoller
{
public:
	diceRoller();
	void playerRoll();
	void displayDiceContainer();

private:
	dice* diceContainer[6];

};