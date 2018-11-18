#pragma once
#include <set>

using namespace std;

class Observer;

class Subject {

private:
	set<Observer*> observers;

public:
	virtual void addObserver(Observer* o);
	virtual void removeObserver(Observer* o);
	virtual void notify(Observer* o);
	virtual void notifyAll();
};
