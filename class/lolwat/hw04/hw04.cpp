//Brian Chuk bc1691
#include <iostream>
#include <vector>
	using namespace std;

//2~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class Object>
Object summation(Object x, int n) {
	if (n == 0)
		return x;
	else {
		cout << x << ", ";
		return x + summation(++x, --n);
	}
}
//3~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void patternPrint(int n) {
	if (n == 1)
		cout << " 1 ";
	else {
		patternPrint(n - 1);
		cout << " " << n << " ";
		patternPrint(n - 1);
	}
}
//4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<class Object>
Object sumRecurse(const vector<Object> & a, int left, int right) {
	int half = (right - left) / 2;
	if (right - left == 1)
		return a[left];
	else
		return sumRecurse(a, left, right - half) + sumRecurse(a, right - half, right);
}

template<class Object>
Object sumVector( const vector<Object> & a) {// driver program
	return sumRecurse(a, 0, a.size());
}
//6~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class RandItr>
void mergeSort(RandItr start, RandItr end) {
	int sz = end-start; // or use auto sz = end-start;
	typedef typename iterator_traits<RandItr>::value_type Object; //Xcode
	// typedef iterator_traits<RandItr>::value_type Object; //Other compilers
	// Don’t worry about this line of code
	vector<Object> tmp(sz);
	mergeSort(tmp.begin(), start, end);
}
//7~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//TODO 6, 7. Written Questions 2-7, & 15

int main() {
	//Test for #3
	// patternPrint(3);
	// cout << endl;
	// patternPrint(5);
	// cout << endl;

	//Test for #4
	vector<int> durr;
	durr.push_back(-21);
	durr.push_back(31);
	durr.push_back(14);
	durr.push_back(1);
	durr.push_back(-20);
	cout << sumVector(durr) << endl;

}