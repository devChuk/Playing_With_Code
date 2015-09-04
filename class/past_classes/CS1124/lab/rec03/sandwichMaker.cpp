/*
Brian Chuk
bc1691
9/18/14

lab03

We have just been hired by a sandwich making company to write modeling code for them.
Specifically they are interested in the order taking, sandwich making, delivery truck loading and delivery and return of the delivery trucks. We'll do this in steps, of course, as we always think incremental development.

Our job is to create software tools that the company's programmers can use.
In testing our code, we'll be writing code a lot like what their programmers might write but our job is really only to provide the things they will need.
*/

#include <iostream>
#include <vector>
#include <string>
	using namespace std;

class Sandwich {
	public:
		Sandwich(int c = 1, int t = 2, int ma = 0.1, int mu = 0.05): tomato(t), cheese(c), mustard(mu), mayo(ma), bread(2){}

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
		int setCheeese(int newC) {return cheese = newC;}
		int setTomato(int newT) {return tomato = newT;}
		int setMayo(int newMa) {return mayo = newMa;}
		int setMustard(int newMu) {return mustard = newMu;}

	private:
		const int bread;
		int cheese, tomato;
		double mayo, mustard;
};

class Truck {
	public:
		void insertSandwich(const Sandwich& s) {
			sandwiches.push_back(s);
		}

		void checkBeforeLeaving() const{
			for (int i = 0; i < sandwiches.size(); i++) {
				sandwiches[i].display();
			}
		}
	private:
		vector<Sandwich> sandwiches;
};

int main() {
	Truck truck;
	Sandwich one;
	Sandwich two;
	two.setMustard(0);
	Sandwich three = Sandwich(2, 2, 0.1, 0.05);
	Sandwich four;

	truck.insertSandwich(one);
	truck.insertSandwich(two);
	truck.insertSandwich(three);
	truck.insertSandwich(four);
	truck.checkBeforeLeaving();
	two.getMustard();
}