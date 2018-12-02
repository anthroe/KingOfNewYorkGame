#pragma once
#include "observer.h"
#include <iostream>
#include <string>

using namespace std;

class cardObserver : public Observer
{
	public:
		cardObserver() {};
		void update() {};
		void update(string, string);
		void displayCardEffect(string, string);
};
