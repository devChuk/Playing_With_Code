#include <iostream>
#include <climits>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;

class durr {
	~durr() {cout << "TGATWRTCAWVTVA" << endl;}

};

int main() {
	vector<durr*> durrs;
	durrs.push_back(new durr);
	delete[] &durrs; 
}