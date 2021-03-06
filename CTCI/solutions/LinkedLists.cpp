#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <functional>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <stack>

struct LLNode {
	LLNode(int newData, LLNode* newNext) {
		data = newData;
		next = newNext;
	}
	LLNode(int newData) {
		data = newData;
	}

	int data;
	LLNode* next;
};

void removeDupes(LLNode* head) {
	std::unordered_map<int, bool> record;
	record.insert({head->data, true});
	LLNode* current = head->next;
	LLNode* prev = head;

	while (current)
		if (record.count(current->data) > 0) {
			current = current->next;
			prev->next = current;
		} else {
			record.insert({current->data, true});
			current = current->next;
			prev = prev->next;
		}
}

bool isPalindrome(LLNode* head) {
	LLNode* slow = head;
	LLNode* fast = head;
	std::stack<int> stack;

	while (fast != NULL && fast->next != NULL) {
		stack.push(slow->data);
		slow = slow->next;
		fast = fast->next->next;
	}

	if (fast != NULL) {
		slow = slow->next;
	}

	while (slow != NULL) {
		if (slow->data == stack.top()) {
			stack.pop();
			slow = slow->next;
		} else {
			return false;
		}
	}
	return true;
}

int main() {
	// LLNode* head = new LLNode(1);
	// LLNode* second = new LLNode(2);
	// LLNode* third = new LLNode(3);
	// LLNode* fourth = new LLNode(4);
	// LLNode* fifth = new LLNode(5);
	// LLNode* sixth = new LLNode(6);
	// LLNode* seventh = new LLNode(7);
	// LLNode* eighth = new LLNode(8);
	// LLNode* ninth = new LLNode(9);

	// head->next = second;
	// second->next = third;
	// third->next = fourth;
	// fourth->next = fifth;
	// fifth->next = sixth;
	// sixth->next = seventh;
	// seventh->next = eighth;
	// eighth->next = ninth;

	LLNode* head = new LLNode(1);
	LLNode* second = new LLNode(2);
	LLNode* third = new LLNode(3);
	LLNode* fourth = new LLNode(4);
	LLNode* fourthTWO = new LLNode(4);
	LLNode* fifth = new LLNode(3);
	LLNode* sixth = new LLNode(2);
	LLNode* seventh = new LLNode(1);
	// LLNode* eighth = new LLNode(8);
	// LLNode* ninth = new LLNode(9);

	head->next = second;
	second->next = third;
	third->next = fourth;
	fourth->next = fourthTWO;
	fourthTWO->next = fifth;
	fifth->next = sixth;
	sixth->next = seventh;
	// seventh->next = eighth;
	// eighth->next = ninth;

	LLNode* runner = head;
	while (runner != NULL) {
		std::cout << runner->data << " ";
		runner = runner->next;
	}
	std::cout << std::endl;

	// insert function here to test.
	std::cout << isPalindrome(head) << std::endl;


	runner = head;
	while (runner != NULL) {
		std::cout << runner->data << " ";
		runner = runner->next;
	}
	std::cout << std::endl;



}