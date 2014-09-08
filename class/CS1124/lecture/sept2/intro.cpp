/*

#include <iostream>
using namespace std;

int main() {
	//	std::cout << "Hello CS1124!!\n";
	// auto x = "blah";
	cout << "Hello CS1124!!\n";
	//cout is a string terminal that represents standard output

}

//This program prints out a Hello CS1124!!

*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
	cout << "Hello CS1124!!\n";
	
	int x = 17;

	cout << "x: " << x << endl;

	string s = "I'm a string";

	if (x == 42) {
		cout << "It's the answer!\n";
	}
	else if (x == 17) {
		cout << "That's random\n";
	}

	while (x > 0) {
		--x;
	}

	for (int i = 0; i < 10; ++i) {
		cout << "i: " << i << endl;
	}

	do {
		cout << x << endl;
		++x;
	} while (x < 10); //the block of code up there gets done at least once

	//cin >> x;
	cout << "Input number is: " << x << endl; 
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	ifstream ifs; //input file stream
	ifs.open("numbers.txt");
	if (!ifs) {
		cerr << "Couldn't open numbers.txt\n";
		exit(1);
	}
	while (ifs >> x) { //try to read an int. if you succeed, then run the block below
		cout << "x: " << x << endl;
	}
	ifs.close();



	ifstream ifs2("numbers.txt");
	while (ifs2 >> s) {
		cout << "s: " << s << endl;
	}
	ifs2.close();

	vector<int> v;
	cout << v.size() << endl;
	v.push_back(17);
	v.push_back(42);
	v.push_back(28);
}