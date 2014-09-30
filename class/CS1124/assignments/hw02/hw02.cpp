/*We are modeling a game of medieval times. Our world is filled with warriors. Naturally what warriors like to do is fight. To the death. So we happily let them.
Each warrior starts out with a name and a certain amount of strength. Each time he fights, he loses some strength. (He gets to keep his name.) If his opponent is stronger than he is, then he loses all of his strength, in which case he is dead, or at the very least pretty useless as a fighter. Otherwise he loses as much strength as his opponent had. Of course, if he and his opponent had the same strength then they are both losers.
Even losers are allowed to pick a fight. It doesn't require having any strength in order to do battle with someone else. Not that you stand much of a chance of winning anything, but perhaps it's worth getting beaten (again) just to have those 15 seconds of fame.
Your program will read in a file of commands. There are three types of commands:
Warrior creates a new warrior with the specified name and strength.
Battle causes a battle to occur between two warriors.
Status lists all warriors, alive or dead, and their strengths.*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Warrior {
	string name;
	int strength;
};



void warrior(vector<Warrior>& warriors, string name, int strength) {
	//creates a new warrior with the specified name and strength
	Warrior newWarrior;
	newWarrior.name = name;
	newWarrior.strength = strength;

	warriors.push_back(newWarrior);
}

int searchWarrior(vector<Warrior>& warriors, string name) {
	//searches for a warrior in the warriors vector and returns an int of its location.
	int index = -1;
	for (int i = 0; i < warriors.size(); i++) {
		if (warriors[i].name == name) {
			index = i;
			break;
		}
		return i;
	}
}

int battle(vector<Warrior>& warriors, string name1, string name2) {
	//causes a battle between two warriors
	int a = searchWarrior(warriors, name1);
	int b = searchWarrior(warriors, name2);
	if (warriors[a].strength == 0 && warriors[b].strength == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
		return 0;
	}
	cout << warriors[a].name << " battles " << warriors[b].name << endl;

	if (warriors[a].strength > warriors[b].strength) {
	//if warrior A is stronger
		warriors[a].strength -= warriors[b].strength;
		warriors[b].strength = 0;
		if (warriors[a].name == "Jim") {
			cout << "He's dead Jim" << endl;
		}
		else {
			cout << warriors[a].name << " defeats " << warriors[b].name << endl;
		}
	}
	else if (warriors[b].strength > warriors[a].strength) {
	//if warrior B is stronger
		warriors[b].strength -= warriors[a].strength;
		warriors[a].strength = 0;
		if (warriors[b].name == "Jim") {
			cout << "He's dead Jim" << endl;
		}
		else {
			cout << warriors[b].name << " defeats " << warriors[a].name << endl;
		}
	}
	else {
	//if they are equally matched
		warriors[a].strength = 0;
		warriors[b].strength = 0;
		cout << "Mutual Annihalation: " << warriors[a].name << " and " << warriors[b].name << " die at each other's hands" << endl;
	}
}

void status(vector<Warrior> warriors) {
	//lists all warriors, alive or dead, and their strengths
	cout << "There are: " << warriors.size() << " warriors\n";
	for (int i = 0; i < warriors.size(); i++) {
		cout << "Warrior: " << warriors[i].name << ", strength: " << warriors[i].strength << endl;
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
			ifs >> strength;
			warrior(warriors, name, strength);
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