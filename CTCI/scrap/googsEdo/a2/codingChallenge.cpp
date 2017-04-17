#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include <vector>
#include <string>


int main() {
`	// setup read-only file input stream
`	std::ifstream infile; 
`   	infile.open("task1-test-input.txt");
`   	std::string line;
`   	int caseNumber = 1;

`	// setup write-only file output stream
`	std::ofstream outfile;
`	outfile.open("task1-test-output.txt");

`	//process total number of test cases
`	std::getline(infile, line);
`	int totalTestCases = std::stoi(line);

`	//handle blank line
`	std::getline(infile, line);

`	while (caseNumber <= totalTestCases) {

`		// process N, number of tests
`		std::getline(infile, line);
`		int n = std::stoi(line);

`		// process test cases and calculate average
`		std::getline(infile, line);
`		std::istringstream iss(line);
`		std::vector<float> testCases;
`		float average = 0;

`		for (int i = 0; i < n; i++) {
`			std::string testCase;
`			if (!(iss >> testCase)) {
`				std::cout << "ERROR: number of test cases does not match N" << std::endl;
`				return 0;
`			}

`			float testCaseFloat = std::stof(testCase);
`			average += testCaseFloat;
`			testCases.push_back(testCaseFloat);
`		}
`		average /= (float) n;


`		// calculate variance
`		float variance = 0;
`		for (int i = 0; i < n; i++) {
`			variance += pow(testCases[i] - average, 2);
`		}
`		variance /= (float) n;


`		// calculate standardized scores and reformat into a string
`		std::string outputTestCases;
`		for (int i = 0; i < n; i++) {
`			float standardizedScore;
`			if (variance != 0.0f) {
`				standardizedScore = 50 + 10 * (testCases[i] - average) / pow(variance, 0.5f);
`			} else {
`				standardizedScore = 50.0f;
`			}
`			outputTestCases += std::to_string(standardizedScore) + " ";
`		}


`		// submit output
`		std::string identifier = "Case #" + std::to_string(caseNumber) + ": ";
`		std::string outputString = identifier + outputTestCases;
`		outfile << outputString << std::endl;


`		// handle blank line
`		std::getline(infile, line);
`		caseNumber++;
`	}


`	infile.close();
`	outfile.close();
`	return 0;
}