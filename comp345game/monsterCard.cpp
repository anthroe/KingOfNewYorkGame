#include "monsterCard.h"


MonsterCard::MonsterCard() {

}

bool MonsterCard::changeHP(int n) {
	// Do not let a monstersubceed 0 hp, nor exceed 10 hp
	if (hp + n >= 0 && hp + n <= 10)
		hp += n;
	else if (hp + n < 0)
		hp = 0;
	else if (hp + n >= 10)
		hp = 10;
	else
		return false;

	return true;
}

bool MonsterCard::changeVP(int n) {
	// Do not let a monster subceed 0 vp, nor exceed 20
	if (vp + n >= 0 && vp + n <= 20)
		vp += n;
	else if (vp + n < 0)
		vp = 0;
	else if (vp + n >= 20)
		vp = 20;
	else
		return false;

	return true;
}