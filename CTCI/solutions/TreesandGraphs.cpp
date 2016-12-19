#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>


#include <set>
#include <functional>
#include <algorithm>
#include <math.h>

#include <queue>

struct TNode {
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

void hurrdurr(int swag[]) {}

int main() {
	
}