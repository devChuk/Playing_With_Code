#include <string>
#include <iostream>
	using namespace std;

int main() {
	for (int i = 1; i <= 100; i++) {
		string print = "";
		if (i % 3 == 0) {
			print += "Crackle";
		}
		if (i % 5 == 0) {
			print += "Pop";
		}
		if (print.length() == 0) {
			print += to_string(i);
		}
		cout << print << endl;
	}
}