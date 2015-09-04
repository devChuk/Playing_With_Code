/*
  oop.cpp
  Object Oriented Programming
  Sec A
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Date {
public:
    Date(int m, int d, int y) : month(m), day(d), year(y) { }
    void display(ostream& os = cout) const {
	os << month << '/' << day << '/' << year;
    }
private:
    int month, day, year;
};

//struct Person {
class Person {
public:
    // Constructor
    // Person(const string& aName, int theAge) : name(aName), age(theAge)
    // Person(const string& aName, int age)
    // 	: name(aName), age(age)
    // {
    // 	//	name = aName;
    // 	// age = theAge;
    // }
    Person(const string& aName, int age, int m, int d, int y)
    //	: name(aName), age(age), dob(Date(m, d, y))
	: name(aName), age(age), dob(m, d, y)
    {
	// Date aDate(m, d, y);
	// dob = aDate;
	//	name = aName;
	// age = theAge;
    }

    // Getter / Accessor
    string getName() const { return name; }
    int getAge() const { return age; }

    // Setter / Mutator
    //void setName(const string& aName) { name = aName; }

    // void display() const {
    // 	//	cout << "Name: " << name << ", age: " << age << ".\n";
    // 	display(cout);
    // }
    void display(ostream& os = cout) const {
	os << "Name: " << name << ", age: " << age
	   << ", dob: ";
	dob.display(os);  // Delegation
	os << ".\n";
    }

    void walk(int steps) {
	for (int i = 0; i < steps; ++i) {
	    cout << "step ";
	}
	cout << endl;
    }
    
private:
    string name;
    int age;
    Date dob;
};

void displayPerson(const Person& aPerson) {
    //    cout << "Name: " << aPerson.name << ", age: " << aPerson.age << ".\n";
    cout << "Name: " << aPerson.getName()
	 << ", age: " << aPerson.getAge() << ".\n";
}

int main() {
    //    Person john;
    Person john("John", 17);
    //    john.name = "John";
    //    john.setName("John");
    
    //    john.age = 17;
    displayPerson(john);
    john.walk(20);
    john.display();
    john.display();

    ifstream ifs("peopleAge");
    if (!ifs) {}

    vector<Person> vp;
    
    string name;
    int age;
    while (ifs >> name >> age) {
	Person someone(name, age);
	vp.push_back(someone);
    }

    for(const Person& p : vp) {
	p.display();
    }
    //    cout << john << endl;

    Date aDate(7, 3, 1949);
    aDate.display();
    cout << endl;
}