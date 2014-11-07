#include "Rational.h"
#include <vector>
#include <iostream>
#include <string>
	using namespace std;

namespace CS1124 {

	Rational::Rational() {}

	int Rational::getNumerator() const {
		return numerator;
	}
	int Rational::getDenominator() const {
		return denominator;
	}
	void Rational::setNumerator(int i) {
		numerator = i;
	}
	void Rational::setDenominator(int i) {
		denominator = i;
	}
	Rational& Rational::operator=(const int& i) {
		numerator = i;
		denominator = 1;
	}
/////////////////////////////////////////////////////////////////////////
	istream& operator>>(istream& is, Rational& num) {
		//is num, char, denom
		int numer, den;
		is >> numer >> den;
		num.setNumerator(numer); num.setDenominator(den);
		return is;
	}
	ostream& operator<<(ostream& os, const	Rational& num) {
		if (num.getDenominator() == 1)
			os << num.getNumerator();
		else
			os << num.getNumerator() << "/" << num.getDenominator();
	}
	int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
	}
}