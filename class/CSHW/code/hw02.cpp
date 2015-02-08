//Brian Chuk
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

class trainStopData {
public:
	trainStopData(string newID, string newName, double newLat, double newLong) :
	stop_id(newID), stop_name(newName), stop_lat(newLat), stop_lon(newLong) {}
	string get_id() const {return stop_id;}
	string get_stop_name() const {return stop_name;}
	double get_latitude() const {return stop_lat;}
	double get_longitude() const {return stop_lon;}
private:
	string stop_id; // id of train stop (1st token)
	string stop_name; // name of station (4th token)
	double stop_lat; // latitude of train stop location
	double stop_lon; // longitude of train stop location
};

int main() {
	vector<trainStopData> data;
	ifstream ifs("MTA_train_stop_data.txt");
	string s;
	int count = 1;
	int newL;
	string stop_id, stop_name;
	double stop_lat, stop_lon;

	while (getline(ifs,s,',')) {
		switch(count) {
			case 1:
				stop_id = s;
				count++;
			break;
			case 3:
				stop_name = s;
				count++;
			break;
			case 5:
				stop_lat = atof(s.c_str());
				count++;
			break;
			case 6:
				stop_lon = atof(s.c_str());
				count++;
			break;
			case 10:
				newL = s.find("\n");
				data.push_back(trainStopData(stop_id,stop_name,stop_lat,stop_lon));
				stop_id = s.substr(newL+1);
				count = 2;
			break;
			default:
				count++;
		}
	}
	for (int i = 0; i < data.size(); i++) {
		cout << " ID: " << data[i].get_id() << " NAME: " << data[i].get_stop_name() << " LAT: " << data[i].get_latitude() << " LON: " << data[i].get_longitude() << endl;
	}

}