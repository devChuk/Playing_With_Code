#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
	using namespace std;



int main() {
	string input;
	while (cin >> input) {
		if (input == "EXIT") {
			cout << "Program ended" << endl;
			break;
		}
		//cout << input[1] << endl;
		switch (input[1]) {
			case '+':
				int a = stoi(input[0]);
				int b = stoi(input[2]);

			break;
			case '/':
				cout << "/" << endl;
			break;
			case '-':
				cout << "-" << endl;
			break;
			case '*':
				cout << "*" << endl;
			break;
		}
	}
	return 0;
}