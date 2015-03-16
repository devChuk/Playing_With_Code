#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
using namespace std;

template <class RandItr>
void mergeSort(RandItr start, RandItr end) {
	int sz = end-start; // or use auto sz = end-start;
	typedef typename iterator_traits<RandItr>::value_type Object; //Xcode
	// typedef iterator_traits<RandItr>::value_type Object; //Other compilers
	// Don’t worry about this line of code
	vector<Object> tmp(sz);
	mergeSort(tmp.begin(), start, end);
}

int main() {

}