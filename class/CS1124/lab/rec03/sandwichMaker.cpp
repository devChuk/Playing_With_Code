#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Sandwich {
	public:
		Sandwich(int bread = 2, int cheese = 1, int tomato = 2, int mayo = 0.1, int mustard= 0.05) {}
		void display(ostream os = cout) const {
			os << "bread: " << bread << "\ncheese: " << cheese << "\ntomato: " << tomato << "\nmayo: " << mayo << "\nmustard" << mustard << endl;
		}
	private:
		int bread, cheese, tomato;
		double mayo, mustard;
};

int main(){
	Sandwich sandwich;
	sandwich.display();
}