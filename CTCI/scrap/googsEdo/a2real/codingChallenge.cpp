#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

int calculateNumBtnPushes(std::unordered_map<char, int> keyMap, std::string s) {
	// given a word s. Calculates the number of button pushes needed to input the word given the key mappings
	int btnPushes = 0;
	for (int i = 0; i < s.length(); i++) {
		btnPushes += keyMap[s[i]];
	}
	return btnPushes;
}

int main() {
	// setup read-only file input stream
	std::ifstream infile; 
   	infile.open("task1-test-input.txt");
   	std::string line;
   	int caseNumber = 1;

	// setup write-only file output stream
	std::ofstream outfile;
	outfile.open("task1-test-output.txt");

	// setup associated button pushes for each letter.
	// This takes advantage of converting decimals ints to ASCII chars and most buttons have exactly 3 characters
	std::unordered_map<char, int> keyMap;
	int pushes = 1;
	for (int i = 65; i <= 90; i++) {
		if (i == 83 || i == 90) {		// used for S and Z, as they are fourth characters on buttons 6 & 8 respectively
			pushes = 4;
		}
		keyMap[(char)i] = pushes++;
		if (pushes >= 4) {
			pushes = 1;
		}
	}

	// process total number of test cases
	std::getline(infile, line);
	int C = std::stoi(line);

	while (caseNumber <= C) {
		caseNumber++;
		std::getline(infile, line);

		int result = calculateNumBtnPushes(keyMap, line);
		std::string identifier = "Case #" + std::to_string(caseNumber) + ": ";
		std::string outputString = identifier + std::to_string(result);
		outfile << outputString << std::endl;
	}
	return 0;
}