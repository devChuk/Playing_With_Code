/*We will expand our Warrior a little. Each Warrior will have a weapon. He is "born" with it, i.e. the weapon is created together with the warrior. It can only be accessed by him. It provides him with his strength. In battle, weapons lose their edge and weaken. When a Warrior's weapon loses all of its strength, the Warrior himself dies.*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

class Weapon {
public:
	string name;
	int strength;

	Weapon(const string& weapName, const int& s) {
		name = weapName;
		strength = s;
	}

	string getName() const {return name;}
	int getStrength() const {return strength;}

	void setStrength(const int& newS) {
		strength = newS;
	}

};

class Warrior {
public:
	//Person(const string& fn, const string& ln, const string& birthday)
	//  : bday(birthday), firstName(fn), lastName(ln), spouse(NULL) {
	Warrior(const string& nname, const string& weapName, const int strength)
		: name(nname), sword(weapName, strength) {
	}

	string getWeaponName() {
		return sword.getName();
	}

	int getWeaponStrength() {
		return sword.getStrength();
	}

	void setWeaponStrength(int i) {
		sword.setStrength(i);
	}

	string getName() {
		return name;
	}

private:
	Weapon sword;
	string name;
};

void warrior(vector<Warrior>& warriors, string name, string weapName, int strength) {
	//creates a new warrior with the specified name and strength
	warriors.push_back(Warrior(name, weapName, strength));
}

int searchWarrior(vector<Warrior>& warriors, string name) {
	//searches for a warrior in the warriors vector and returns an int of its location.
	int index = -1;
	for (int i = 0; i < warriors.size(); i++) {
		if (warriors[i].name == name) {
			index = i;
			break;
		}
	}
	return index;
}

int battle(vector<Warrior>& warriors, string name1, string name2) {
	//causes a battle between two warriors
	int a = searchWarrior(warriors, name1);
	int b = searchWarrior(warriors, name2);
	cout << warriors[a].name << " battles " << warriors[b].name << endl;

	if (warriors[a].getWeaponStrength() == 0 && warriors[b].getWeaponStrength() == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
		return 0;
	}

	if (warriors[a].getWeaponStrength() > warriors[b].getWeaponStrength()) {
	//if warrior A is stronger
		warriors[a].setWeaponStrength(warriors[a].getWeaponStrength() - warriors[b].getWeaponStrength());
		warriors[b].setWeaponStrength(0);
		if (warriors[a].name == "Jim") {
			cout << "He's dead Jim" << endl;
		}
		else {
			cout << warriors[a].name << " defeats " << warriors[b].name << endl;
		}
	}
	else if (warriors[b].getWeaponStrength() > warriors[a].getWeaponStrength()) {
	//if warrior B is stronger
		warriors[b].setWeaponStrength(warriors[b].getWeaponStrength() - warriors[a].getWeaponStrength());
		warriors[a].setWeaponStrength(0);
		if (warriors[b].name == "Jim") {
			cout << "He's dead Jim" << endl;
		}
		else {
			cout << warriors[b].name << " defeats " << warriors[a].name << endl;
		}
	}
	else {
	//if they are equally matched
		warriors[a].setWeaponStrength(0);
		warriors[b].setWeaponStrength(0);
		cout << "Mutual Annihalation: " << warriors[a].name << " and " << warriors[b].name << " die at each other's hands" << endl;
	}
}

void status(vector<Warrior> warriors) {
	//lists all warriors, alive or dead, and their strengths
	cout << "There are: " << warriors.size() << " warriors\n";
	for (int i = 0; i < warriors.size(); i++) {
		cout << "Warrior: " << warriors[i].name << ", weapon: " << warriors[i].getWeaponName() << ", " << warriors[i].getWeaponStrength() << endl;
	}
}

void readandprocessFile(ifstream& ifs, vector<Warrior>& warriors){
	//opens warriors.txt and processes the information
	string s;
	string name;
	string name2;
	int strength;
	while(ifs >> s) {
		if (s == "Warrior") {
			ifs >> name;
			ifs >> name2;
			ifs >> strength;
			warrior(warriors, name, name2, strength);
		}
		else if (s == "Battle") {
			ifs >> name;
			ifs >> name2;
			battle(warriors, name, name2);
		}
		else if (s == "Status") {
			status(warriors);
		}
		else {
			cout << s << ": command not found\n";
		}
	}
}


int main() {
	//The main function that pulls it all together.
	ifstream ifs("warriors.txt");
	vector<Warrior> warriors;
	readandprocessFile(ifs, warriors);
	ifs.close();
}