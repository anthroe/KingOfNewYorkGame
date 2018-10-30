#include <string>
#include "dice.h"
using namespace std;
class diceRoller
{
public:
	diceRoller();
	void playerRoll();
	void resolveDice();
	void displayDiceContainer();
	const int size();

private:
	dice* diceContainer[6];

};