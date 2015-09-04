#include "Rational.h"
#include <vector>
#include <iostream>
#include <string>
	using namespace std;

namespace CS1124 {

	int greatestCommonDivisor(int x, int y) {
	while (y != 0) {
    	int temp = x % y;
        x = y;
        y = temp;
	}
    return x;
	}

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
	void Rational::simplify() {
		int d = greatestCommonDivisor(numerator, denominator);
		Rational::setNumerator(numerator / d);
		Rational::setDenominator(denominator / d);
		if (denominator < 0 && numerator > 0) {
			numerator *= -1;
			denominator *= -1;
		}
	}
	Rational& Rational::operator=(const int& i) {
		numerator = i;
		denominator = 1;
	}
	Rational& Rational::operator+=(const Rational& rhs) {
		int mult = rhs.getDenominator();
		Rational::setNumerator(	(Rational::getNumerator() * rhs.getDenominator()) + 
								(rhs.getNumerator() * Rational::getDenominator()));
		Rational::setDenominator(mult * Rational::getDenominator());
		Rational::simplify();
		return *this;
	}
	bool Rational::operator==(Rational& rhs) {
		rhs.simplify();
		Rational::simplify();
		if (Rational::getNumerator() == rhs.getNumerator() && Rational::getDenominator() == rhs.getDenominator()) {
			return true;
		}
	}
	Rational& Rational::operator++() {
		Rational::setNumerator(numerator+denominator);
		return *this;
	}
	Rational Rational::operator++(int) {
		Rational* ans = new Rational();
		ans->setNumerator(numerator);
		ans->setDenominator(denominator);
		Rational::setNumerator(numerator+denominator);
		return *ans;
	}
/////////////////////////////////////////////////////////////////////////
	istream& operator>>(istream& is, Rational& num) {
		//is num, char, denom
		int numer, den;
		is >> numer >> den;
		num.setNumerator(numer); num.setDenominator(den);
		return is;
	}
	ostream& operator<<(ostream& os, const Rational& num) {
		if (num.getDenominator() == 1)
			os << num.getNumerator();
		else
			os << num.getNumerator() << "/" << num.getDenominator();
	}
	const Rational operator+(Rational& lhs, Rational& rhs) {
		Rational* ans = new Rational();
		ans->setNumerator(lhs.getNumerator());
		ans->setDenominator(lhs.getDenominator());
		cout << "swag" << endl;
		*ans += rhs;
		return *ans;
	}
	bool operator==(int i, Rational& rhs) {
		if (rhs.getDenominator() == 1 && rhs.getNumerator() == i) {
			return true;
		}
		return false;
	}
	bool operator!=(Rational& lhs, Rational& rhs) {
		return !(lhs == rhs);
	}
	Rational& operator--(Rational& r) {
		r.setNumerator(r.getNumerator()-r.getDenominator());
		return r;
	}
	Rational& operator--(Rational& r, int) {
		Rational* ans = new Rational();
		ans->setNumerator(r.getNumerator());
		ans->setDenominator(r.getDenominator());
		r.setNumerator(r.getNumerator()-r.getDenominator());
		return *ans;
	}

}