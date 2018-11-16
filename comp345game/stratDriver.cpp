#include "player.h"
#include "aggressiveStrat.h"
#include "moderateStrat.h"
#include "humanStrat.h"
#include "startup.h"
#include "gameStart.h"
#include "stratDriver.h"

player* playerStrategy = NULL;
aggressiveStrat aggressiveBot;
moderateStrat moderateBot;

void setPlayerStrategy(player* strategy) {
	playerStrategy = strategy;
}

stratDriver::stratDriver() {
	Deck deck;
	aggressiveBot.rollDice();
	aggressiveBot.resolveDice(deck);
}
