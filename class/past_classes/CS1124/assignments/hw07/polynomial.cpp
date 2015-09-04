#include "polynomial.h"
#include <vector>
#include <iostream>
#include <string>
	using namespace std;

void listDisplay(const Node* headPtr) {
	const Node* p = headPtr;
	// Loop through the list.
	while (p) {
		cout << p->data << ' ';
		p = p->link;
	}
	cout << endl;
}

Polynomial::Polynomial(const int newDegree, const vector<int> coefficients) : degree(newDegree) {
	vector<Node*> temp;
	for (int i = coefficients.size() - 1; i >= 0; i--) {
		Node* newNode = new Node;			//4107
		newNode->data = coefficients[i];
		temp.push_back(newNode);			//7014
	}
	for (int i = 0; i < temp.size(); i++) {
		if (i != temp.size() - 1)
			temp[i]->link = temp[i + 1];
	}
	head = temp[0];
	// listDisplay(head);
}

Node* Polynomial::getHead() const {
	return head;
}

int Polynomial::getDeg() const {
	return degree;
}

Polynomial Polynomial::operator+=(const Polynomial& rhs) {
	Node* lp = head;
	Node* rp = rhs.Polynomial::getHead();
	Node* temp = head;
	while (lp && rp) {
		lp->data += rp->data;
		if (!lp->link) {
		}
		rp = rp->link;
		temp = lp;
		lp = lp->link;
	}
	if (rp) {
		temp->link = rp;
	}
	if (Polynomial::getDeg() < rhs.Polynomial::getDeg())
		degree = rhs.Polynomial::getDeg();
	return *this;
}

bool Polynomial::operator==(Polynomial& rhs) {
	Node* lp = head;
	Node* rp = rhs.Polynomial::getHead();
	while (lp && rp) {
		if (lp->data != rp->data)
			return false;
		lp = lp->link;
		rp = rp->link;
	}
	if (lp || rp) {
		return false;
	}
	return true;
}

void Polynomial::evaluate(int& y) {}
string Polynomial::display() const {
	string ans = "";
	int count = 0;
	Node* p = head;
	while (p != NULL) {
		if (count == 1 && p->data)
			ans = to_string(p->data) + "x + " + ans;
		else if (count && p->data)
			ans = to_string(p->data) + "x^" + to_string(count) + " + " + ans;
		else if (!count)
			ans = to_string(p->data);
		p = p->link;
		count++;
	}
	return ans;
}

const Polynomial operator+(Polynomial& lhs, Polynomial& rhs) {
	Polynomial ans(lhs);
	ans += rhs;
	return ans;
}

bool operator!=(Polynomial& lhs, Polynomial& rhs) {
	return !(lhs == rhs);
}
std::ostream& operator<<(std::ostream& os, const Polynomial& num) {
	os << num.display();
	return os;
}