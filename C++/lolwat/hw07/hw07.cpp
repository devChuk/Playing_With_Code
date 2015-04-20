#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <list>
using namespace std;

void parseTrainData(map<string, int>& moo, vector<string>& int_to_stop_id) { //fills up moo & int_to_stop_id
	ifstream stopFile("MTA_train_stop_data.txt");
	if (!stopFile) {
		cerr << "Yo the train stop data file's missing.\n";
		exit(1);
	}
	string line;
	getline(stopFile, line);
	int count = 0;
	while (getline(stopFile, line)) {
		int comma = line.find(',');
		string stop_id = line.substr(0,comma);
		if (stop_id.substr(comma-1) != "S" && stop_id.substr(comma-1) != "N") {
			moo[stop_id] = count;
			int_to_stop_id.push_back(stop_id);
			count++;
		}
	}
}

void parseTransfersData(vector<list<int>>& adjacent, map<string, int>& moo, vector<string>& int_to_stop_id) {
	ifstream stopFile("transfers.txt");
	if (!stopFile) {
		cerr << "Yo the transfers data file's missing.\n";
		exit(1);
	}
	string line;
	getline(stopFile, line);
	while (getline(stopFile, line)) { //adjacent index represents init transfer point
		string from = line.substr(0,line.find(','));
		string to = line.substr(4,3);
		cout << from << "|" << to << "|" << moo[from] << "|" << moo[to] << endl;

	}
}

int main() {
	map<string, int> moo;
	vector<string> int_to_stop_id;
	parseTrainData(moo, int_to_stop_id);
	vector<list<int>> adjacent;
	parseTransfersData(adjacent, moo, int_to_stop_id);
}