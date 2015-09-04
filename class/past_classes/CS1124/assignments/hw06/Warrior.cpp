#include "Warrior.h"
#include "Noble.h"
#include <vector>
#include <iostream>
#include <string>
	using namespace std;

namespace WarriorCraft {
	Warrior::Warrior(const string newName, const int newStrength) : name(newName), strength(newStrength) {}
	string Warrior::getName() const {
		return name;
	}
	int Warrior::getStrength() const {
		return strength;
	}
	void Warrior::setStrength(int hurr) {
		strength = hurr;
	}
	void Warrior::boss(Noble* boss) {
		noble = boss;
	}
	void Warrior::runaway() {
		noble->remove(name);
		noble = NULL;
	}
}