#pragma once
#ifndef MONSTERCARD_H
#define MONSTERCARD_H
#include "card.h"
#include <string>

class MonsterCard : public Card {
	public:
		int hp;
		int vp;

		MonsterCard(std::string n, std::string t, int health = 10, int victory = 10) :
			Card::Card(n, t), hp(health), vp(victory) {};

};

#endif