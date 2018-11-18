#include "Subject.h"
#include "Observer.h"

using namespace std;

void Subject::addObserver(Observer* o) {
	observers.insert(o);
}

void Subject::removeObserver(Observer* o) {
	observers.erase(o);
}

void Subject::notify(Observer* o) {
	o->update();
}

void Subject::notifyAll() {
	for (set<Observer*>::iterator i = observers.begin(); i != observers.end(); i++) {
		(*i)->update();
	}
}