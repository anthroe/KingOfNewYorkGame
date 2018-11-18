#pragma once
#ifndef GAMESTATSOBSERVER_H
#define GAMESTATSOBSERVER_H

#include "gameStart.h"
#include "mainLoop.h"
#include "Observer.h"
#include "libraries/TextTable.h"

class GameStatsObserver : public Observer {
public:
	GameStatsObserver() { gameLoop = NULL; };
	GameStatsObserver(mainLoop* loop) : gameLoop(loop) {};
	void update();
	void displayStats(TextTable, TextTable);

private:
	mainLoop* gameLoop;
};

#endif // !GAMESTATSOBSERVER_H
