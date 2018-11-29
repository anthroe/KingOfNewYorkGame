#pragma once
#include "turnObserver.h"
#include "player.h"

class turn
{
private:
	static turnObserver observer;
public:
	static void notify(player* p);

};