#pragma once
#ifndef MONSTERCARD_H
#define MONSTERCARD_H
#include "cardTypes.h"
#include "card.h"
#include <string>

class MonsterCard : public Card {
	private:
		int hp;
		int vp;

	public:
		MonsterCard(std::string n, int health = 10, int victory = 10) :
			Card::Card(n, CardTypes::MONSTER_CARD), hp(health), vp(victory) {};
		int getHP() { return hp; };
		int getVP() { return vp; };
		bool changeHP(int n);
		bool changeVP(int n);
};

#endif