#include <iostream>
#include <vector>
#include <string>


#include <set>
#include <functional>
#include <algorithm>
#include <math.h>

template <class Object>
Object sumVector(const std::vector<Object> & a, int left, int right) {
        
}

int runFunction(int one, int two) {
	std::cout << "ran" << std::endl;
	return one;
}

int main() {
	
	while(false) {
	   int a = 4;
	}

	for (int i = 0; i < 10; i++) {
		std::cout << i << std::endl;
	}

	do {
	   int b = 2;
	} while( false );


	std::cout << "ay" << std::endl;

	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (4,100);                       // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);                       // a copy of third


	/*
	char grade = 'D';

	switch(grade)
	{
	case 'A' :
		cout << "Excellent!" << endl; 
		break;
	case 'B' :
	case 'C' :
		cout << "Well done" << endl;
		break;
	case 'D' :
		cout << "You passed" << endl;
		break;
	case 'F' :
		cout << "Better try again" << endl;
		break;
	default :
		cout << "Invalid grade" << endl;
	}
	*/

	string str1 = "Hello";
	string str2 = "World";
	string str3;
	int  len ;

	// copy str1 into str3
	str3 = str1;
	cout << "str3 : " << str3 << endl;

	// concatenates str1 and str2
	str3 = str1 + str2;
	cout << "str1 + str2 : " << str3 << endl;

	// total lenghth of str3 after concatenation
	len = str3.size();
	cout << "str3.size() :  " << len << endl;


	std::string str="We think in generalities, but we live in details.";
                                           // (quoting Alfred N. Whitehead)

	std::string str2 = str.substr (3,5);     // "think"


	runFunction(1,2);
	
	/*
	// 3
	// 1 5
	// 3 10
	// 999 -34343

	int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        cout << a+b << "\n";
    }
    */   

    return 0;
}