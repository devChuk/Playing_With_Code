#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <math.h>
using namespace std;

string reversi(string input) {
	if (input.length() <= 1) return input;
	else return reversi(input.substr(1)) + input.substr(0,1);
}

void reversi(int input) {
	if (input < 10) cout << input << endl;
	else {cout << input % 10; reversi(input / 10);}
}

template <class Object>
Object summation(Object x, int n) {
	if (n <= 1) return x;
	else return x + summation(x, n - 1); 
}

void recPattern (int n) {
    if (n >= 1) {
        recPattern(n-1);
        cout << " " << n;
        recPattern(n-1);
    }
}

template<class Object>
Object sumVector( const vector<Object> & a) {
	
}

int main() {
	reversi(1234);
	reversi("1234");


	cout << summation(4, 4) << endl;

	recPattern(3);
}