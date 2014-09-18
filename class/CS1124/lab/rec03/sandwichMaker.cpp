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
				<< "\nmustard: " << mustard << endl;
		}
		//accessors
		int getBread() const{return bread;}
		int getCheese() const{return cheese;}
		int getTomato() const{return tomato;}
		int getMayo() const{return mayo;}
		int getMustard() const{return mustard;}

		//mutators
		int setBread(int newB) {return bread = newB;}
		int setCheeese(int newC) {return cheese = newC;}
		int setTomato(int newT) {return tomato = newT;}
		int setMayo(int newMa) {return mayo = newMa;}
		int setMustard(int newMu) {return mustard = newMu;}
	private:
		int bread, cheese, tomato;
		double mayo, mustard;
};

int main(){
	Sandwich sandwich;
	sandwich.display();
}