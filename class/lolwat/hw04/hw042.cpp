//Brian Chuk
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <math.h>
using namespace std;

template <class RandItr, class T, class Comparator>
T select_item(RandItr start, RandItr end, Comparator comp) {
	for (RandItr tmp_itr(end); tmp_itr != start; tmp_itr--)
		if (comp(*tmp_itr))
			return tmp_itr; //"The function returns an iterator"
	return *end; //"the function returns the value of the iterator end"
}

class closest_stop {
public:
	closest_stop(double lo, double la) : longitude(lo), latitude(la), shortest_dist(numeric_limits<double>::max( )) {}
	bool operator()(train_stop_data what) {
		if (sqrt((what.getLon() - longitude) * (what.getLon() - longitude) + (what.getLat() - latitude) * (what.getLat() - latitude)) < shortest_dist){
			shortest_dist = sqrt((what.getLon() - longitude) * (what.getLon() - longitude) + (what.getLat() - latitude) * (what.getLat() - latitude));
			return true;
	}

		return false;
	}
private:
	double longitude, latitude, shortest_dist;
};


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

class LessThanByName { 
public:
	LessThanByName(string durr) : me(durr) {}
	bool operator()(const student& lhs, const student& rhs) const {
		if (me == lhs.get_name())
			return true;
		else if (me == rhs.get_name())
			return false
		else
			return lhs.get_name() < rhs.get_name();
	}
private:
	string me;
};


template<class Comparable>
void printVec(vector<Comparable>& a) {
	for (int i = 0; i < a.size(); i++)
		cout << a[i] << " ";
	cout << endl;
}

void quickSort( vector<int> & a, int low, int high )
{
if (low < high)
{
int mid = ( low + high )/2; // select pivot to be element in middle position
int pivot = a[ mid ];
swap( a[high], a[mid] ); // put pivot in a[high]
// Begin partitioning
int i, j;
for( i = low, j = high - 1; ; )
{
while ( a[i ] < pivot ) ++i;
while( j > i && pivot < a[j ] ) --j;
if( i < j )
swap( a[ i++ ], a[ j-- ] );
else
break;
}
swap( a[ i ], a[ high ] ); // Restore pivot
printVec(a); // prints the contents of the vector in order
quickSort( a, low, i - 1 ); // Sort small elements
quickSort( a, i + 1, high ); // Sort large elements
}
}

int main() {
	// int myints[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	// std::vector<int> pls (myints, myints + sizeof(myints) / sizeof(int) );
	// mergeSort(pls.begin(), pls.end());
	int what[] = {9, 8, -11, 2, 0, 3};
	std::vector<int> pls (what, what + sizeof(what) / sizeof(int) );
	quickSort(pls, 0, pls.size() - 1);
}