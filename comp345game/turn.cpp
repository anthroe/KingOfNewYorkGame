#include "turn.h"

turnObserver turn::observer;

void turn::notify(player* p) {
	observer.update(p);
}