#pragma once
#include "phaseObserver.h"
#include "player.h"

class phase
{
private:
	static phaseObserver observer;
public:
	static void notify(player* p, string currPhase, string currAct);

};