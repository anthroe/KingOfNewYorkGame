#include "Subject.h"
#include "Observer.h"

using namespace std;

Subject::Subject() {
	observers = new list<Observer*>;
}

Subject::~Subject() {
	delete observers;
}

void Subject::addObserver(Observer* o) {
	observers->push_back(o);
}

void Subject::removeObserver(Observer* o) {
	for (list<Observer*>::iterator itr = observers->begin(); itr != observers->end(); itr++) {
		if (*itr == o) {
			observers->erase(itr);
		}
	}
}

void Subject::notify(Observer* o) {
	// TODO get a specific observer to notify
}

void Subject::notifyAll() {
	list<Observer*>::iterator i = observers->begin();

	for (; i != observers->end(); ++i) {
		(*i)->update();
	}
}