/*
Brian Chuk
CS1124 Recitation02

This program is built to take in a text file that contains a list of hydrocarbons. After that, it 
prints out the hydrocarbons in order of increasing carbon atom amount.
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct HydroCarbon {
	string name;    			//the name of the hydrocarbon. e.g. Propyne
	int numCarbon;				//the number of carbon atoms
	int numHydrogen;			//the number of hydrogren atoms
};

HydroCarbon searchHydrocarbon(vector<HydroCarbon>& vector, int numC, int numH) {
								//finds a hydrocarbon. false if not found. true if found.
	HydroCarbon ans;
	ans.name = "null";
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i].numCarbon == numC && vector[i].numHydrogen == numH) {
			ans = vector[i];
			return ans;
			break;				//if a hydrocarbon is not found, a hydrocarbon is returned with a name of "null"
		}
	}
}

void readAndProcessFile(ifstream& ifs, vector<HydroCarbon>& molecules) {
								//the name is rather self-explanatory
	string name;
	char junk;
	int numC;
	int numH;
	while (ifs >> name >> junk >> numC >> junk >> numH) { 
								//a while loop that goes through each line and extracts the information
		HydroCarbon foo = searchHydrocarbon(molecules, numC, numH);
		if (foo.name == "null") {
			HydroCarbon someHC;
			someHC.name = name;
			someHC.numCarbon = numC;
			someHC.numHydrogen = numH;
			molecules.push_back(someHC);
		}
		else {					//if a molecule with the same carbon and hydrogen atom count exists, a name is pushed into that existing molecule
			searchHydrocarbon(molecules, numC, numH).name = searchHydrocarbon(molecules, numC, numH).name + name;
		}
	}
}

int findMax(vector<HydroCarbon>& molecules) {
								//finds the maximum carbon amount in a single molecule
	int max = 0;
	for (int i = 0; i < molecules.size(); i++) {
		if (molecules[i].numCarbon > max) {
			max = molecules[i].numCarbon;
		}
	}
	return max;

}

void displayHydroCarbons(vector<HydroCarbon>& molecules) {
								//prints out the HydroCarbons
	int max = findMax(molecules);
	for (int count = 0; count <= max; count++) {
								//this makes it print only the molecules of the same carbon amount
		for (int i = 0; i < molecules.size(); i++) {
								//this iterates through all molecules
			if (count == molecules[i].numCarbon) {
				cout << 'C' << molecules[i].numCarbon << 'H' << molecules[i].numHydrogen << " " << molecules[i].name << endl;
			}
		}
	}
}

int main() {					//the main function that pulls it all together
	vector<HydroCarbon> molecules;
	ifstream ifs("hydrocarbon-set-in-example.txt");
	readAndProcessFile(ifs, molecules);
	displayHydroCarbons(molecules);
	ifs.close();

}