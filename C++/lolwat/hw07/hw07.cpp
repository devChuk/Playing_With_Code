#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
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
		string stop_id = line.substr(0,line.find(','));
		moo[stop_id] = count;
		int_to_stop_id.push_back(stop_id);
		count++;
	}
}

int main() {
	map<string, int> moo;
	vector<string> int_to_stop_id;
	parseTrainData(moo, int_to_stop_id);

}