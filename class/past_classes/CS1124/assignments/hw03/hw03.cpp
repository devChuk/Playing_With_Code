/*We will model a game of medieval times. Our world is filled with nobles and warriors. Nobles don't have much to do except do battle with each other. (We'll leave the feasting and other entertainments for add-ons.) Warriors don't have much to do except hire out to a noble and fight in his behalf. Of course the nobles are pretty wimpy themselves and will lose if they don't have warriors to defend them.*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

class Warrior {
public:
	//Warrior constructor
	Warrior(const string newName, const int newStrength)
		:name(newName), strength(newStrength) {}

	string getName() const {
		return name;
	}
	int getStrength() const {
		return strength;
	}
	void setStrength(int hurr) {
		strength = hurr;
	}
private:
	string name;
	int strength;

};

class Noble {
public:
	//Noble constructor
	Noble(const string& newName)
		: name(newName), dead(0) {}
	//hire a Warrior
	void hire(Warrior& warrior) {
		Warrior* p;
		p = &warrior;
		warriors.push_back(p);
	}
	//fire a Warrior
	void fire(Warrior& warrior) {
		for (int i = 0; i < warriors.size(); i++) {
			if (warriors[i]->getName() == warrior.getName()) {
				cout << warrior.getName() << ", you're fired! -- " << name << endl;
				warriors.erase(warriors.begin()+i);
				break;
			} 
		}
	}
	//returns the name
	string getName() const {
		return name;
	}
	//checks if alive
	int uded() {
		return dead;
	}

	int die() {
		dead = 1;
	}
	//display all warriors and their strengths
	void display() {
		cout << name << " has an army of " << warriors.size() << "\n";
		for (Warrior* warrior : warriors) {
			cout << "\t" << warrior->getName() << ": " << warrior->getStrength() << endl;
		}
	}
	//get the total strength of the army
	int getStrength() {
		int s = 0;
		for (int i = 0; i < warriors.size(); i++) {
			s+= warriors[i]->getStrength();
		}
		return s;
	}
	//attack another noble
	void battle(Noble& target) {
		cout << name << " battles " << target.getName() << endl;
		if (uded() && target.uded()) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
			die();
			target.die();
		}
		else if (getStrength() > target.getStrength() || target.uded()) {
			double per = 1 - (double)target.getStrength()/getStrength();
			for (int i = 0; i < warriors.size(); i++) {
				warriors[i]->setStrength(warriors[i]->getStrength() * per);
			}
			target.die();
			if (name == "Jim") {
				cout << "He's dead Jim" << endl;
			}
			else
				cout << name << " defeats " << target.getName() << endl;
			
		}
		else if (getStrength() < target.getStrength() || uded()) {
			double per = 1 - getStrength()/(double)target.getStrength();
			for (int i = 0; i < target.warriors.size(); i++) {
				target.warriors[i]->setStrength(target.warriors[i]->getStrength() * per);
			}
			cout << target.getName() << " defeats " << name << endl;
			die();

		}
		else
			cout << "Mutual Annihalation: " << name << " and " << target.getName() << " die at each other's hands" << endl;
			for (int i = 0; i < warriors.size(); i++) {
				warriors[i]->setStrength(0);
			}
			for (int i = 0; i < target.warriors.size(); i++) {
				target.warriors[i]->setStrength(0);
			}
			die();
			target.die();
	}

private:
	int dead; //1 if dead
	string name;
	vector<Warrior*> warriors;

};


int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}