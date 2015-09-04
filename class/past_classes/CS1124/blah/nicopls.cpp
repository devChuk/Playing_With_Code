#include <iostream>
#include <climits>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;

class Joe{
public:
	Joe(){

	}
	Joe(const string& name, int numberJoes = 0){
		for(int i = 0; i < numberJoes; ++i){
			lilJs.push_back(new Joe(name));
		}
	}
	Joe(const Joe& rhs) {
		name = rhs.name;
		for (int i = 0; i < rhs.lilJs.size(); i++) {
			lilJs.push_back(new Joe(rhs.lilJs[i]->name));
		}
	}
	virtual ~Joe() {
		for(int i = 0; i < lilJs.size(); i++) {
			delete lilJs[i];
		}
	}
	Joe operator=(const Joe& rhs) {
		if (this != &rhs) {
			if (lilJs.size() != rhs.lilJs.size()) {
				for(int i = 0; i < lilJs.size(); i++)
					delete lilJs[i];
			while (lilJs.size() < rhs.lilJs.size()) {
				lilJs.push_back(NULL);
			}
		}
			name = rhs.name;
			for (int i = 0; i < rhs.lilJs.size(); i++) {
				lilJs[i] = new Joe(rhs.lilJs[i]->name);
			}
		}
		return *this;
	}
	void gimmeLils(const string& name, int numberJoes){
		for(int i = 0; i <numberJoes; ++i){
			lilJs.push_back(new Joe(name));
		}
	}





private:
	vector<Joe*> lilJs;
	string name;
};

class Smith: public Joe{
public:
	Smith(int t, const string& name, int numberJs = 0):tomatos(t), Joe(name, numberJs){}
	Smith(const Smith& rhs): Joe(rhs) {
		tomatos = rhs.tomatos;
	}
	~Smith() {}
	Smith operator=(const Smith& rhs) {
		if (this != &rhs) {
			tomatos = rhs.tomatos;
		}
		return *this;
	}
private:
	int tomatos;

};

main(){

	Joe* j = new Joe("BIG JOEY");
	j->gimmeLils("lil j", 8);





}