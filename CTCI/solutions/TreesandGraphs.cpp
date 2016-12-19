#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>


#include <set>
#include <functional>
#include <algorithm>
#include <math.h>

struct TNode {
	TNode* left;
	TNode* right;
	int data;
};

struct GNode {
	int data;
	std::vector<GNode*> nodes;
};

int checkHeight(TNode* head) {
	if (!head)
		return 0;

	int leftHeight = checkHeight(head->left);
	if (leftHeight == -1)
		return -1;

	int rightHeight = checkHeight(head->right);
	if (rightHeight == -1)
		return -1;

	if (abs(leftHeight - rightHeight) > 1)
		return -1;
	else {
		return std::max(leftHeight, rightHeight) + 1;
	}
}

bool isBalanced(TNode* head) {
	if (checkHeight(head) == -1)
		return false;
	else {
		return true;
	}
}

int main() {
	if (-1) {
		std::cout << "test" << std::endl;
	}
}