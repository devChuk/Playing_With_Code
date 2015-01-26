/*If Base has virtual functions then Derived needs to override them all
Any virtual function in derived must be virtual in base
Base destructor should be virtual
Any object of type Base is an object of type Derived
If Base has friend<< then it is also a friend of Derived
Assigning an object of type Base to Derived is called slicing
Pure virtual functions in Base are PV in Derived (by default)
System provided 
*/

/*

A 	 	N
B 	 	N
C 	 	Y
E 	 	N
F 	 	N
G 	 	N
H 	 	Y
I 	 	Y
J 	 	Y

*/
#include <iostream>
#include <climits>
#include <string.h>
#include <stdio.h>
using namespace std;

struct Node {
	Node(int d = 0, Node* l = NULL) : data(d),link(l) {}
	int data;
	Node* link;
};

bool remove(vector<int>& theVector, int target) {
	for (vector<int>::iterator durr = theVector.begin(); durr != theVector.end(); durr++) {
		if (*durr == target) {
			*durr = theVector[theVector.size() - 1];
			theVector.pop_back();
			return true;
		}
	}
	return false;
}

void throwIfNegativeOne(int i) {
	if (i == -1) {
		Exception up;
		up.message = "YOU DONE GOOF";
		throw up;
	}
}

template<class T>
T multiply(T num1, T num2) {
	return num1 * num2;
}