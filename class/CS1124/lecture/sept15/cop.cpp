#include <iostream>
#include <string>
using namespace std;

//struct Person {
class Person {
public:
	//Constructors
	Person(const string& theName, int theAge) : name(theName), age(theAge) {
		//some code
	}

	//setters / mutators
	void setName(const string& theName) {
		name = theName;
	}
	//getter / accessor
	string getName() const {return name;} //you are promising the function won't modify anything
	int getAge() const{return age;}
	void walk(int steps) {
		for (int i = 0; i < steps; ++i) {
			cout << "step";
		}
		cout << endl;
	}

	void display() {
		cout << "Name: " << name << ", age: " << age << ".\n";
	}
private:
	string name;
	int age;
};

void displayPerson(const Person& aPerson) {
	cout << "Name: " << aPerson.name << ", age: " << aPerson.age << ".\n";
}

int main() {
	Person john("John", 17);
	Person mary();
//	john.setName("John");
//	john.age = 17;
	displayPerson(john);

	cout << john << endl;
}