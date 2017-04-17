#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int traverse(std::vector<std::vector<bool>> isVisited, int positionX, int positionY) {
	// given a starting position (X,Y). Returns number of dead ends in a labybrinth from the starting position.
	int result = 0;
	int isDeadEnd = true;
	isVisited[positionX][positionY] = true;

	if (isVisited[positionX + 1][positionY] == false) {
		result += traverse(isVisited, positionX + 1, positionY);
		isDeadEnd = false;
	}

	if (isVisited[positionX - 1][positionY] == false) {
		result += traverse(isVisited, positionX - 1, positionY);
		isDeadEnd = false;
	}

	if (isVisited[positionX][positionY + 1] == false) {
		result += traverse(isVisited, positionX, positionY + 1);
		isDeadEnd = false;
	}

	if (isVisited[positionX][positionY - 1] == false) {
		result += traverse(isVisited, positionX, positionY - 1);
		isDeadEnd = false;
	}

	if (isDeadEnd) {
		result = 1;
	}

	return result;
}

int main() {
	// setup read-only file input stream
	std::ifstream infile; 
   	infile.open("task2-test-input.txt");
   	std::string line;
   	int caseNumber = 1;

	// setup write-only file output stream
	std::ofstream outfile;
	outfile.open("task2-test-output.txt");

	// process total number of test cases
	std::getline(infile, line);
	int C = std::stoi(line);

	//handle blank line
	std::getline(infile, line);

	while (caseNumber <= C) {
		std::getline(infile, line);
		std::istringstream iss(line);
		int H, W;
		if (!(iss >> H >> W)) {
			std::cout << "ERROR (" << line << "): H & W input does not match" << std::endl;
			return 0;
		}

		// populate 2D vector to simulate labyrinth
		std::vector<std::vector<bool>> isVisited(H, std::vector<bool>(W, false));
		for (int i = 0; i < H; i++) {
			std::getline(infile, line);
			for (int j = 0; j < W; j++) {
				if (line[j] == '#') {
					isVisited[i][j] = true;
				}
			}
		}

		// traverse vector to find dead ends starting at S(1,2)
		// we use (0,1) instead because vectors start at index 0
		isVisited[0][1] = true;
		int result = traverse(isVisited, 1, 1);

		std::string identifier = "Case #" + std::to_string(caseNumber) + ": ";
		std::string outputString = identifier + std::to_string(result);
		outfile << outputString << std::endl;

		//handle blank line
		std::getline(infile, line);
		caseNumber++;
	}
	return 0;
}