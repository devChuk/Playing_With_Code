#ifndef WARRIOR_H
#define WARRIOR_H
#include <vector>
#include <iostream>
#include <string>

namespace WarriorCraft {
	class Noble;
	class Warrior {
	public:
		Warrior(const std::string newName, const int newStrength);
		std::string getName() const;
		int getStrength() const;
		void setStrength(int hurr);
		void boss(Noble* boss);
		void runaway();
	private:
		std::string name;
		int strength;
		Noble* noble;
	};
}
#endif