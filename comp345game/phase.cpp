#include "phase.h"

phaseObserver phase::observer;

void phase::notify(player* p, string currPhase, string currAct) {
	observer.update(p, currPhase, currAct);
}