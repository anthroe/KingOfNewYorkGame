#include "monsterCard.h"

bool MonsterCard::changeHP(int n) {
	// Do not let a monster exceed 10 hp
	if (hp + n <= 10)
		hp += n;
	// Do not let a monster subceed 0 hp
	else if (hp + n <= 0)
		hp = 0;
	else
		return false;

	return true;
}

bool MonsterCard::changeVP(int n) {
	// Do not let a monster subceed 0 vp
	if (vp + n <= 0)
		vp = 0;
	else
		vp += n;
	return true;
}