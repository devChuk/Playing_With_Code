#include <vector>
#include <string>
#include <sstream>

// Calculates the maximum number of three-person families that can be seated in the remaining unreserved seats, given: 
/*
    N - number of rows
    S - list of reserved seats
*/
int solution(int N, string &S) {
    // Initialize variables
    unsigned int capacity = 0;
    vector<vector<bool>> rows;
    std::vector<bool> seats = {true, true, true, true, true, true, true, true, true, true};
    for (int i = 0; i < N; i++) {
        rows.push_back(seats);
    }

    // Handle reserved seat string input
    string buffer;
    stringstream ss(S);
    while (ss >> buffer) {
        int rowNumber;
        if (buffer.length() == 2) {
            rowNumber = stoi(buffer.substr(0,1)) - 1;
        }
        else {
            rowNumber = stoi(buffer.substr(0,2)) - 1;
        }
        
        int seatLetter;
        seatLetter = ((int) buffer[buffer.length() - 1]) - 65;
        if (seatLetter >= 9)
            // handle letter I omission
            seatLetter--;
        
        rows[rowNumber][seatLetter] = false;
    }
    
    // Compute max capacity for families of three
    for (int i = 0; i < N; i++) {
        if (rows[i][0] && rows[i][1] && rows[i][2]) {
            capacity++;
        }
        if (rows[i][7] && rows[i][8] && rows[i][9]) {
            capacity++;
        }
        if (rows[i][4] && rows[i][5] && (rows[i][3] || rows[i][6])) {
            capacity++;
        }
    }

    return capacity;
}
//////////////////////////////////////////////////////////////////////////////////////////
/*
I finished both tasks 30 minutes early and I'm pretty sure they satisfy all cases.
Here's a cat
───────────────────────────────────────
───▐▀▄───────▄▀▌───▄▄▄▄▄▄▄─────────────
───▌▒▒▀▄▄▄▄▄▀▒▒▐▄▀▀▒██▒██▒▀▀▄──────────
──▐▒▒▒▒▀▒▀▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄────────
──▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▒▒▒▒▒▒▒▒▀▄──────
▀█▒▒▒█▌▒▒█▒▒▐█▒▒▒▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌─────
▀▌▒▒▒▒▒▒▀▒▀▒▒▒▒▒▒▀▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐───▄▄
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌▄█▒█
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▒█▀─
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█▀───
▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌────
─▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐─────
─▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▌─────
──▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐──────
──▐▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▌──────
────▀▄▄▀▀▀▀▀▄▄▀▀▀▀▀▀▀▄▄▀▀▀▀▀▄▄▀────────
*/
#include <vector>

// Used to represent a city. nodes represents adjacent cities
struct Node {
    Node() {}
    vector<Node*> nodes;
    bool visited = false;
};

// Recursively runs through a graph via depth-first-search, starting at a capital
/*
    numCityDistances - stores the number of each city positioned at a distance from the capital
    root - the current city
    distance - keeps track of how far away from the capital the current city is
*/
void calculateDistances(vector<int> &numCityDistances, Node* root, int distance) {
    root->visited = true;
	for (unsigned int i = 0; i < root->nodes.size(); i++) {
		Node* neighbor = root->nodes[i];
		if (!neighbor->visited) {
		    numCityDistances[distance]++;
		    calculateDistances(numCityDistances, neighbor, distance + 1);
		}
	}
}

// Returns a vector that specifies the number of cities positioned at certain distances
/*
    T - a vector that describes a network of cities
*/
vector<int> solution(vector<int> &T) {
    // Initialize variables
    vector<int> numCityDistances;
    vector<Node*> cities;
    Node* capital;
    for (unsigned int i = 0; i < T.size() - 1; i++) {
        numCityDistances.push_back(0);
    }
    for (unsigned int i = 0; i < T.size(); i++) {
        cities.push_back(new Node());
    }

    // Run through T and generate roads. Find the capital.
    for (int i = 0; i < T.size(); i++) {
    	if (i == T[i]) {
    		capital = cities[i];
    	} else {
    	    cities[i]->nodes.push_back(cities[T[i]]);
    	    cities[T[i]]->nodes.push_back(cities[i]);
    	}
    }

    // Compute result
    calculateDistances(numCityDistances, capital, 0);

    return numCityDistances;
}

// Generate a vector of valid words based on T9 input string.

// Ex: 123 = [ABC][DEF][GHI]
// based off of dictionary & hashmap of valid words