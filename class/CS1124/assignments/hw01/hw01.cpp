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
using namespace std;

struct Warrior {
	string name;
	int strength;
};



void warrior(vector<Warrior>& warriors, string name, int strength) {
	Warrior newWarrior;
	newWarrior.name = name;
	newWarrior.strength = strength;

	warriors.push_back(newWarrior);
	//creates a new warrior with the specified name and strength
}

void battle(vector<Warrior>& warriors, string name1, string name2) {

	//causes a battle between two warriors
}

void status(vector<Warrior> warriors) {
	//lists all warriors, alive or dead, and their strengths
}

void readandprocessFile(ifstream ifs, vector<Warrior> warriors){
	//opens warriors.txt and processes the information
}

int main() {
	//The main function that pulls it all together. What didja expect?
	ifstream ifs("warriors.txt");
	vector<Warrior> warriors;
	readandprocessFile(ifs, warriors);
	ifs.close();
}