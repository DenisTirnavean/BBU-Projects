#pragma once
#include <vector>
using namespace std;

class Observer {
public:
	//functie de update continut al obiectul observer
	virtual void update()=0;
};

class Observable {
public:

	//functie care ataseaza un nou observator la obiectul observabil
	void add_observer(Observer* obs) {
		observatori.push_back(obs);
	}

	//functie care detaseaza observatorul de obicetul observabil
	void remove_observer(Observer* obs) {
		observatori.erase(remove(begin(observatori), end(observatori), obs), observatori.end());
	}
protected:
	//functia care semnaleaza tuturor observatorilor un eveniment care necesita update
	void notify() {
		for (auto obs : observatori)
		{
			obs->update();
		}
	}

private:
	vector<Observer*> observatori;

};