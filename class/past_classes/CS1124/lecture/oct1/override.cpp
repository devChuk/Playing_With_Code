#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

class Base {
public:
	virtual void whereAmI() { cout << "Base\n";}
};

class Derived : public Base {
public:
	void whereAmI() override { cout << "Derived\n";}
};

void foo(Base& thing) {
	thing.whereAmI();
}

int main() {
	Base base;
	foo(base);
	Derived der;
	foo(der);
}