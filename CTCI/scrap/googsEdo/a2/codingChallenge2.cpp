#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>

#include <vector>
#include <string>
#include <unordered_map>

struct Node {
	Node(int item) {
		id = item;
	}

	int id;
	bool visited = false;
	std::vector<Node*> adjacentNodes;
};

void traverse(Node* root, int& size) {
	root->visited = true;
	size++;
	for (int i = 0; i < root->adjacentNodes.size(); i++) {
		if (!root->adjacentNodes[i]->visited)
			traverse(root->adjacentNodes[i], size);
	}
}

int countGroupSize(Node* root) {
	int size = 0;
	if (!root->visited)
		traverse(root, size);
	return size;
}


int main() {
	// setup read-only file input stream
	std::ifstream infile; 
   	infile.open("task2-sample-input.txt");
   	std::string line;
   	int caseNumber = 1;

	// setup write-only file output stream
	std::ofstream outfile;
	outfile.open("task2-test-output.txt");

	//process total number of test cases
	std::getline(infile, line);
	int totalTestCases = std::stoi(line);

	//handle blank line
	std::getline(infile, line);

	std::cout << totalTestCases << std::endl;

	while (caseNumber <= totalTestCases) {
		
		// process N, number of nodes
		std::getline(infile, line);
		int n = std::stoi(line);
		std::cout << "\n\n||||||||||||||||||||\n" << n << "\n";


		// process D, number of direct connections
		std::getline(infile, line);
		int d = std::stoi(line);
		std::cout << d << "\n";


		// process direct connections
		std::unordered_map<int, Node*> nodes;
		for (int i = 0; i < d; i++) {
			std::getline(infile, line);
			std::istringstream iss(line);
			int a, b;
			if (!(iss >> a >> b)) {
				std::cout << "ERROR: number of test cases does not match N" << std::endl;
				return 0;
			}

			Node* nodeA;
			Node* nodeB;
			if (nodes.find(a) == nodes.end()) {
				nodeA = new Node(a);
				nodes[a] = nodeA;
			} else {
				nodeA = nodes[a];
			}

			if (nodes.find(b) == nodes.end()) {
				nodeB = new Node(b);
				nodes[b] = nodeB;
			} else {
				nodeB = nodes[b];
			}

			if (nodeA != nodeB) {
				std::vector<Node*> AdjNodesA = nodeA->adjacentNodes;
				if (std::find(AdjNodesA.begin(), AdjNodesA.end(), nodeB) == AdjNodesA.end()) {
					nodeA->adjacentNodes.push_back(nodeB);
				}

				std::vector<Node*> AdjNodesB = nodeB->adjacentNodes;
				if (std::find(AdjNodesB.begin(), AdjNodesB.end(), nodeA) == AdjNodesB.end()) {
					nodeB->adjacentNodes.push_back(nodeA);
				}
			}

			std::cout << a << b << std::endl;
		}
		std::cout << "\nOUTPUT: " << std::endl;

		std::vector<int> sizes;
		for (std::pair<int, Node*> element : nodes) {
			Node* node = element.second;
			int size = countGroupSize(node);
			if (size != 0)
				sizes.push_back(size);
		}

		std::sort(sizes.begin(), sizes.end());
		// std::reverse(sizes.begin(), sizes.end());
		std::string outputSizes;
		for (int i = 0; i < sizes.size(); i++) {
			outputSizes += std::to_string(sizes[i]) + " ";
		}
		std::cout << outputSizes << std::endl;

		// submit output
		std::string identifier = "Case #" + std::to_string(caseNumber) + ": ";
		std::string outputString = identifier + outputSizes;
		outfile << outputString << std::endl;

		// handle blank line
		std::getline(infile, line);
		caseNumber++;
	}


	infile.close();
	outfile.close();
	return 0;
}