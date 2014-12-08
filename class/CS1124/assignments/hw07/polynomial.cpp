#include "polynomial.h"
#include <vector>
#include <iostream>
#include <string>
	using namespace std;

Polynomial::Polynomial(const int newDegree, const vector<int> coefficients) : degree(newDegree) {

}
Polynomial Polynomial::operator+=(const Polynomial& rhs) {}
bool Polynomial::operator==(Polynomial& rhs) {}

const Polynomial operator+(Polynomial& lhs, Polynomial& rhs) {}
bool operator!=(Polynomial& lhs, Polynomial& rhs) {}
std::ostream& operator<<(std::ostream& os, const Polynomial& num) {}