#include <iostream>
#include <vector>
#include <string>


#include <set>
#include <functional>
#include <algorithm>
#include <math.h>

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



class Stack {
	LLNode* top;

	int pop() {
		if (top != NULL) {
			int item = top->data;
			top = top->next;
			return item;
		}
		return -666;
	}

	void push(int item) {
		LLNode* t = new LLNode(item);
		t->next = top;
		top = t;
	}

	int peek() {
		return top->data;
	}
};


class Queue {
	LLNode* first;
	LLNode* last;

	void enqueue(int item) {
		if (first == NULL) {
			last = new LLNode(item);
			first = last;
		} else {
			last->next = new LLNode(item);
			last = last->next;
		}
	}

	int dequeue() {
		if (first != NULL) {
			int item = first->data;
			first = first->next;
			return item;
		}
		return -666;
	}
};

int main() {
	
}