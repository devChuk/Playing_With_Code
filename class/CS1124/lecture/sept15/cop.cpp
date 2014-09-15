#include <iostream>
#include <string>
using namespace std;

struct Person {
	string name;
	int age;
};

void displayPerson(const Person& aPerson) {
	cout << "Name: " << aPerson.name << ", age: " << aPerson.age << ".\n";
}

int main() {
	Person john;
	john.name = "John";
	john.age = 17;
	displayPerson(john);
}