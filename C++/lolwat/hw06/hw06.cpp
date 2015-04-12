//Brian Chuk
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <math.h>
#include <list>
using namespace std;


//preconditions
//	it is a valid forward iterator
//	n is a valid int
//	

//post conditions
//	it now points n items ahead


template <class ForwardIterator>
	void advance (ForwardIterator& it, int n) {
		for (int i = 0; i < n; i++) {
			it++;
		}
	}

int main() {

}