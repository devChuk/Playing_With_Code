#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;



template <class RandItr>
void mergeSort(RandItr beg, RandItr start, RandItr end) {
    if (end-start < 2)
            return;
    int sz = end-start;
    int middle = sz / 2;
    mergeSort(beg, start, start + middle);
    mergeSort(beg, start + middle, end);
    std::merge(start, start + middle, start + middle, end, beg);
    std::copy(beg, beg + sz, start);
 
}

template <class RandItr>
void mergeSort(RandItr start, RandItr end) {
	int sz = end-start; // or use auto sz = end-start;
	typedef typename iterator_traits<RandItr>::value_type Object; //Xcode
	// typedef iterator_traits<RandItr>::value_type Object; //Other compilers
	// Don’t worry about this line of code
	vector<Object> tmp(sz);
	mergeSort(tmp.begin(), start, end);
	for (int i = 0; i < tmp.size(); i++) {
		cout << tmp[i] << " ";
	}
	cout << endl;
}

int main() {
	int myints[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	std::vector<int> pls (myints, myints + sizeof(myints) / sizeof(int) );
	mergeSort(pls.begin(), pls.end());
}