#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <vector>
#include <iostream>
#include <string>

struct Node {
  Node(int data = 0, Node* link = NULL) : data(data), link(link) {}
  int data;
  Node* link;
};

class Polynomial {
public:
	Polynomial(const int newDegree, const std::vector<int> coefficients);
	Polynomial operator+=(const Polynomial& rhs);
	bool operator==(Polynomial& rhs);


private:
	int degree;
	Node* head;
};

const Polynomial operator+(Polynomial& lhs, Polynomial& rhs);
bool operator!=(Polynomial& lhs, Polynomial& rhs);
std::ostream& operator<<(std::ostream& os, const Polynomial& num);

#endif