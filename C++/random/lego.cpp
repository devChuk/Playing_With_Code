#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <math.h>
using namespace std;

//321
//123


string reversi(string input) {
	if (input.length() <= 1) return input;
	else return reversi(input.substr(1)) + input.substr(0,1);
}

void reversi(int input) {
	if (input < 10) cout << input << endl;
	else {cout << input % 10; reversi(input / 10);}

	// else return ((input % 10) ) + reversi(input / 10);
}


int main() {
	reversi(1234);
}