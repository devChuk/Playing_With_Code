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
	void hire(Warrior* warrior) {
		warriors.push_back(warrior);
	}
	//fire a Warrior
	Warrior* fire(string warrior) {
		for (int i = 0; i < warriors.size(); i++) {
			if (warriors[i]->getName() == warrior) {
				cout << warrior << ", you're fired! -- " << name << endl;
				Warrior* temp = warriors[i];
				warriors.erase(warriors.begin()+i);
				return temp;
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
		else {
			cout << "Mutual Annihalation: " << name << " and " << target.getName() << " die at each other's hands" << endl;
			for (int i = 0; i < warriors.size(); i++) {
				warriors[i]->setStrength(0);
			}
			for (int i = 0; i < target.warriors.size(); i++) {
				target.warriors[i]->setStrength(0);
			}
			die();
			target.die();}
	}

private:
	int dead; //1 if dead
	string name;
	vector<Warrior*> warriors;

};

void warrior(vector<Warrior*>& warriors, string name, int strength) {
	//creates a new warrior with the specified name and strength
	Warrior* ptemp = new Warrior(name, strength);
	warriors.push_back(ptemp);
}

void hireWarrior(vector<Warrior*>& warriors, vector<Noble*> &nobles, string noble, string warrior) {
	for (int i = 0; i < nobles.size(); i++) {
		if (nobles[i]->getName() == noble) {
			for (int j = 0; j < warriors.size(); j++) {
				if (warriors[j]) {
					if (warriors[j]->getName() == warrior) {
						nobles[i]->hire(warriors[j]);
						warriors[j] = NULL;
					}
				}
			}
		}
	}
}

void fireWarrior(vector<Warrior*>& warriors, vector<Noble*> &nobles, string noble, string warrior) {
	for (int i = 0; i < nobles.size(); i++) {
		if (nobles[i]->getName() == noble) {
			warriors.push_back(nobles[i]->fire(warrior));
		}
	}
}

void battle(vector<Noble*> &nobles, string n1, string n2) {
	for (int i = 0; i < nobles.size(); i++) {
		if (nobles[i]->getName() == n1) {
			for (int j = 0; j < nobles.size(); j++) {
				if (nobles[j]->getName() == n2) {
					nobles[i]->battle(*nobles[j]);
				}
			}
		}
	}
}

void status(vector<Warrior*>& warriors, vector<Noble*> &nobles) {
	cout << "Status\n" << "======\n" << "Nobles:\n" << endl;
	for (int i = 0; i < nobles.size(); i++) {
		nobles[i]->display();
	}
	cout << "Unemployed Warriors:\n" << endl;
	for (int j = 0; j < warriors.size(); j++) {
		if (warriors[j])
			cout << warriors[j]->getName() << ": " << warriors[j]->getStrength() << endl;
	}
	/*
		//lists all warriors, alive or dead, and their strengths
	cout << "There are: " << warriors.size() << " warriors\n";
	for (int i = 0; i < warriors.size(); i++) {
		cout << "Warrior: " << warriors[i].name << ", weapon: " << warriors[i].getWeaponName() << ", " << warriors[i].getWeaponStrength() << endl;
	}
	*/
}

void readandprocessFile(ifstream& ifs, vector<Warrior*>& warriors, vector<Noble*> &nobles){
	//opens txt and processes the information
	string s;
	string name;
	string name2;
	int strength;
	while(ifs >> s) {
		if (s == "Warrior") {
			ifs >> name;
			ifs >> strength;
			warrior(warriors, name, strength);
		}
		else if (s == "Noble") {
			ifs >> name;
			Noble* pTemp = new Noble(name);
			nobles.push_back(pTemp);
		}
		else if (s == "Hire") {
			ifs >> name;
			ifs >> name2;
			hireWarrior(warriors, nobles, name, name2);
		}
		else if (s == "Fire") {
			ifs >> name;
			ifs >> name2;
			fireWarrior(warriors, nobles, name, name2);
		}
		else if (s == "Battle") {
			ifs >> name;
			ifs >> name2;
			battle(nobles, name, name2);
		}
		else if (s == "Status") {
			status(warriors, nobles);
		}
		else if (s == "Clear") {
			for (int i = 0; i < warriors.size(); i++) {
				delete warriors[i];
				warriors[i] = NULL;
			}
			warriors.clear();
			for (int i = 0; i < nobles.size(); i++) {
				delete nobles[i];
				nobles[i] = NULL;
			}
			nobles.clear();
		}
		else {
			cout << s << ": command not found\n";
		}
	}
}

int main() {
	ifstream ifs("nobleWarriors.txt");
	vector<Warrior*> warriors;
	vector<Noble*> nobles;
	readandprocessFile(ifs, warriors, nobles);
	ifs.close();
}