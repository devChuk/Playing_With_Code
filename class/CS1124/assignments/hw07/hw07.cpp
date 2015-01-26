#include "polynomial.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector<int> pol1;
	pol1.push_back(4);
	pol1.push_back(0);
	pol1.push_back(1);
	pol1.push_back(7);
	cout << "Polynomial 1" << endl;
	Polynomial first(3, pol1);

	cout << first << endl;

	vector<int> pol2;
	pol2.push_back(1);
	pol2.push_back(4);
	pol2.push_back(0);
	pol2.push_back(1);
	pol2.push_back(7);
	cout << "\nPolynomial 2" << endl;
	Polynomial second(3, pol2);
	cout << second << endl;
	cout << "\nPolynomial 1 += 2" << endl;
	first += second;

	cout << "\nPolynomial 1" << endl;
	cout << first << endl;

	cout << "\nPolynomial 3" << endl;
	Polynomial third(3, pol2);
	cout << third << endl;

	cout << "\nPolynomial 1 == 2" << endl;
	cout << (first == second) << endl;

	cout << "\nPolynomial 2 != 3" << endl;
	cout << (second != third) << endl;

	//cout << second + third << endl;

}

/*
copy control
*/
