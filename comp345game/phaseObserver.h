#pragma once
#include "observer.h"
#include "player.h"

class phaseObserver : public Observer
{
	public:
		void update();
		void update(player* p, string currPhase, string currAct);
		void displayPhase();
	private:
		player* currPlayer;
		string currPhase;
		string currAction;
};
