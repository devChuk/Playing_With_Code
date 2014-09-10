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

	//loop for file filling vector
	string token;
	while (wordStream >> token) {


	//get a token

	//is it there?

		// if yes, then we have found a word object in the collection and we simply need to update its position
		// not? Add a new Word object for this token with its position.
	}
}