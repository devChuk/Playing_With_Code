#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Lord;

class Protector {
public:
	Protector(const string& newName, const int& newStrength): name(newName), strength(newStrength) {}
	string getName() const {return name;}
	int getStrength(){return strength;}
	Lord* getLord() const {return lord;}
	void setLord(Lord* newLord) {lord = newLord;}
	void weaken(const double& per) {strength *= per;}
	virtual void state() const = 0;
private:
	string name;
	int strength;
	Lord* lord;
};

class Wizard : public Protector {
public:
	Wizard(const string& newName, const int& newStrength) : Protector(newName, newStrength) {}
	void state() const {
		cout << "POOF!" << endl;
	}
};

class Warrior: public Protector {
public:
	Warrior(const string& newName, const int& newStrength) : Protector(newName,newStrength) {}
};

class Archer : public Warrior {
public:
	Archer(const string& newName, const int& newStrength) : Warrior(newName, newStrength) {}
	void state() const;
};

class Swordsman : public Warrior {
public:
	Swordsman(const string& newName, const int& newStrength) : Warrior(newName, newStrength) {}
	void state() const;
};

class Lord {
public:
	Lord(const string& newName) : name(newName), alive(1) {}
	string getName() const {return name;}
	void hires(Protector& protector) {
		if (protector.getLord()) {
			Protector* pProtector = &protector;
			protectors.push_back(pProtector);
			protector.setLord(this);
		}
	}
	virtual int getStrength() {
		int powa = 0;
		for (int i = 0; i < protectors.size(); i++) {
			powa += protectors[i]->getStrength();
		}
		return powa;
	}
	int isalive() {
		return alive;
	}
	void die() {
		alive = 0;
	}
	void battle(Lord* lord) {
		cout << name << " battles " << lord->getName() << endl;
		if (alive) {	
			for (int i = 0; i < protectors.size(); i++) {
				protectors[i]->state();
			}
		}
		// cout << getStrength() << endl;
		// cout << lord->getStrength() << endl;
		if (!alive && !lord->isalive()){
			cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
		}
		else if (!alive) {
			cout << "He's dead, " << lord->getName() << endl;
		}
		else if (!lord->isalive()) {
			cout << "He's dead, " << getName() << endl;
		}
		else if (getStrength() > lord->getStrength()) {
			cout << name << " defeats " << lord->getName() << endl;
			lord->die();
		}
		else if (getStrength() < lord->getStrength()) {
			cout << lord->getName() << " defeats " << name << endl;
			die();
		}
	}
private:
	string name;
	int alive; //1 if alive
	vector<Protector*> protectors;
};

class PersonWithStrengthToFight : public Lord {
public:
	PersonWithStrengthToFight(const string& newName, const int& newStrength): Lord(newName), strength(newStrength) {}
	int getStrength() {
		return strength;
		cout << "swag" << endl;
	}
private:
	int strength;
};

void Swordsman::state() const {
	cout << "CLANG! " << getName() << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
}
void Archer::state() const {
	cout << "TWANG! " << getName() << " says: Take that in the name of my lord, " << "Sam" << endl;
}

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    joe.battle(&randy);	
    joe.battle(&sam);	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    janet.battle(&barclay);	
    janet.hires(samantha);	
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(&barclay);	
    sam.battle(&barclay);	
    joe.battle(&barclay);
}       