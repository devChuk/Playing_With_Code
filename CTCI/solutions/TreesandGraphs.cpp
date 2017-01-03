#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <stdlib.h>
#include <limits>


#include <set>
#include <functional>
#include <algorithm>
#include <math.h>

#include <queue>

struct TNode {

	TNode(int item) {
		data = item;
	}
	TNode* left;
	TNode* right;
	int data;
};

struct GNode {
	int data;
	bool visited = false;
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

void DFsearch(TNode* root) {
	if (root) {
		DFsearch(root->left);
		DFsearch(root->right);
	}
}

void BFsearch(GNode* root) {
	std::queue<GNode*> queue;
	root->visited = true;
	queue.push(root);

	while (!queue.empty()) {
		GNode* r = queue.front();
		queue.pop();
		for (int i = 0; i > r->nodes.size(); i++) {
			if (!r->nodes[i]->visited) {
				r->nodes[i]->visited = true;
				queue.push(r->nodes[i]);
			}
		}
	}
}

bool checkForRoute(GNode* start, GNode* end) {
	std::queue<GNode*> queue;
	start->visited = true;
	queue.push(start);

	while (!queue.empty()) {
		GNode* r = queue.front();
		if (r == end)
			return true;
		for (int i = 0; i < r->nodes.size(); i++) {
			GNode* current = r->nodes[i];
			if (!current->visited) {
				current->visited = true;
				queue.push(current);
			}
		}
	}
	return false;
}

TNode* genMinialHeightBST(std::vector<int> array) {
	int n = array.size();

	if (n == 0) {
		return NULL;
	} else if (n == 1) {
		TNode* leaf = new TNode(array[0]);
		return leaf;
	} else {
		TNode* head = new TNode(array[n/2]);
		std::vector<int> leftHalf(array.begin(), array.begin() + n/2);
		std::vector<int> rightHalf(array.begin() + n/2 + 1, array.end());
		head->left = genMinialHeightBST(leftHalf);
		head->right = genMinialHeightBST(rightHalf);
		return head;
	}
}

void printDFSTree(TNode* root) {
	if (root) {
		std::cout << root->data << std::endl;
		printDFSTree(root->left);
		printDFSTree(root->right);
	}
}

void printBFSTree(TNode* root) {
	std::queue<TNode*> queue;
	queue.push(root);

	while (!queue.empty()) {
		TNode* r = queue.front();
		queue.pop();

		if (r != NULL) {
			std::cout << r->data << std::endl;
			queue.push(r->left);
			queue.push(r->right);
		}
	}
}

void addToLists(TNode* root, std::vector<std::list<int>> lists, int depth) {
	if (root != NULL) {
		if (lists.size() <= depth) {
			std::list<int> list;
			lists.push_back(list);
		}
		lists[depth].push_back(root->data);
		addToLists(root->left, lists, depth + 1);
		addToLists(root->right, lists, depth + 1);
	}
}

std::vector<std::list<int>> genLevelLinkedLists(TNode* root) {
	std::vector<std::list<int>> lists;
	addToLists(root, lists, 0);
	return lists;
}

bool checkIfBST(TNode* root, int min, int max) {
	if (root == NULL) {
		return true;
	}

	if (root->data <= min || root->data > max) {
		return false;
	}

	if (!checkIfBST(root->left, min, root->data) ||
		!checkIfBST(root->right, root->data, max)) {
		return false;
	}
	return true;
}

bool checkIfBST(TNode* root) {
	checkIfBST(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

bool testOne() {
	std::cout << "test1 ran" << std::endl;
	return false;
}

bool testTwo() {
	std::cout << "test2 ran" << std::endl;
	return true;
}

// TNode* findInOrderSuccessor(TNode* root) {
// 	if (root->right) {
// 		TNode* runner = root->right;
// 		while (runner->left)
// 			runner = runner->left;
// 		return runner;
// 	} else if (root->parent) {
// 		TNode* runner = root;
// 		while (runner->parent && runner->parent->left != runner) {
// 			runner = runner->parent
// 		}
// 		return runner->parent;
// 	}
// }

bool TreeContainsR(TNode* root, int item) {
	if (root) {
		if (root->data == item)
			return true;
		else
			return TreeContainsR(root->left, item) || TreeContainsR(root->right, item);
	}
	return false;
}

bool TreeContainsP(TNode* root, TNode* item) {
	if (root) {
		if (root == item)
			return true;
		else
			return TreeContainsP(root->left, item) || TreeContainsP(root->right, item);
	}
	return false;	
}

TNode* firstCommonAncestor(TNode* root, TNode* a, TNode* b) {
	if (!TreeContainsP(root, a) || !TreeContainsP(root, b))
		return NULL;

	if (!root)
		return NULL;
	if (root == a && root == b)
		return root;
	TNode* left = firstCommonAncestor(root->left, a, b);
	TNode* right = firstCommonAncestor(root->right, a, b);

	if (left != NULL && left != a && left != b)
		return left;

	if (right != NULL && right != a && right != b)
		return right;

	if (left != NULL && right != NULL)
		return root;
	else if (root == a || root == b)
		return root;
	else
		return (left == NULL) ? right : left;
}

int main() {
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	TNode* root = genMinialHeightBST(v);
	
	// root->right->left->data = 2;

	printBFSTree(root);
	
	std::cout << firstCommonAncestor(root, root->right->right, new TNode(30))->data << std::endl;
	//std::cout << checkIfBST(root) << std::endl;

	// if (testOne() && testTwo()) {
	// 	std::cout << "gg" << std::endl;
	// }
}