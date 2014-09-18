#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Sandwich {
	public:
		Sandwich(int b = 2, int c = 1, int t = 2, int ma = 0.1, int mu = 0.05):
			tomato(t), cheese(c), mustard(mu), mayo(ma), bread(b){
		}

		void display(ostream& os = cout) const{
			cout<< "bread: " << bread 
				<< "\ncheese: " << cheese 
				<< "\ntomato: " << tomato 
				<< "\nmayo: " << mayo 
				<< "\nmustard" << mustard << endl;
		}

	private:
		int bread, cheese, tomato;
		double mayo, mustard;
};

int main(){
	Sandwich sandwich;
	sandwich.display();
}