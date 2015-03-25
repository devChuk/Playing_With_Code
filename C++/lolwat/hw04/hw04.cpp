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

//Written Questions 2-7, & 15

void myRecFunc(int n)
{
cout << n << ": ";
if (n < 1) return;
myRecFunc(n/2);
}

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
	// cout << sumVector(durr) << endl;

	myRecFunc(4);

}