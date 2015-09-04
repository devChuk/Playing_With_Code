#ifndef NOBLE_H
#define NOBLE_H
#include <vector>
#include <iostream>
#include <string>
#include "Warrior.h"

namespace WarriorCraft {
	class Warrior;
	class Noble {
	public:
		Noble(const std::string newName);
		void hire(Warrior& warrior);
		std::vector<Warrior*> getArmy() const;
		std::string getName() const;
		void remove(const std::string f);
		void battle(Noble& lord);
		int getStrength();
		int isdead();
		void die();
		void weaken(double per);

	private:
		int dead; //1 if dead
		std::string name;
		std::vector<Warrior*> warriors;

	};
	/*
	double per = 1 - (double)target.getStrength()/getStrength();
		for (int i = 0; i < warriors.size(); i++) {
				warriors[i]->setStrength(warriors[i]->getStrength() * per);
			}
		}*/
	std::ostream& operator<<(std::ostream& os, const Noble& nob);
}
#endif