#pragma once
#include "observer.h"
#include "player.h"

class phaseObserver : public Observer
{
	private:
		player* currPlayer;
		string currPhase;
		string currAction;

	public:
		//phaseObserver() {};
		//phaseObserver(player* plr) : currPlayer(plr) {};
		void update();
		void update(player* p, string currPhase, string currAct);
		void displayPhase();
};
