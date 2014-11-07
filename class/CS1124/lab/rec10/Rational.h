#ifndef RATIONAL_H
#define RATIONAL_H


#include <vector>
#include <iostream>
#include <string>

namespace CS1124 {

	class Rational {
	public:
		Rational();
		int getNumerator() const;
		int getDenominator() const;
		void setNumerator(int i);
		void setDenominator(int i);
		Rational& operator=(const int &i);
	private:
		int numerator, denominator;
	};


	std::istream& operator>>(std::istream& is, Rational& num);
	std::ostream& operator<<(std::ostream& os, const Rational& num);
	int greatestCommonDivisor(int x, int y);
/*
Stuff to implement
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