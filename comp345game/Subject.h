#pragma once
#include <list>

using namespace std;

class Observer;

class Subject {

private:
	list<Observer*>* observers;

public:
	virtual void addObserver(Observer* o);
	virtual void removeObserver(Observer* o);
	virtual void notify(Observer* o);
	virtual void notifyAll();
	Subject();
	~Subject();

};
