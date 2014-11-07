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
		void simplify();
		Rational& operator=(const int &i);
		Rational& operator+=(const Rational& rhs);
		bool operator==(Rational& rhs);
		Rational& operator++();
		Rational operator++(int);

	private:
		int numerator, denominator;
	};

	std::istream& operator>>(std::istream& is, Rational& num);
	std::ostream& operator<<(std::ostream& os, const Rational& num);
	int greatestCommonDivisor(int x, int y);
	const Rational operator+(Rational& lhs, Rational& rhs);
	bool operator==(int i, Rational& rhs);
	bool operator!=(Rational& lhs, Rational& rhs);
	Rational& operator--(Rational& r);
	Rational& operator--(Rational& r, int);
/*
--

Complex& operator-- (Complex& x) {
		x.real--;
		return x;
	}
	
	// Overloading the -- post-decrement operator.
	Complex operator-- (Complex& x, int) {
		Complex temp(x);
		x.real--;
		return temp;
	}

*/


}
#endif