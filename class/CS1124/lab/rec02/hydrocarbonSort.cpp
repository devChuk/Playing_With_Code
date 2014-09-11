#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct HydroCarbon {
	string name;    			//the name of the hydrocarbon. e.g. Propyne
	string formula;				//the chemical formula of the hydrocarbon. e.g. C3H3	
	int position;				//the 
};

void searchHydrocarbon(vector<HydroCarbon>& molecules, numC, numH) {
								//finds a hydrocarbon


}

void readAndProcessFile(ifstream ifs, vector<HydroCarbon> molecules) {
								//the name is rather self-explanatory
	
}

void displayHydroCarbons(vector<HydroCarbon>& molecules) {
								//prints out the HydroCarbons
}

int findMax(vector<HydroCarbon>& molecules) {
								//finds the maximum carbon amount in a single molecule
}

int main() {					//the main function that pulls it all together
	vector<HydroCarbon> molecules;
	ifstream ifs("hydrocarbon-set-in-example.txt");
	readAndProcessFile(ifs, molecules);








	ifs.close();

}