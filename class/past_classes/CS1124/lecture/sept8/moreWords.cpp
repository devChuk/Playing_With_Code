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
	int position = 0;
	while (wordStream >> token) {	//get a token

		for (Word& w : words) {
			if (token == w.token) {
				w.positions.push_back(position);
				break;
			}
			else {

			}
			position++;


	//is it there?

		// if yes, then we have found a word object in the collection and we simply need to update its position
		// not? Add a new Word object for this token with its position.
		}
		if (!found) {
			
		}
	}
}