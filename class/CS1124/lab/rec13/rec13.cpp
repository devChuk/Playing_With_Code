#include <iostream>
#include <climits>
#include <string.h>
#include <stdio.h>
using namespace std;

struct Node {
  Node(int data = 0, Node* link = NULL) : data(data), link(link) {}
  int data;
  Node* link;
};

void binary(int num) {
	if (num == 1) {
		cout << 1;
		return;
	}

	binary(num / 2);
	cout << num % 2;
}

Node* sumList(Node* head1, Node* head2) {
	if (head1->link) {
		Node* yo = new Node;
		yo->data = head1->data + head2->data;
		yo->link = sumList(head1->link, head2->link);
		return yo;
	}
	else {
		Node* yo = new Node;
		yo->data = head1->data + head2->data;
		return yo;
	}
}

void listDisplay(const Node* headPtr) {
	const Node* p = headPtr;
	// Loop through the list.
	while (p != NULL) {
		cout << p->data << ' ';
		p = p->link;
	}
	cout << endl;
}

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
	if (!root)
		return INT_MIN;
	int left = max(root->left);
	int right = max(root->right);
	if (root->data > left && root->data > right)
		return root->data;
	else if (left >= right)
		return left;
	else
		return right;
}

int stringSum(char* p) {
	if (!(*p))
		return 0;
	else
		return int(*p) + stringSum(p + 1);
}

int binSearch(char* p, char target) {
	int half = strlen(p) / 2;
	if (target > p[half]) {
		return binSearch(p + half, target);
		return 0;
	}
	else if (target == p[half]) {
		return half;
	}
	else {
		p[half] = 0;
		return binSearch(p, target);
	}
}



int main() {
	cout << "binary of 8" << endl;
	binary(8);
	cout << endl;
	cout << "binary 10" << endl;
	binary(10);
	cout << "\n" << "================\n" << endl;

	Node one; one.data = 1;
	Node nine; nine.data = 9; nine.link = &one;
	Node seven; seven.data = 7; seven.link = &nine;
	Node two; two.data = 2;
	Node three; three.data = 3; three.link = &two;
	Node six; six.data = 6; six.link = &three;
	//6 3 2 + 7 9 1 = 13 12 3
	Node* swag = sumList(&six, &seven);
	listDisplay(swag);
	cout << "================\n" << endl;

	TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
  	cout << max(&f) << endl;	
	cout << "================\n" << endl;

  	char aa('A');
  	char cstring[] = "IloveC++"; 
  	cout << stringSum(cstring) << endl;	
	cout << "================\n" << endl;

  	char ccstring[] = "abcdefghijklmnopqrstuv";
  	cout << binSearch(ccstring, 'c') << endl;	
}