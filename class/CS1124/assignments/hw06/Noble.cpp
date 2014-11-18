#include "Noble.h"
#include "Warrior.h"
#include <vector>
#include <iostream>
#include <string>
	using namespace std;

namespace WarriorCraft {
	Noble::Noble(const string newName) : name(newName), dead(0) {}
	void Noble::hire(Warrior& warrior) {
		warrior.boss(this);
		Warrior* p;
		p = &warrior;
		warriors.push_back(p);
	}
	string Noble::getName() const{
		return name;
	}
	std::vector<Warrior*> Noble::getArmy() const{
		return warriors;
	}
	void Noble::remove(const string f) {
		for (int i = 0; i < warriors.size(); i++)
			if (warriors[i]->getName() == f)
				warriors.erase(warriors.begin()+i);
	}
	ostream& operator<<(ostream& os, const Noble& nob) {
		os << nob.Noble::getName() << " has an army of " << nob.Noble::getArmy().size() << "\n";	
		for (int i = 0; i < nob.Noble::getArmy().size(); i++) {
			os << "\t" << nob.Noble::getArmy()[i]->getName() << ": " << nob.Noble::getArmy()[i]->getStrength() << endl;
		}
		return os;
	}
	int Noble::isdead() {
		return dead;
	}
	int Noble::getStrength() {
		int powa = 0;
		for (int i = 0; i < warriors.size(); i++) {
			powa += warriors[i]->getStrength();
		}
		return powa;
	}
	void Noble::die() {
		dead = 1;
	}
	void Noble::weaken(double per) {
		for (int i = 0; i < warriors.size(); i++) {
			warriors[i]->setStrength(warriors[i]->getStrength() * per);
		}
	}
	void Noble::battle(Noble& lord) {
		cout << name << " battles " << lord.Noble::getName() << endl;
		// cout << Noble::getStrength() << endl;
		// cout << lord.Noble::getStrength() << endl;
		if (dead && lord.Noble::isdead()){
			cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
		}
		else if (dead) {
			cout << "He's dead, " << lord.Noble::getName() << endl;
		}
		else if (lord.Noble::isdead()) {
			cout << "He's dead, " << Noble::getName() << endl;
		}
		else if (Noble::getStrength() > lord.Noble::getStrength()) {
			cout << name << " defeats " << lord.Noble::getName() << endl;
			double per = 1 - (double)lord.Noble::getStrength()/Noble::getStrength();
			Noble::weaken(per);
			lord.Noble::die();
		}
		else if (Noble::getStrength() < lord.Noble::getStrength()) {
			cout << lord.Noble::getName() << " defeats " << name << endl;
			double per = 1 - (double)Noble::getStrength()/lord.Noble::getStrength();
			lord.Noble::weaken(per);
			Noble::die();
		}
		else {
			cout << "Mutual Annialation" << endl;
			Noble::die(); lord.Noble::die();
		}
	}
}