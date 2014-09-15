#include <iostream>
#include <string>
using namespace std;

//struct Person {
class Person {
public:
	//Constructors
	Person(const string& theName, int theAge) : name(theName) {
		//some code
	}

	//setters / mutators
	void setName(const string& theName) {
		name = theName;
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
//	john.setName("John");
//	john.age = 17;
	displayPerson(john);
}