#ifndef RATIONAL_H
#define RATIONAL_H


#include <vector>
#include <iostream>
#include <string>

namespace CS1124 {

	class Rational {

	};


	std::istream& operator>>(std::istream& is, const Rational& num);
	std::ostream& operator<<(std::ostream& os, const	Rational& num);
/*
Stuff to implement
<<
>>
+=
+
==
!=
++
--

ostream& operator<< (ostream& os, const Elephant& e) {
    	//os << e.getName();
    	return os;
	} 

*/


}
#endif