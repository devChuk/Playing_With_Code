#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Word {
	string token;
	vector<int> positions;
};

int main() {

	vector<Word> words;

	ifstream wordStream("jabber.txt");
	if (!wordStream) {

	}
}